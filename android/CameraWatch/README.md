# CameraWatch

Phone + Wear OS companion app: the phone captures the camera and streams a live preview to a paired Galaxy Watch (Wear OS).

## Modules

| Module | Device | APK |
|--------|--------|-----|
| `:app` | Phone | `app/build/outputs/apk/debug/app-debug.apk` |
| `:wear` | Watch | `wear/build/outputs/apk/debug/wear-debug.apk` |

## Build

```bash
export JAVA_HOME="/Applications/Android Studio.app/Contents/jbr/Contents/Home"
./gradlew :app:assembleDebug :wear:assembleDebug
```

If `adb` is not on your PATH:

```bash
export PATH="$HOME/Library/Android/sdk/platform-tools:$PATH"
```

Or call it with the full path:

```bash
~/Library/Android/sdk/platform-tools/adb
```

---

## Phone — USB debugging (cable)

1. On the phone, enable **Developer options** (tap **Build number** 7 times under About phone).
2. Enable **USB debugging** in Developer options.
3. Connect the phone to your Mac with a USB cable.
4. Unlock the phone and accept **Allow USB debugging?** if prompted.
5. Verify the phone appears:

```bash
adb devices -l
```

Example output:

```text
List of devices attached
RFCT513GXLX    device usb:... model:SM_G781B ...
```

6. Install the phone app:

```bash
adb -s PHONE_SERIAL install -r app/build/outputs/apk/debug/app-debug.apk
```

Replace `PHONE_SERIAL` with the id from `adb devices` (e.g. `RFCT513GXLX`).

If only one device is connected, you can omit `-s`:

```bash
adb install -r app/build/outputs/apk/debug/app-debug.apk
```

### Phone — wireless debugging (optional)

On Android 11+:

1. Same Wi‑Fi as the Mac.
2. **Developer options → Wireless debugging** → on.
3. **Pair device with pairing code** → note IP:pairing-port and code.
4. Pair, then connect:

```bash
adb pair PHONE_IP:PAIRING_PORT
# enter the 6-digit code when prompted

adb connect PHONE_IP:CONNECTION_PORT
adb devices -l
```

Use the **connection** port from the main Wireless debugging screen (not the pairing port).

---

## Watch — wireless ADB (Galaxy Watch / Wear OS)

The watch does **not** appear automatically when the phone is plugged in. You must connect the watch over Wi‑Fi ADB.

### 1. Enable debugging on the watch

1. **Settings → About watch → Software information** → tap **Build number** 7 times.
2. **Settings → Developer options**:
   - Turn on **ADB debugging**
   - Turn on **Wireless debugging** (or **Debug over Wi‑Fi**)
3. Open Wireless debugging and note:
   - **IP address & port** → used for `adb connect`
   - **Pair device with pairing code** → different port + 6-digit code → used for `adb pair`

Mac and watch must be on the **same Wi‑Fi** (avoid VPN / guest network / AP isolation).

### 2. Pair (first time, or after ports reset)

Leave the watch on the **pairing code** screen, then:

```bash
adb pair WATCH_IP:PAIRING_PORT
```

Enter the 6-digit code. You should see `Successfully paired...`.

### 3. Connect

Use the **other** IP:port from the main Wireless debugging screen:

```bash
adb connect WATCH_IP:CONNECTION_PORT
adb devices -l
```

You should see both phone and watch, for example:

```text
RFCT513GXLX              device
192.168.0.211:40437      device
```

### 4. Install the wear app

```bash
adb -s WATCH_IP:CONNECTION_PORT install -r wear/build/outputs/apk/debug/wear-debug.apk
```

Always target the watch serial. Installing the wear APK on the phone fails with:

`INSTALL_FAILED_MISSING_SHARED_LIBRARY: com.google.android.wearable`

### 5. If connect fails

```bash
# Check network reachability
ping -c 3 WATCH_IP

# Toggle Wireless debugging off/on on the watch (ports change), then pair + connect again
adb disconnect
adb pair WATCH_IP:NEW_PAIRING_PORT
adb connect WATCH_IP:NEW_CONNECTION_PORT
```

Quick test that the watch shell responds:

```bash
adb -s WATCH_IP:CONNECTION_PORT shell echo ok
```

---

## Run the apps

1. Open **CameraWatch** on the phone → grant **Camera** permission → leave it open.
2. Open **CameraWatch** on the watch → **Refresh** if needed → **Start**.
3. **Stop** on the watch (or leave the app) ends the stream.

---

## Android Studio tips

- Create separate run configurations: **app** (module `CameraWatch.app`) and **wear** (module `CameraWatch.wear`).
- For **wear**, select the **watch** device, not the phone.
- If the green **Run** button is greyed out / unclickable, use **File → Sync Project with Gradle Files** and wait for sync to finish. That often makes Run clickable again (alongside picking an online device in the device dropdown).
- Wireless watch links often drop; re-run `adb connect` and refresh devices in Studio.

### Logcat on the watch (zsh)

Quote the filter so zsh does not treat `*:E` as a glob:

```bash
adb -s WATCH_IP:CONNECTION_PORT logcat '*:E'
```

---

## Troubleshooting

| Symptom | Likely cause |
|---------|----------------|
| `adb: command not found` | Use `~/Library/Android/sdk/platform-tools/adb` or add it to `PATH` |
| Watch not in `adb devices` | Pair + connect over Wi‑Fi; phone USB does not expose the watch |
| `failed to connect` to watch | Used pairing port for connect; or network isolation — try phone hotspot |
| Wear APK fails with `MISSING_SHARED_LIBRARY` | Installed wear APK on the phone by mistake |
| Watch app closes after ~1s of streaming | Fixed by not recycling bitmaps still used by Compose; reinstall latest wear APK |
