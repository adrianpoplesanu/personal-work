package ro.adrianus.camerawatch.wear

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.util.Log
import com.google.android.gms.wearable.ChannelClient
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.isActive
import kotlinx.coroutines.launch
import ro.adrianus.camerawatch.shared.FrameProtocol
import java.io.InputStream

class FrameStreamReceiver(
    private val scope: CoroutineScope,
) {
    private val _frame = MutableStateFlow<Bitmap?>(null)
    val frame: StateFlow<Bitmap?> = _frame.asStateFlow()

    private var readJob: Job? = null
    private var inputStream: InputStream? = null
    private var channel: ChannelClient.Channel? = null

    fun start(stream: InputStream, openChannel: ChannelClient.Channel) {
        stop()
        inputStream = stream
        channel = openChannel
        readJob = scope.launch(Dispatchers.IO) {
            try {
                while (isActive) {
                    val result = FrameProtocol.readFrame(stream) ?: break
                    val (_, jpegBytes) = result
                    val decoded = BitmapFactory.decodeByteArray(jpegBytes, 0, jpegBytes.size)
                        ?: continue
                    // Do not recycle bitmaps still referenced by Compose (asImageBitmap shares
                    // the buffer); recycling causes "trying to use a recycled bitmap" crashes.
                    _frame.value = decoded
                }
            } catch (t: Throwable) {
                if (isActive) {
                    Log.e(TAG, "Frame receive failed", t)
                }
            }
        }
    }

    fun stop() {
        readJob?.cancel()
        readJob = null
        try {
            inputStream?.close()
        } catch (_: Throwable) {
        }
        inputStream = null
        channel = null
        _frame.value = null
    }

    fun currentChannel(): ChannelClient.Channel? = channel

    companion object {
        private const val TAG = "FrameStreamReceiver"
    }
}
