package ro.adrianus.camerawatch.camera

import android.graphics.Bitmap
import android.graphics.Matrix
import androidx.camera.core.ImageProxy
import java.io.ByteArrayOutputStream

object FrameEncoder {
    const val MAX_EDGE_PX = 360
    const val JPEG_QUALITY = 50

    fun encodeRgbaToJpeg(imageProxy: ImageProxy): ByteArray? {
        val plane = imageProxy.planes.firstOrNull() ?: return null
        val buffer = plane.buffer
        val pixelStride = plane.pixelStride
        val rowStride = plane.rowStride
        val width = imageProxy.width
        val height = imageProxy.height

        val bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888)
        buffer.rewind()
        if (pixelStride == 4 && rowStride == width * 4) {
            bitmap.copyPixelsFromBuffer(buffer)
        } else {
            val row = ByteArray(rowStride)
            val argb = IntArray(width * height)
            var index = 0
            for (y in 0 until height) {
                buffer.get(row, 0, rowStride.coerceAtMost(buffer.remaining()))
                var col = 0
                while (col < width) {
                    val offset = col * pixelStride
                    val r = row[offset].toInt() and 0xFF
                    val g = row[offset + 1].toInt() and 0xFF
                    val b = row[offset + 2].toInt() and 0xFF
                    val a = if (pixelStride >= 4) row[offset + 3].toInt() and 0xFF else 0xFF
                    argb[index++] = (a shl 24) or (r shl 16) or (g shl 8) or b
                    col++
                }
            }
            bitmap.setPixels(argb, 0, width, 0, 0, width, height)
        }

        val rotated = rotateBitmap(bitmap, imageProxy.imageInfo.rotationDegrees.toFloat())
        if (rotated !== bitmap) {
            bitmap.recycle()
        }
        val scaled = scaleToMaxEdge(rotated, MAX_EDGE_PX)
        if (scaled !== rotated) {
            rotated.recycle()
        }
        val out = ByteArrayOutputStream()
        val ok = scaled.compress(Bitmap.CompressFormat.JPEG, JPEG_QUALITY, out)
        scaled.recycle()
        return if (ok) out.toByteArray() else null
    }

    private fun scaleToMaxEdge(bitmap: Bitmap, maxEdge: Int): Bitmap {
        val longest = maxOf(bitmap.width, bitmap.height)
        if (longest <= maxEdge) return bitmap
        val scale = maxEdge.toFloat() / longest
        val width = (bitmap.width * scale).toInt().coerceAtLeast(1)
        val height = (bitmap.height * scale).toInt().coerceAtLeast(1)
        return Bitmap.createScaledBitmap(bitmap, width, height, true)
    }

    private fun rotateBitmap(bitmap: Bitmap, degrees: Float): Bitmap {
        if (degrees == 0f) return bitmap
        val matrix = Matrix().apply { postRotate(degrees) }
        return Bitmap.createBitmap(bitmap, 0, 0, bitmap.width, bitmap.height, matrix, true)
    }
}
