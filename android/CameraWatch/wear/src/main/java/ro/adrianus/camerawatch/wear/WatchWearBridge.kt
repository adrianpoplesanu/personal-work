package ro.adrianus.camerawatch.wear

import android.content.Context
import android.graphics.Bitmap
import android.util.Log
import com.google.android.gms.wearable.ChannelClient
import com.google.android.gms.wearable.Wearable
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import kotlinx.coroutines.tasks.await
import ro.adrianus.camerawatch.shared.ControlCommands
import ro.adrianus.camerawatch.shared.WearCapabilities
import ro.adrianus.camerawatch.shared.WearPaths

enum class WatchFeedStatus {
    Disconnected,
    Ready,
    Connecting,
    Streaming,
    Error,
}

class WatchWearBridge(
    context: Context,
) : ChannelClient.ChannelCallback() {

    private val appContext = context.applicationContext
    private val messageClient = Wearable.getMessageClient(appContext)
    private val channelClient = Wearable.getChannelClient(appContext)
    private val capabilityClient = Wearable.getCapabilityClient(appContext)

    private val scope = CoroutineScope(SupervisorJob() + Dispatchers.Main.immediate)
    private val receiver = FrameStreamReceiver(scope)

    private val _status = MutableStateFlow(WatchFeedStatus.Disconnected)
    val status: StateFlow<WatchFeedStatus> = _status.asStateFlow()

    private val _statusMessage = MutableStateFlow("Looking for phone…")
    val statusMessage: StateFlow<String> = _statusMessage.asStateFlow()

    val frame: StateFlow<Bitmap?> = receiver.frame

    private var phoneNodeId: String? = null
    private var discoverJob: Job? = null

    fun start() {
        channelClient.registerChannelCallback(this)
        refreshPhoneNode()
    }

    fun stop() {
        discoverJob?.cancel()
        channelClient.unregisterChannelCallback(this)
        scope.launch { stopStreaming() }
    }

    fun refreshPhoneNode() {
        discoverJob?.cancel()
        discoverJob = scope.launch {
            try {
                val capability = capabilityClient.getCapability(
                    WearCapabilities.PHONE,
                    com.google.android.gms.wearable.CapabilityClient.FILTER_REACHABLE,
                ).await()
                val node = capability.nodes.firstOrNull { it.isNearby }
                    ?: capability.nodes.firstOrNull()
                phoneNodeId = node?.id
                if (node == null) {
                    _status.value = WatchFeedStatus.Disconnected
                    _statusMessage.value = "Phone app not found"
                } else if (_status.value != WatchFeedStatus.Streaming &&
                    _status.value != WatchFeedStatus.Connecting
                ) {
                    _status.value = WatchFeedStatus.Ready
                    _statusMessage.value = "Phone ready"
                }
            } catch (t: Throwable) {
                Log.e(TAG, "Capability discovery failed", t)
                _status.value = WatchFeedStatus.Error
                _statusMessage.value = "Wearable services unavailable"
            }
        }
    }

    fun startStreaming() {
        scope.launch {
            val nodeId = phoneNodeId
            if (nodeId == null) {
                refreshPhoneNode()
                _status.value = WatchFeedStatus.Disconnected
                _statusMessage.value = "Phone app not found"
                return@launch
            }
            _status.value = WatchFeedStatus.Connecting
            _statusMessage.value = "Starting stream…"
            try {
                messageClient.sendMessage(
                    nodeId,
                    WearPaths.CONTROL,
                    ControlCommands.START.toByteArray(Charsets.UTF_8),
                ).await()
                _statusMessage.value = "Waiting for frames…"
            } catch (t: Throwable) {
                Log.e(TAG, "Failed to send START", t)
                _status.value = WatchFeedStatus.Error
                _statusMessage.value = "Failed to contact phone"
            }
        }
    }

    fun stopStreaming() {
        scope.launch {
            val nodeId = phoneNodeId
            if (nodeId != null) {
                try {
                    messageClient.sendMessage(
                        nodeId,
                        WearPaths.CONTROL,
                        ControlCommands.STOP.toByteArray(Charsets.UTF_8),
                    ).await()
                } catch (t: Throwable) {
                    Log.w(TAG, "Failed to send STOP", t)
                }
            }
            closeReceiverChannel()
            if (phoneNodeId != null) {
                _status.value = WatchFeedStatus.Ready
                _statusMessage.value = "Phone ready"
            } else {
                _status.value = WatchFeedStatus.Disconnected
                _statusMessage.value = "Phone app not found"
            }
        }
    }

    override fun onChannelOpened(channel: ChannelClient.Channel) {
        if (channel.path != WearPaths.STREAM) return
        scope.launch {
            try {
                val input = channelClient.getInputStream(channel).await()
                receiver.start(input, channel)
                _status.value = WatchFeedStatus.Streaming
                _statusMessage.value = "Live"
            } catch (t: Throwable) {
                Log.e(TAG, "Failed to accept stream channel", t)
                _status.value = WatchFeedStatus.Error
                _statusMessage.value = "Stream open failed"
            }
        }
    }

    override fun onChannelClosed(
        channel: ChannelClient.Channel,
        closeReason: Int,
        appSpecificErrorCode: Int,
    ) {
        if (channel.path != WearPaths.STREAM) return
        scope.launch {
            receiver.stop()
            if (_status.value == WatchFeedStatus.Streaming) {
                _status.value = WatchFeedStatus.Ready
                _statusMessage.value = "Stream ended"
            }
        }
    }

    private suspend fun closeReceiverChannel() {
        val channel = receiver.currentChannel()
        receiver.stop()
        if (channel != null) {
            try {
                channelClient.close(channel).await()
            } catch (t: Throwable) {
                Log.w(TAG, "Channel close failed", t)
            }
        }
    }

    companion object {
        private const val TAG = "WatchWearBridge"
    }
}
