package ro.adrianus.soundchecker1.presentation.services

import android.app.Service
import android.content.Intent
import android.os.Handler
import android.os.IBinder
import android.os.Vibrator
import android.util.Log

class MetronomeService : Service() {

    private val handler = Handler()
    private lateinit var vibrator: Vibrator
    private var bpm: Int = 60
    private var interval: Long = 60000 / 60 // default 60 bpm

    private val metronomeRunnable = object : Runnable {
        override fun run() {
            Log.d("metronome_service", "Vibrating at BPM: $bpm")
            if (vibrator.hasVibrator()) {
                vibrator.vibrate(100)
            } else {
                Log.d("metronome_service", "No vibrator found on the device")
            }
            handler.postDelayed(this, interval)
        }
    }

    override fun onCreate() {
        super.onCreate()
        vibrator = getSystemService(VIBRATOR_SERVICE) as Vibrator
        handler.post(metronomeRunnable)
    }

    override fun onDestroy() {
        super.onDestroy()
        handler.removeCallbacks(metronomeRunnable)
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        Log.d("metronome_service", "setting up vibration runnables")
        // Update the interval if a new BPM is provided
        intent?.let {
            val bpm = it.getIntExtra("BPM", 60) // Default BPM is 60
            interval = 60000L / bpm
        }
        handler.removeCallbacks(metronomeRunnable)
        handler.post(metronomeRunnable)
        return START_STICKY
    }

    override fun onBind(intent: Intent?): IBinder? {
        return null
    }
}