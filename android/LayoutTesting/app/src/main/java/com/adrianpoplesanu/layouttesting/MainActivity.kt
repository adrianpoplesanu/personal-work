package com.adrianpoplesanu.layouttesting

import android.content.Intent
import android.graphics.Color
import android.os.Bundle
import android.util.Log
import android.view.ViewGroup
import android.widget.Button
import android.widget.LinearLayout
import android.widget.RelativeLayout
import android.widget.ScrollView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // asta ascunde title bar-ul
        //getSupportActionBar()?.hide()

        setContentView(R.layout.activity_main)
        Log.d("LayoutTesting Debug", "main activity loaded")

        val scrollContent = findViewById<LinearLayout>(R.id.scrollContent)
        val scrollLayout = findViewById<ScrollView>(R.id.scrollLayout)

        val text_view_dinamic = TextView(this)
        text_view_dinamic.textSize = 30f
        text_view_dinamic.text = "Message received"
        text_view_dinamic.setBackgroundResource(R.drawable.received_message)
        //text_view_dinamic.id = R.id.test
        //text_view_dinamic
        //ll_main_layout.addView(text_view_dinamic)
        //text_view_dinamic.isCursorVisible = true
        scrollContent?.addView(text_view_dinamic)

        val button_dinamic = Button(this)
        val params = RelativeLayout.LayoutParams(
            ViewGroup.LayoutParams.WRAP_CONTENT,
            ViewGroup.LayoutParams.WRAP_CONTENT
        )
        //params.addRule(RelativeLayout.BELOW, R.id.test)
        params.addRule(RelativeLayout.BELOW)
        //params.addRule(RelativeLayout.BELOW, R.id.textView) // asta nu merge
        button_dinamic.layoutParams = params
        button_dinamic.text = "Press me!!!"
        button_dinamic.setBackgroundResource(R.drawable.button_face)
        button_dinamic.setOnClickListener {
            Log.d("LayoutTesting Debug", "button clicked!!!")
        }
        scrollContent?.addView(button_dinamic)

        val text_view_dinamic2 = TextView(this)
        text_view_dinamic2.textSize = 30f
        text_view_dinamic2.text = "Message received2"
        text_view_dinamic2.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic2.setTextColor(Color.parseColor("#0aad3f"))
        //text_view_dinamic2.layoutParams = params // s-ar putea sa nu am nevoie de asta
        scrollContent?.addView(text_view_dinamic2)

        val text_view_dinamic3 = TextView(this)
        text_view_dinamic3.textSize = 30f
        text_view_dinamic3.text = "sdfghsd dfg hsdfjh2"
        text_view_dinamic3.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic3.layoutParams = params
        scrollContent?.addView(text_view_dinamic3)

        val text_view_dinamic4 = TextView(this)
        text_view_dinamic4.textSize = 30f
        text_view_dinamic4.text = "asdfuiasd dfhgj sdhsdfkjhg "
        text_view_dinamic4.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic4.layoutParams = params
        scrollContent?.addView(text_view_dinamic4)

        val text_view_dinamic5 = TextView(this)
        text_view_dinamic5.textSize = 30f
        text_view_dinamic5.text = "asertertrtg fd8bfogbi yt"
        text_view_dinamic5.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic5.layoutParams = params
        scrollContent?.addView(text_view_dinamic5)

        val text_view_dinamic6 = TextView(this)
        text_view_dinamic6.textSize = 30f
        text_view_dinamic6.text = "ertg fhg fgh yh rth"
        text_view_dinamic6.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic6.layoutParams = params
        scrollContent?.addView(text_view_dinamic6)

        val text_view_dinamic7 = TextView(this)
        text_view_dinamic7.textSize = 30f
        text_view_dinamic7.text = "fghf ytjh tyh wer g"
        text_view_dinamic7.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic7.layoutParams = params
        scrollContent?.addView(text_view_dinamic7)

        val text_view_dinamic8 = TextView(this)
        text_view_dinamic8.textSize = 30f
        text_view_dinamic8.text = "neata!!!"
        text_view_dinamic8.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic8.layoutParams = params
        scrollContent?.addView(text_view_dinamic8)

        val text_view_dinamic9 = TextView(this)
        text_view_dinamic9.textSize = 30f
        text_view_dinamic9.text = "dexiciul"
        text_view_dinamic9.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic9.layoutParams = params
        scrollContent?.addView(text_view_dinamic9)

        val text_view_dinamic10 = TextView(this)
        text_view_dinamic10.textSize = 30f
        text_view_dinamic10.text = "e dexiciut"
        text_view_dinamic10.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic10.layoutParams = params
        scrollContent?.addView(text_view_dinamic10)

        val text_view_dinamic11 = TextView(this)
        text_view_dinamic11.textSize = 30f
        text_view_dinamic11.text = "scumpet overload"
        text_view_dinamic11.setBackgroundResource(R.drawable.received_message)
        text_view_dinamic11.setTextColor(Color.parseColor("#11ff33"))
        //text_view_dinamic10.layoutParams = params
        scrollContent?.addView(text_view_dinamic11)

        // asta face scroll la bottom
        scrollLayout.post(Runnable { scrollLayout.fullScroll(ScrollView.FOCUS_DOWN) })

        val chat_log_button = findViewById<Button>(R.id.chat_log)
        chat_log_button.setOnClickListener() {
            val intent = Intent(this, ChatLogActivity::class.java)
            startActivity(intent)
            //finish()
        }
    }
}
