package ro.adrianus.camerawatch.shared

import org.junit.Assert.assertArrayEquals
import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Test
import java.io.ByteArrayInputStream
import java.io.ByteArrayOutputStream

class FrameProtocolTest {
    @Test
    fun writeAndReadRoundTrip() {
        val payload = byteArrayOf(1, 2, 3, 4, 5, 9)
        val out = ByteArrayOutputStream()
        FrameProtocol.writeFrame(out, payload, seq = 42, timestampMs = 123456789L)

        val result = FrameProtocol.readFrame(ByteArrayInputStream(out.toByteArray()))
        assertNotNull(result)
        val (header, bytes) = result!!
        assertEquals(payload.size, header.length)
        assertEquals(42, header.seq)
        assertEquals(123456789L, header.timestampMs)
        assertArrayEquals(payload, bytes)
    }
}
