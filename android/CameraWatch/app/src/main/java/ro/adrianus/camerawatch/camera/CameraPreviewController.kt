package ro.adrianus.camerawatch.camera

import android.content.Context
import android.util.Log
import android.util.Size
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.Preview
import androidx.camera.core.resolutionselector.AspectRatioStrategy
import androidx.camera.core.resolutionselector.ResolutionSelector
import androidx.camera.core.resolutionselector.ResolutionStrategy
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.view.PreviewView
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import java.util.concurrent.atomic.AtomicBoolean
import kotlin.coroutines.resume
import kotlin.coroutines.resumeWithException
import kotlin.coroutines.suspendCoroutine

class CameraPreviewController(
    private val context: Context,
) {
    private val analysisExecutor: ExecutorService = Executors.newSingleThreadExecutor()
    private var cameraProvider: ProcessCameraProvider? = null
    private var imageAnalysis: ImageAnalysis? = null
    private val busy = AtomicBoolean(false)
    private var frameCallback: ((ByteArray) -> Unit)? = null
    private var lastSentMs = 0L
    private val minFrameIntervalMs = 1000L / TARGET_FPS

    fun setFrameCallback(callback: ((ByteArray) -> Unit)?) {
        frameCallback = callback
    }

    suspend fun start(
        lifecycleOwner: LifecycleOwner,
        previewView: PreviewView,
    ) {
        val provider = getCameraProvider()
        cameraProvider = provider
        provider.unbindAll()

        val preview = Preview.Builder()
            .build()
            .also { it.surfaceProvider = previewView.surfaceProvider }

        val resolutionSelector = ResolutionSelector.Builder()
            .setAspectRatioStrategy(AspectRatioStrategy.RATIO_4_3_FALLBACK_AUTO_STRATEGY)
            .setResolutionStrategy(
                ResolutionStrategy(
                    Size(640, 480),
                    ResolutionStrategy.FALLBACK_RULE_CLOSEST_LOWER_THEN_HIGHER,
                ),
            )
            .build()

        val analysis = ImageAnalysis.Builder()
            .setResolutionSelector(resolutionSelector)
            .setBackpressureStrategy(ImageAnalysis.STRATEGY_KEEP_ONLY_LATEST)
            .setOutputImageFormat(ImageAnalysis.OUTPUT_IMAGE_FORMAT_RGBA_8888)
            .build()
            .also { analyzer ->
                analyzer.setAnalyzer(analysisExecutor) { imageProxy ->
                    try {
                        val now = System.currentTimeMillis()
                        if (now - lastSentMs < minFrameIntervalMs) {
                            return@setAnalyzer
                        }
                        if (!busy.compareAndSet(false, true)) {
                            return@setAnalyzer
                        }
                        try {
                            val jpeg = FrameEncoder.encodeRgbaToJpeg(imageProxy)
                            if (jpeg != null) {
                                lastSentMs = now
                                frameCallback?.invoke(jpeg)
                            }
                        } finally {
                            busy.set(false)
                        }
                    } catch (t: Throwable) {
                        Log.e(TAG, "Frame encode failed", t)
                        busy.set(false)
                    } finally {
                        imageProxy.close()
                    }
                }
            }
        imageAnalysis = analysis

        provider.bindToLifecycle(
            lifecycleOwner,
            CameraSelector.DEFAULT_BACK_CAMERA,
            preview,
            analysis,
        )
    }

    fun stop() {
        frameCallback = null
        try {
            cameraProvider?.unbindAll()
        } catch (t: Throwable) {
            Log.w(TAG, "unbindAll failed", t)
        }
        imageAnalysis = null
    }

    fun release() {
        stop()
        analysisExecutor.shutdown()
    }

    private suspend fun getCameraProvider(): ProcessCameraProvider =
        suspendCoroutine { cont ->
            val future = ProcessCameraProvider.getInstance(context)
            future.addListener(
                {
                    try {
                        cont.resume(future.get())
                    } catch (t: Throwable) {
                        cont.resumeWithException(t)
                    }
                },
                ContextCompat.getMainExecutor(context),
            )
        }

    companion object {
        private const val TAG = "CameraPreviewCtrl"
        private const val TARGET_FPS = 7
    }
}
