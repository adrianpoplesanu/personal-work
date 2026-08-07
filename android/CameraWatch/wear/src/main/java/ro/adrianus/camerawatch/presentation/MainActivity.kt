package ro.adrianus.camerawatch.presentation

import android.graphics.Bitmap
import android.os.Bundle
import android.view.WindowManager
import androidx.activity.ComponentActivity
import androidx.activity.compose.LocalActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.asImageBitmap
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.core.splashscreen.SplashScreen.Companion.installSplashScreen
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.LifecycleEventObserver
import androidx.lifecycle.compose.LocalLifecycleOwner
import androidx.wear.compose.material.Chip
import androidx.wear.compose.material.MaterialTheme
import androidx.wear.compose.material.Text
import androidx.wear.compose.material.TimeText
import ro.adrianus.camerawatch.presentation.theme.CameraWatchTheme
import ro.adrianus.camerawatch.wear.WatchFeedStatus
import ro.adrianus.camerawatch.wear.WatchWearBridge

class MainActivity : ComponentActivity() {
    private lateinit var wearBridge: WatchWearBridge

    override fun onCreate(savedInstanceState: Bundle?) {
        installSplashScreen()
        super.onCreate(savedInstanceState)
        setTheme(android.R.style.Theme_DeviceDefault)

        wearBridge = WatchWearBridge(applicationContext)
        wearBridge.start()

        setContent {
            CameraWatchTheme {
                CameraFeedScreen(wearBridge = wearBridge)
            }
        }
    }

    override fun onStop() {
        wearBridge.stopStreaming()
        window.clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        super.onStop()
    }

    override fun onDestroy() {
        wearBridge.stop()
        super.onDestroy()
    }
}

@Composable
fun CameraFeedScreen(wearBridge: WatchWearBridge) {
    val status by wearBridge.status.collectAsState()
    val statusMessage by wearBridge.statusMessage.collectAsState()
    val frame by wearBridge.frame.collectAsState()
    val activity = LocalActivity.current
    val lifecycleOwner = LocalLifecycleOwner.current

    DisposableEffect(status) {
        if (status == WatchFeedStatus.Streaming) {
            activity?.window?.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        } else {
            activity?.window?.clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        }
        onDispose { }
    }

    DisposableEffect(lifecycleOwner) {
        val observer = LifecycleEventObserver { _, event ->
            if (event == Lifecycle.Event.ON_STOP) {
                wearBridge.stopStreaming()
            }
        }
        lifecycleOwner.lifecycle.addObserver(observer)
        onDispose { lifecycleOwner.lifecycle.removeObserver(observer) }
    }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(MaterialTheme.colors.background),
    ) {
        TimeText()

        when {
            status == WatchFeedStatus.Streaming && frame != null -> {
                StreamingContent(
                    bitmap = frame!!,
                    onStop = { wearBridge.stopStreaming() },
                )
            }
            else -> {
                IdleContent(
                    status = status,
                    statusMessage = statusMessage,
                    onStart = {
                        wearBridge.refreshPhoneNode()
                        wearBridge.startStreaming()
                    },
                    onRefresh = { wearBridge.refreshPhoneNode() },
                    canStart = status == WatchFeedStatus.Ready ||
                        status == WatchFeedStatus.Error ||
                        status == WatchFeedStatus.Disconnected,
                )
            }
        }
    }
}

@Composable
private fun StreamingContent(
    bitmap: Bitmap,
    onStop: () -> Unit,
) {
    val imageBitmap = remember(bitmap) { bitmap.asImageBitmap() }
    Box(modifier = Modifier.fillMaxSize()) {
        Image(
            bitmap = imageBitmap,
            contentDescription = "Phone camera feed",
            modifier = Modifier.fillMaxSize(),
            contentScale = ContentScale.Crop,
        )
        Chip(
            onClick = onStop,
            modifier = Modifier
                .align(Alignment.BottomCenter)
                .fillMaxWidth(0.7f)
                .padding(bottom = 12.dp),
            shape = RoundedCornerShape(50),
            label = { Text("Stop") },
        )
    }
}

@Composable
private fun IdleContent(
    status: WatchFeedStatus,
    statusMessage: String,
    onStart: () -> Unit,
    onRefresh: () -> Unit,
    canStart: Boolean,
) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(horizontal = 16.dp),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Text(
            text = when (status) {
                WatchFeedStatus.Disconnected -> "No phone"
                WatchFeedStatus.Ready -> "Ready"
                WatchFeedStatus.Connecting -> "Connecting"
                WatchFeedStatus.Streaming -> "Streaming"
                WatchFeedStatus.Error -> "Error"
            },
            style = MaterialTheme.typography.title3,
            textAlign = TextAlign.Center,
        )
        Spacer(modifier = Modifier.height(4.dp))
        Text(
            text = statusMessage,
            style = MaterialTheme.typography.body2,
            textAlign = TextAlign.Center,
            modifier = Modifier.fillMaxWidth(),
        )
        Spacer(modifier = Modifier.height(12.dp))
        if (canStart) {
            Chip(
                onClick = onStart,
                modifier = Modifier.fillMaxWidth(0.85f),
                shape = RoundedCornerShape(50),
                label = { Text("Start") },
            )
            Spacer(modifier = Modifier.height(8.dp))
            Chip(
                onClick = onRefresh,
                modifier = Modifier.fillMaxWidth(0.85f),
                shape = RoundedCornerShape(50),
                label = { Text("Refresh") },
            )
        }
    }
}
