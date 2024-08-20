/* While this template provides a good starting point for using Wear Compose, you can always
 * take a look at https://github.com/android/wear-os-samples/tree/main/ComposeStarter and
 * https://github.com/android/wear-os-samples/tree/main/ComposeAdvanced to find the most up to date
 * changes to the libraries and their usages.
 */

package ro.adrianus.soundchecker1.presentation

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.os.PowerManager
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.activity.ComponentActivity
import ro.adrianus.soundchecker1.R
import ro.adrianus.soundchecker1.presentation.services.MetronomeService

class MainActivity : ComponentActivity() {

    private var tempos = setOf(40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 63, 66, 69, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 126, 132, 138, 144, 152, 160, 168, 176, 184, 192, 200, 208)
    private var index = 10
    private lateinit var bpmTextView: TextView
    private lateinit var startMetronomeButton: Button
    private lateinit var stopMetronomeButton: Button
    private lateinit var wakeLock: PowerManager.WakeLock

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val powerManager = getSystemService(Context.POWER_SERVICE) as PowerManager
        wakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "SoundChecker1::MetronomeWakelock")
        wakeLock.acquire()

        bpmTextView = findViewById(R.id.bpmTextView)
        val increaseBpmButton: Button = findViewById(R.id.increaseBpmButton)
        val decreaseBpmButton: Button = findViewById(R.id.decreaseBpmButton)
        startMetronomeButton = findViewById(R.id.startMetronomeButton)
        stopMetronomeButton = findViewById(R.id.stopMetronomeButton)

        increaseBpmButton.setOnClickListener {
            index++
            if (index >= tempos.size) {
                index = tempos.size - 1
            }
            updateBpm()
        }

        decreaseBpmButton.setOnClickListener {
            index--
            if (index < 0) {
                index = 0
            }
            updateBpm()
        }

        startMetronomeButton.setOnClickListener {
            startMetronomeService()
        }

        stopMetronomeButton.setOnClickListener {
            stopMetronomeService()
        }
    }

    private fun updateBpm() {
        val tempo = tempos.elementAt(index)
        bpmTextView.text = "BPM: $tempo"
        stopMetronomeService()
    }

    private fun startMetronomeService() {
        Log.d("main_activity", "starting metronome service")
        val intent = Intent(this, MetronomeService::class.java).apply {
            putExtra("BPM", tempos.elementAt(index))
        }
        startService(intent)
        toggleButtons(isRunning = true)
    }

    private fun stopMetronomeService() {
        stopService(Intent(this, MetronomeService::class.java))
        toggleButtons(isRunning = false)
    }

    private fun toggleButtons(isRunning: Boolean) {
        startMetronomeButton.visibility = if (isRunning) Button.GONE else Button.VISIBLE
        stopMetronomeButton.visibility = if (isRunning) Button.VISIBLE else Button.GONE
    }

    override fun onPause() {
        super.onPause()
        stopService(Intent(this, MetronomeService::class.java))
        toggleButtons(isRunning = false)
    }

    override fun onDestroy() {
        super.onDestroy()
        stopService(Intent(this, MetronomeService::class.java))
        if (wakeLock.isHeld) {
            wakeLock.release()
        }
    }
}
