package ro.adrianus.voicebridge.network

import android.util.Log
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.OkHttpClient
import okhttp3.Request
import okhttp3.RequestBody.Companion.toRequestBody
import ro.adrianus.voicebridge.shared.AskPayload
import ro.adrianus.voicebridge.shared.ReplyPayload
import ro.adrianus.voicebridge.shared.VoiceBridgeCodec
import java.util.concurrent.TimeUnit

class BackendClient(
    private val baseUrl: String,
    private val apiKey: String,
    private val useMock: Boolean,
) {
    private val client = OkHttpClient.Builder()
        .connectTimeout(15, TimeUnit.SECONDS)
        .readTimeout(60, TimeUnit.SECONDS)
        .writeTimeout(30, TimeUnit.SECONDS)
        .build()

    private val jsonMediaType = "application/json; charset=utf-8".toMediaType()

    fun ask(ask: AskPayload): ReplyPayload {
        val rid = ask.requestId
        if (useMock) {
            logPhase(rid, "mock_skip_http")
            Log.d(TAG, "queryLen=${ask.query.length} sttLocale=${ask.sttLocale}")
            val preview = ask.query.take(120)
            return ReplyPayload(
                requestId = rid,
                answer = "Mock server (no HTTP). You said: $preview",
            )
        }

        val url = baseUrl.trimEnd('/') + "/v1/ask"
        logPhase(rid, "http_post_start")
        Log.d(TAG, "http_url=$url")

        val bodyJson = VoiceBridgeCodec.encodeServerRequest(ask)
        val requestBuilder = Request.Builder()
            .url(url)
            .post(bodyJson.toRequestBody(jsonMediaType))

        if (apiKey.isNotEmpty()) {
            requestBuilder.header(HEADER_API_KEY, apiKey)
        }

        return try {
            client.newCall(requestBuilder.build()).execute().use { response ->
                val responseBody = response.body?.string().orEmpty()
                logPhase(rid, "http_done status=${response.code} bodyLen=${responseBody.length}")
                if (!response.isSuccessful) {
                    return ReplyPayload(
                        requestId = rid,
                        errorCode = "http_${response.code}",
                        message = responseBody.take(200).ifEmpty { response.message },
                    )
                }
                val parsed = runCatching { VoiceBridgeCodec.decodeServerResponse(responseBody) }.getOrElse { e ->
                    Log.e(TAG, "parse_fail requestId=$rid", e)
                    return ReplyPayload(
                        requestId = rid,
                        errorCode = "parse_error",
                        message = e.message ?: "parse_error",
                    )
                }
                ReplyPayload(requestId = rid, answer = parsed.answer)
            }
        } catch (e: Exception) {
            Log.e(TAG, "http_fail requestId=$rid", e)
            ReplyPayload(
                requestId = rid,
                errorCode = "network",
                message = e.message ?: "network_error",
            )
        }
    }

    private fun logPhase(requestId: String, phase: String) {
        Log.d(TAG, "phase=$phase requestId=$requestId")
    }

    companion object {
        private const val TAG = "VoiceBridge"
        const val HEADER_API_KEY: String = "X-API-Key"
    }
}
