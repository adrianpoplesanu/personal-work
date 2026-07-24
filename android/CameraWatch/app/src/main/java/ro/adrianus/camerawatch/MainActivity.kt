package ro.adrianus.camerawatch

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.view.ViewGroup
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.camera.view.PreviewView
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.compose.LocalLifecycleOwner
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView
import androidx.core.content.ContextCompat
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import ro.adrianus.camerawatch.camera.CameraPreviewController
import ro.adrianus.camerawatch.ui.theme.CameraWatchTheme
import ro.adrianus.camerawatch.wear.PhoneStreamStatus
import ro.adrianus.camerawatch.wear.PhoneWearBridge

class MainActivity : ComponentActivity() {
    private lateinit var cameraController: CameraPreviewController
    private lateinit var wearBridge: PhoneWearBridge

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        cameraController = CameraPreviewController(applicationContext)
        wearBridge = PhoneWearBridge(
            context = applicationContext,
            onStartRequested = { watchNodeId ->
                lifecycleScope.launch {
                    try {
                        wearBridge.openStreamToWatch(watchNodeId)
                        cameraController.setFrameCallback { jpeg ->
                            lifecycleScope.launch(Dispatchers.IO) {
                                wearBridge.sendFrame(jpeg)
                            }
                        }
                    } catch (_: Throwable) {
                        cameraController.setFrameCallback(null)
                    }
                }
            },
            onStopRequested = {
                lifecycleScope.launch {
                    cameraController.setFrameCallback(null)
                    wearBridge.closeStream()
                }
            },
        )
        wearBridge.start()

        setContent {
            CameraWatchTheme {
                PhoneCameraScreen(
                    cameraController = cameraController,
                    wearBridge = wearBridge,
                )
            }
        }
    }

    override fun onDestroy() {
        cameraController.setFrameCallback(null)
        wearBridge.stop()
        cameraController.release()
        super.onDestroy()
    }
}

@Composable
private fun PhoneCameraScreen(
    cameraController: CameraPreviewController,
    wearBridge: PhoneWearBridge,
) {
    val context = LocalContext.current
    val lifecycleOwner = LocalLifecycleOwner.current
    val status by wearBridge.status.collectAsState()
    val statusMessage by wearBridge.statusMessage.collectAsState()

    var hasCameraPermission by remember {
        mutableStateOf(
            ContextCompat.checkSelfPermission(context, Manifest.permission.CAMERA) ==
                PackageManager.PERMISSION_GRANTED,
        )
    }
    var previewView by remember { mutableStateOf<PreviewView?>(null) }
    var cameraError by remember { mutableStateOf<String?>(null) }

    val permissionLauncher = rememberLauncherForActivityResult(
        ActivityResultContracts.RequestPermission(),
    ) { granted ->
        hasCameraPermission = granted
    }

    LaunchedEffect(hasCameraPermission, previewView) {
        val view = previewView ?: return@LaunchedEffect
        if (!hasCameraPermission) return@LaunchedEffect
        try {
            cameraController.start(lifecycleOwner, view)
            cameraError = null
        } catch (t: Throwable) {
            cameraError = t.message ?: "Camera failed to start"
        }
    }

    DisposableEffect(Unit) {
        onDispose {
            cameraController.stop()
        }
    }

    Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding),
        ) {
            Box(
                modifier = Modifier
                    .weight(1f)
                    .fillMaxWidth(),
            ) {
                if (hasCameraPermission) {
                    AndroidView(
                        factory = { ctx ->
                            PreviewView(ctx).also { pv ->
                                pv.layoutParams = ViewGroup.LayoutParams(
                                    ViewGroup.LayoutParams.MATCH_PARENT,
                                    ViewGroup.LayoutParams.MATCH_PARENT,
                                )
                                pv.scaleType = PreviewView.ScaleType.FILL_CENTER
                                previewView = pv
                            }
                        },
                        modifier = Modifier.fillMaxSize(),
                    )
                } else {
                    Column(
                        modifier = Modifier
                            .fillMaxSize()
                            .padding(24.dp),
                        horizontalAlignment = Alignment.CenterHorizontally,
                    ) {
                        Spacer(modifier = Modifier.height(48.dp))
                        Text("Camera permission is required to stream to your watch.")
                        Spacer(modifier = Modifier.height(16.dp))
                        Button(onClick = { permissionLauncher.launch(Manifest.permission.CAMERA) }) {
                            Text("Grant camera permission")
                        }
                    }
                }
            }

            Surface(
                tonalElevation = 2.dp,
                modifier = Modifier.fillMaxWidth(),
            ) {
                Column(modifier = Modifier.padding(16.dp)) {
                    Text(
                        text = when (status) {
                            PhoneStreamStatus.Idle -> "Idle"
                            PhoneStreamStatus.WaitingForWatch -> "Waiting for watch"
                            PhoneStreamStatus.Streaming -> "Streaming"
                            PhoneStreamStatus.Error -> "Error"
                        },
                        style = MaterialTheme.typography.titleMedium,
                    )
                    Text(
                        text = statusMessage,
                        style = MaterialTheme.typography.bodyMedium,
                    )
                    cameraError?.let {
                        Text(
                            text = it,
                            color = MaterialTheme.colorScheme.error,
                            style = MaterialTheme.typography.bodySmall,
                        )
                    }
                }
            }
        }
    }
}
