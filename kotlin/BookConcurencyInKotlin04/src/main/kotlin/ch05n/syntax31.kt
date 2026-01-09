package ch05n

import kotlinx.coroutines.channels.ReceiveChannel
import kotlinx.coroutines.channels.consumeEach
import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val context = newSingleThreadContext("myThread")

    val producer = produce(context) {
        for (i in 0..9) {
            send(i)
        }
    }

    producer.consumeEach {
        println("$it")
    }
}