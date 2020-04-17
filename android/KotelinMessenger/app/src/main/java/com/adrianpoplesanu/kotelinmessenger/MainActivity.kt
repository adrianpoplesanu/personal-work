package com.adrianpoplesanu.kotelinmessenger

import android.os.Bundle
import android.text.TextPaint
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import okhttp3.*
//import java.net.Socket
//import java.util.concurrent.TimeUnit


class MainActivity : AppCompatActivity() {
    var webSocket : WebSocket? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button_test_socket = findViewById<Button>(R.id.test_socket)
        button_test_socket.setOnClickListener {
            Log.d("Test Button Listener","button was clicked!")
            try {
                // some code
                //val socket = Socket("192.168.0.101", 5000) // asta merge cu un socket server scris in C++
                //val b : ByteArray = ByteArray("add user");
                //socket.getOutputStream().write("add user".toByteArray())
                val client = OkHttpClient.Builder()
                    //.readTimeout(3, TimeUnit.SECONDS)
                    //.sslSocketFactory()
                    .build()
                val request = Request.Builder()
                    .url("ws://192.168.0.108:8090") // aici trebuie sa pun IP-ul de la amazon
                    .build()
                val wsListener = EchoWebSocketListener ()
                webSocket = client.newWebSocket(request, wsListener) // this provide to make 'Open ws connection'
                //webSocket?.send("neata!")
            }
            catch (e: Exception) {
                // handler
                Log.d("Test Button Listener","there was an error with the socket!")
                Log.d("Test Button Listener", e.toString())
            }
        }
        val message_input = findViewById<TextView>(R.id.messageInput)
        val button_send_neata = findViewById<Button>(R.id.send_neatza)
        button_send_neata.setOnClickListener {
            val text = message_input.text.toString()
            webSocket?.send(text)
        }
    }

    private class EchoWebSocketListener : WebSocketListener() {
        override fun onMessage(webSocket: WebSocket?, text: String?) {
            //output("Receiving : " + text!!)
            Log.d("Test Button Listener", text)
        }

        override fun onFailure(webSocket: WebSocket, t: Throwable, response: Response?) {
            //output("Error : " + t.message)
            Log.d("Test Button Listener", t.message)
        }
    }
}

