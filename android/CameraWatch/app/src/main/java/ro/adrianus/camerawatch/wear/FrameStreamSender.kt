package ro.adrianus.camerawatch.wear

import android.util.Log
import com.google.android.gms.wearable.ChannelClient
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock
import kotlinx.coroutines.withContext
import ro.adrianus.camerawatch.shared.FrameProtocol
import java.io.OutputStream
import java.util.concurrent.atomic.AtomicBoolean
import java.util.concurrent.atomic.AtomicInteger

class FrameStreamSender {
    private val sendMutex = Mutex()
    private val sending = AtomicBoolean(false)
    private val sequence = AtomicInteger(0)
    private var outputStream: OutputStream? = null
    private var channel: ChannelClient.Channel? = null

    fun isOpen(): Boolean = outputStream != null

    suspend fun open(stream: OutputStream, openChannel: ChannelClient.Channel) {
        close()
        outputStream = stream
        channel = openChannel
        sequence.set(0)
    }

    /**
     * Attempts to send a frame. Returns false if busy or closed (caller should drop).
     */
    suspend fun trySend(jpegBytes: ByteArray): Boolean {
        if (outputStream == null) return false
        if (!sending.compareAndSet(false, true)) return false
        return try {
            sendMutex.withLock {
                val stream = outputStream ?: return@withLock false
                withContext(Dispatchers.IO) {
                    FrameProtocol.writeFrame(
                        output = stream,
                        jpegBytes = jpegBytes,
                        seq = sequence.getAndIncrement(),
                    )
                }
                true
            }
        } catch (t: Throwable) {
            Log.e(TAG, "Failed to write frame", t)
            false
        } finally {
            sending.set(false)
        }
    }

    suspend fun close() {
        sendMutex.withLock {
            try {
                outputStream?.close()
            } catch (_: Throwable) {
            }
            outputStream = null
            channel = null
        }
        sending.set(false)
    }

    fun currentChannel(): ChannelClient.Channel? = channel

    companion object {
        private const val TAG = "FrameStreamSender"
    }
}
