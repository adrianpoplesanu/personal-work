# VoiceBridge

Wear OS companion + phone app: watch captures speech, sends text to the phone over the Wearable Data Layer, the phone calls your HTTP backend, and the answer returns to the watch for English text-to-speech.

See `docs/PLAN.md` for architecture and phased work.

## Phone / HTTP configuration

Edit **`mobile/src/main/java/ro/adrianus/voicebridge/config/VoiceBridgeServerConfig.kt`** in place:

- **`BASE_URL`** — your API base; the client appends `/v1/ask`.
- **`API_KEY`** — sent as `X-API-Key` when non-empty.
- **`USE_MOCK`** — when `true`, no HTTP is performed and a mock answer is returned.

No Gradle-generated `BuildConfig` is used for these settings.

### Phone module packages (`ro.adrianus.voicebridge`)

| Package | Role |
|---------|------|
| `config` | `VoiceBridgeServerConfig` — base URL, API key, mock flag |
| `network` | `BackendClient` — HTTP to `/v1/ask` |
| `service` | `VoiceBridgeListenerService` — Wear messages in, replies out |
| *(root)* | `MainActivity` — phone UI shell |
