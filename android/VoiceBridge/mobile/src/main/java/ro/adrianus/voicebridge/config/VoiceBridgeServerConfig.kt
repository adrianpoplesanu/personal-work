package ro.adrianus.voicebridge.config

/**
 * Phone-side HTTP settings. Edit these values here in source; nothing is generated from Gradle.
 *
 * [BASE_URL]: scheme + host (+ optional port/path prefix). Trailing slash is optional; the client
 * appends `/v1/ask`.
 *
 * [API_KEY]: sent as `X-API-Key` when non-empty. Avoid committing real secrets to a public repo.
 *
 * [USE_MOCK]: when true, [ro.adrianus.voicebridge.network.BackendClient] skips HTTP and returns a mock
 * answer (handy without a server).
 */
object VoiceBridgeServerConfig {
    const val BASE_URL: String = "https://example.invalid/"
    const val API_KEY: String = ""
    const val USE_MOCK: Boolean = true
}
