package ro.adrianus.camerawatch.wear

import android.content.Context
import android.util.Log
import com.google.android.gms.wearable.ChannelClient
import com.google.android.gms.wearable.MessageClient
import com.google.android.gms.wearable.MessageEvent
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

enum class PhoneStreamStatus {
    Idle,
    WaitingForWatch,
    Streaming,
    Error,
}

class PhoneWearBridge(
    context: Context,
    private val onStartRequested: (watchNodeId: String) -> Unit,
    private val onStopRequested: () -> Unit,
) : MessageClient.OnMessageReceivedListener {

    private val appContext = context.applicationContext
    private val messageClient = Wearable.getMessageClient(appContext)
    private val channelClient = Wearable.getChannelClient(appContext)
    private val capabilityClient = Wearable.getCapabilityClient(appContext)

    private val scope = CoroutineScope(SupervisorJob() + Dispatchers.Main.immediate)
    private var listenJob: Job? = null

    private val _status = MutableStateFlow(PhoneStreamStatus.WaitingForWatch)
    val status: StateFlow<PhoneStreamStatus> = _status.asStateFlow()

    private val _statusMessage = MutableStateFlow("Waiting for watch…")
    val statusMessage: StateFlow<String> = _statusMessage.asStateFlow()

    private val sender = FrameStreamSender()

    fun start() {
        messageClient.addListener(this)
        listenJob = scope.launch {
            try {
                // Ensure local capability is advertised via wear.xml; refresh cache.
                capabilityClient.getCapability(
                    WearCapabilities.PHONE,
                    com.google.android.gms.wearable.CapabilityClient.FILTER_ALL,
                ).await()
                _status.value = PhoneStreamStatus.WaitingForWatch
                _statusMessage.value = "Waiting for watch…"
            } catch (t: Throwable) {
                Log.e(TAG, "Capability check failed", t)
                _status.value = PhoneStreamStatus.Error
                _statusMessage.value = "Wearable services unavailable"
            }
        }
    }

    fun stop() {
        messageClient.removeListener(this)
        listenJob?.cancel()
        scope.launch { closeStream() }
    }

    override fun onMessageReceived(messageEvent: MessageEvent) {
        if (messageEvent.path != WearPaths.CONTROL) return
        val command = messageEvent.data.toString(Charsets.UTF_8)
        when (command) {
            ControlCommands.START -> {
                _statusMessage.value = "Watch requested stream"
                onStartRequested(messageEvent.sourceNodeId)
            }
            ControlCommands.STOP -> {
                _statusMessage.value = "Watch stopped stream"
                onStopRequested()
            }
            else -> Log.w(TAG, "Unknown command: $command")
        }
    }

    suspend fun openStreamToWatch(watchNodeId: String) {
        closeStream()
        try {
            val channel = channelClient.openChannel(watchNodeId, WearPaths.STREAM).await()
            val output = channelClient.getOutputStream(channel).await()
            sender.open(output, channel)
            _status.value = PhoneStreamStatus.Streaming
            _statusMessage.value = "Streaming to watch"
        } catch (t: Throwable) {
            Log.e(TAG, "Failed to open channel to watch $watchNodeId", t)
            _status.value = PhoneStreamStatus.Error
            _statusMessage.value = "Failed to open stream"
            throw t
        }
    }

    suspend fun sendFrame(jpegBytes: ByteArray): Boolean = sender.trySend(jpegBytes)

    suspend fun closeStream() {
        val channel = sender.currentChannel()
        sender.close()
        if (channel != null) {
            try {
                channelClient.close(channel).await()
            } catch (t: Throwable) {
                Log.w(TAG, "Channel close failed", t)
            }
        }
        if (_status.value == PhoneStreamStatus.Streaming) {
            _status.value = PhoneStreamStatus.WaitingForWatch
            _statusMessage.value = "Waiting for watch…"
        }
    }

    fun isStreaming(): Boolean = sender.isOpen()

    companion object {
        private const val TAG = "PhoneWearBridge"
    }
}
