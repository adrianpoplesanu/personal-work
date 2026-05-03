package ro.adrianus.voicebridge.shared

import kotlinx.serialization.Serializable

@Serializable
data class AskPayload(
    val version: Int = 1,
    val requestId: String,
    val query: String,
    val sttLocale: String,
)

@Serializable
data class ReplyPayload(
    val version: Int = 1,
    val requestId: String,
    val answer: String? = null,
    val errorCode: String? = null,
    val message: String? = null,
)

@Serializable
data class ServerAskRequest(
    val query: String,
    val requestId: String,
    val sttLocale: String,
    val version: Int = 1,
)

@Serializable
data class ServerAskResponse(
    val answer: String,
)
