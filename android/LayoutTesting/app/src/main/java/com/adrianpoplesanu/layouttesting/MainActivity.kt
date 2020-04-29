package com.adrianpoplesanu.layouttesting

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import androidx.constraintlayout.widget.ConstraintLayout

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        Log.d("LayoutTesting Debug", "main activity loaded")

        val text_view_dinamic = TextView(this)
        text_view_dinamic.textSize = 20f
        text_view_dinamic.text = "Message received";
        //text_view_dinamic
        //ll_main_layout.addView(text_view_dinamic)
        val linearLayout = findViewById<ConstraintLayout>(R.id.rootLayout)
        linearLayout?.addView(text_view_dinamic)
    }
}
