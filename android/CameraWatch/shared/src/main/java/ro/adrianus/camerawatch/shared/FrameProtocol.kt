package ro.adrianus.camerawatch.shared

import java.io.DataInputStream
import java.io.DataOutputStream
import java.io.EOFException
import java.io.IOException
import java.io.InputStream
import java.io.OutputStream

object FrameProtocol {
    const val MAGIC = 0xCAFEF00D.toInt()
    const val HEADER_SIZE = 4 + 4 + 4 + 8 // magic + length + seq + timestampMs
    const val MAX_FRAME_BYTES = 512 * 1024

    data class FrameHeader(
        val length: Int,
        val seq: Int,
        val timestampMs: Long,
    )

    fun writeFrame(
        output: OutputStream,
        jpegBytes: ByteArray,
        seq: Int,
        timestampMs: Long = System.currentTimeMillis(),
    ) {
        val dataOut = DataOutputStream(output)
        dataOut.writeInt(MAGIC)
        dataOut.writeInt(jpegBytes.size)
        dataOut.writeInt(seq)
        dataOut.writeLong(timestampMs)
        dataOut.write(jpegBytes)
        dataOut.flush()
    }

    fun readFrame(input: InputStream): Pair<FrameHeader, ByteArray>? {
        val dataIn = DataInputStream(input)
        return try {
            val magic = dataIn.readInt()
            if (magic != MAGIC) {
                throw IOException("Invalid frame magic: 0x${Integer.toHexString(magic)}")
            }
            val length = dataIn.readInt()
            if (length <= 0 || length > MAX_FRAME_BYTES) {
                throw IOException("Invalid frame length: $length")
            }
            val seq = dataIn.readInt()
            val timestampMs = dataIn.readLong()
            val jpegBytes = ByteArray(length)
            dataIn.readFully(jpegBytes)
            FrameHeader(length, seq, timestampMs) to jpegBytes
        } catch (_: EOFException) {
            null
        }
    }
}
