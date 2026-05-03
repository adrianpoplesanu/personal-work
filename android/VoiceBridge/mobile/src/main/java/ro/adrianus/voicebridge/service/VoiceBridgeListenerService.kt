package ro.adrianus.voicebridge.service

import android.util.Log
import com.google.android.gms.wearable.MessageEvent
import com.google.android.gms.wearable.Wearable
import com.google.android.gms.wearable.WearableListenerService
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.cancel
import kotlinx.coroutines.launch
import kotlinx.coroutines.tasks.await
import ro.adrianus.voicebridge.config.VoiceBridgeServerConfig
import ro.adrianus.voicebridge.network.BackendClient
import ro.adrianus.voicebridge.shared.VoiceBridgeCodec
import ro.adrianus.voicebridge.shared.VoiceBridgePaths

class VoiceBridgeListenerService : WearableListenerService() {

    private val scope = CoroutineScope(SupervisorJob() + Dispatchers.IO)
    private lateinit var backend: BackendClient

    override fun onCreate() {
        super.onCreate()
        backend = BackendClient(
            VoiceBridgeServerConfig.BASE_URL,
            VoiceBridgeServerConfig.API_KEY,
            VoiceBridgeServerConfig.USE_MOCK,
        )
    }

    override fun onMessageReceived(messageEvent: MessageEvent) {
        if (messageEvent.path != VoiceBridgePaths.ASK) {
            return
        }

        val ask = try {
            VoiceBridgeCodec.decodeAsk(messageEvent.data)
        } catch (e: Exception) {
            Log.e(TAG, "decode_ask_failed", e)
            return
        }

        val sourceNodeId = messageEvent.sourceNodeId
        Log.d(TAG, "phase=ask_received requestId=${ask.requestId} queryLen=${ask.query.length}")

        scope.launch {
            val reply = backend.ask(ask)
            runCatching {
                Wearable.getMessageClient(this@VoiceBridgeListenerService)
                    .sendMessage(
                        sourceNodeId,
                        VoiceBridgePaths.REPLY,
                        VoiceBridgeCodec.encodeReply(reply),
                    )
                    .await()
                Log.d(TAG, "phase=reply_sent requestId=${ask.requestId} success=${reply.answer != null}")
            }.onFailure { e ->
                Log.e(TAG, "reply_send_failed requestId=${ask.requestId}", e)
            }
        }
    }

    override fun onDestroy() {
        scope.cancel()
        super.onDestroy()
    }

    companion object {
        private const val TAG = "VoiceBridge"
    }
}
