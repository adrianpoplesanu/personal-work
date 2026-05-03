package ro.adrianus.voicebridge.shared

import kotlinx.serialization.json.Json

object VoiceBridgeCodec {
    val json: Json = Json {
        ignoreUnknownKeys = true
        isLenient = true
        encodeDefaults = true
    }

    fun encodeAsk(payload: AskPayload): ByteArray =
        json.encodeToString(AskPayload.serializer(), payload).encodeToByteArray()

    fun decodeAsk(bytes: ByteArray): AskPayload =
        json.decodeFromString(AskPayload.serializer(), bytes.decodeToString())

    fun encodeReply(payload: ReplyPayload): ByteArray =
        json.encodeToString(ReplyPayload.serializer(), payload).encodeToByteArray()

    fun decodeReply(bytes: ByteArray): ReplyPayload =
        json.decodeFromString(ReplyPayload.serializer(), bytes.decodeToString())

    fun encodeServerRequest(ask: AskPayload): String =
        json.encodeToString(
            ServerAskRequest.serializer(),
            ServerAskRequest(
                query = ask.query,
                requestId = ask.requestId,
                sttLocale = ask.sttLocale,
                version = ask.version,
            ),
        )

    fun decodeServerResponse(body: String): ServerAskResponse =
        json.decodeFromString(ServerAskResponse.serializer(), body)
}
