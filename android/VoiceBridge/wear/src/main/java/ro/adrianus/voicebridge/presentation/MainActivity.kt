/* While this template provides a good starting point for using Wear Compose, you can always
 * take a look at https://github.com/android/wear-os-samples/tree/main/ComposeStarter to find the
 * most up to date changes to the libraries and their usages.
 */

package ro.adrianus.voicebridge.presentation

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.speech.RecognizerIntent
import android.speech.tts.TextToSpeech
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import androidx.core.splashscreen.SplashScreen.Companion.installSplashScreen
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.lifecycleScope
import androidx.wear.compose.material.Button
import androidx.wear.compose.material.MaterialTheme
import androidx.wear.compose.material.Text
import androidx.wear.compose.material.TimeText
import androidx.wear.tooling.preview.devices.WearDevices
import com.google.android.gms.wearable.MessageClient
import com.google.android.gms.wearable.Wearable
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.launch
import kotlinx.coroutines.tasks.await
import ro.adrianus.voicebridge.R
import ro.adrianus.voicebridge.presentation.theme.VoiceBridgeTheme
import ro.adrianus.voicebridge.shared.AskPayload
import ro.adrianus.voicebridge.shared.ReplyPayload
import ro.adrianus.voicebridge.shared.VoiceBridgeCodec
import ro.adrianus.voicebridge.shared.VoiceBridgePaths
import java.util.Locale
import java.util.UUID

private const val TAG = "VoiceBridge"

class MainActivity : ComponentActivity(), TextToSpeech.OnInitListener {

    internal val replyMessages = MutableSharedFlow<ReplyPayload>(extraBufferCapacity = 8)

    private val pendingRequestIdState = MutableStateFlow<String?>(null)
    internal val pendingRequestId = pendingRequestIdState.asStateFlow()

    private val messageListener = MessageClient.OnMessageReceivedListener { event ->
        if (event.path != VoiceBridgePaths.REPLY) {
            return@OnMessageReceivedListener
        }
        val reply = runCatching { VoiceBridgeCodec.decodeReply(event.data) }
            .onFailure { Log.e(TAG, "decode_reply_failed", it) }
            .getOrNull() ?: return@OnMessageReceivedListener
        val emitted = replyMessages.tryEmit(reply)
        if (!emitted) {
            Log.w(TAG, "reply_buffer_full requestId=${reply.requestId}")
        }
    }

    private val messageClient by lazy { Wearable.getMessageClient(this) }

    private var textToSpeech: TextToSpeech? = null
    private var ttsReady: Boolean = false

    private var pendingSttLocaleTag: String = SttLanguage.ENGLISH.localeTag

    private lateinit var speechLauncher: androidx.activity.result.ActivityResultLauncher<Intent>

    override fun onCreate(savedInstanceState: Bundle?) {
        installSplashScreen()
        super.onCreate(savedInstanceState)
        setTheme(android.R.style.Theme_DeviceDefault)

        textToSpeech = TextToSpeech(this, this)
        messageClient.addListener(messageListener)

        speechLauncher = registerForActivityResult(
            ActivityResultContracts.StartActivityForResult(),
        ) { result ->
            if (result.resultCode != RESULT_OK) {
                Log.d(TAG, "stt_cancelled_or_failed code=${result.resultCode}")
                return@registerForActivityResult
            }
            val matches = result.data?.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS)
            val spoken = matches?.firstOrNull()
            if (spoken.isNullOrBlank()) {
                Log.d(TAG, "stt_empty_result")
                return@registerForActivityResult
            }
            sendQueryToPhone(spoken, pendingSttLocaleTag)
        }

        setContent {
            VoiceBridgeTheme {
                VoiceBridgeScreen(
                    activity = this,
                    onSpeakClick = { localeTag ->
                        pendingSttLocaleTag = localeTag
                        launchSpeechRecognizer(localeTag)
                    },
                    replyMessages = replyMessages,
                    onSpeakEnglishAnswer = { text -> speakEnglish(text) },
                )
            }
        }
    }

    override fun onInit(status: Int) {
        ttsReady = status == TextToSpeech.SUCCESS
        if (ttsReady) {
            textToSpeech?.language = Locale.US
            Log.d(TAG, "tts_ready")
        } else {
            Log.e(TAG, "tts_init_failed status=$status")
        }
    }

    private fun speakEnglish(text: String) {
        val tts = textToSpeech
        if (tts == null || !ttsReady) {
            Log.w(TAG, "tts_not_ready skip_speak")
            return
        }
        tts.language = Locale.US
        tts.speak(text, TextToSpeech.QUEUE_FLUSH, null, "vb-${UUID.randomUUID()}")
    }

    private fun launchSpeechRecognizer(localeTag: String) {
        val intent = Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH).apply {
            putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM)
            putExtra(RecognizerIntent.EXTRA_LANGUAGE, localeTag)
            putExtra(RecognizerIntent.EXTRA_PROMPT, getString(R.string.stt_prompt))
        }
        try {
            speechLauncher.launch(intent)
        } catch (e: Exception) {
            Log.e(TAG, "stt_launch_failed", e)
            Toast.makeText(this, R.string.error_stt_launch, Toast.LENGTH_LONG).show()
        }
    }

    private fun sendQueryToPhone(query: String, sttLocaleTag: String) {
        lifecycleScope.launch {
            val requestId = UUID.randomUUID().toString()
            Log.d(TAG, "phase=send_start requestId=$requestId queryLen=${query.length} locale=$sttLocaleTag")
            val nodes = try {
                Wearable.getNodeClient(this@MainActivity).connectedNodes.await()
            } catch (e: Exception) {
                Log.e(TAG, "connected_nodes_failed", e)
                Toast.makeText(this@MainActivity, R.string.error_no_phone, Toast.LENGTH_LONG).show()
                return@launch
            }
            val nodeId = nodes.firstOrNull()?.id
            if (nodeId == null) {
                Log.w(TAG, "no_connected_nodes count=${nodes.size}")
                Toast.makeText(this@MainActivity, R.string.error_no_phone, Toast.LENGTH_LONG).show()
                return@launch
            }
            val payload = AskPayload(
                requestId = requestId,
                query = query,
                sttLocale = sttLocaleTag,
            )
            pendingRequestIdState.value = requestId
            runCatching {
                messageClient.sendMessage(
                    nodeId,
                    VoiceBridgePaths.ASK,
                    VoiceBridgeCodec.encodeAsk(payload),
                ).await()
            }.onSuccess {
                Log.d(TAG, "phase=ask_sent requestId=$requestId")
            }.onFailure { e ->
                Log.e(TAG, "ask_send_failed requestId=$requestId", e)
                pendingRequestIdState.value = null
                Toast.makeText(this@MainActivity, R.string.error_send_failed, Toast.LENGTH_LONG).show()
            }
        }
    }

    internal fun clearPendingRequest() {
        pendingRequestIdState.value = null
    }

    internal fun peekPendingRequestId(): String? = pendingRequestIdState.value

    override fun onDestroy() {
        messageClient.removeListener(messageListener)
        textToSpeech?.stop()
        textToSpeech?.shutdown()
        textToSpeech = null
        super.onDestroy()
    }
}

private enum class SttLanguage(
    val localeTag: String,
) {
    ENGLISH("en-US"),
    ROMANIAN("ro-RO"),
}

@Composable
private fun VoiceBridgeScreen(
    activity: MainActivity,
    onSpeakClick: (localeTag: String) -> Unit,
    replyMessages: MutableSharedFlow<ReplyPayload>,
    onSpeakEnglishAnswer: (String) -> Unit,
) {
    val context = LocalContext.current
    val pendingRequestId by activity.pendingRequestId.collectAsStateWithLifecycle()

    var statusText by remember { mutableStateOf(context.getString(R.string.status_idle)) }

    val permissionLauncher = rememberLauncherForActivityResult(
        ActivityResultContracts.RequestPermission(),
    ) { granted ->
        if (!granted) {
            statusText = context.getString(R.string.error_mic_denied)
        }
    }

    LaunchedEffect(pendingRequestId) {
        if (pendingRequestId != null) {
            statusText = context.getString(R.string.status_waiting_phone)
        }
    }

    LaunchedEffect(replyMessages) {
        replyMessages.collectLatest { reply ->
            val pending = activity.peekPendingRequestId()
            if (pending == null || reply.requestId != pending) {
                Log.d(TAG, "reply_ignored expected=$pending got=${reply.requestId}")
                return@collectLatest
            }
            activity.clearPendingRequest()
            val answer = reply.answer
            if (!answer.isNullOrBlank()) {
                statusText = context.getString(R.string.status_speaking)
                onSpeakEnglishAnswer(answer)
                statusText = context.getString(R.string.status_idle)
            } else {
                val err = reply.message ?: reply.errorCode ?: context.getString(R.string.error_unknown)
                statusText = context.getString(R.string.status_error, err)
                Log.w(TAG, "reply_error requestId=${reply.requestId} code=${reply.errorCode} msg=$err")
            }
        }
    }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(MaterialTheme.colors.background),
    ) {
        TimeText()
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(horizontal = 8.dp, vertical = 36.dp),
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally,
        ) {
            Text(
                text = statusText,
                modifier = Modifier.fillMaxWidth(),
                textAlign = TextAlign.Center,
                color = MaterialTheme.colors.primary,
            )
            Spacer(modifier = Modifier.height(12.dp))
            Button(
                onClick = {
                    when {
                        ContextCompat.checkSelfPermission(
                            context,
                            Manifest.permission.RECORD_AUDIO,
                        ) != PackageManager.PERMISSION_GRANTED -> {
                            permissionLauncher.launch(Manifest.permission.RECORD_AUDIO)
                        }

                        else -> onSpeakClick(SttLanguage.ENGLISH.localeTag)
                    }
                },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text(stringResource(R.string.action_speak_english))
            }
            Spacer(modifier = Modifier.height(6.dp))
            Button(
                onClick = {
                    when {
                        ContextCompat.checkSelfPermission(
                            context,
                            Manifest.permission.RECORD_AUDIO,
                        ) != PackageManager.PERMISSION_GRANTED -> {
                            permissionLauncher.launch(Manifest.permission.RECORD_AUDIO)
                        }

                        else -> onSpeakClick(SttLanguage.ROMANIAN.localeTag)
                    }
                },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text(stringResource(R.string.action_speak_romanian))
            }
        }
    }
}

@Preview(device = WearDevices.SMALL_ROUND, showSystemUi = true)
@Composable
fun DefaultPreview() {
    VoiceBridgeTheme {
        Text("VoiceBridge preview")
    }
}
