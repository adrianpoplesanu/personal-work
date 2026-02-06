package ch06c

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

fun main(args: Array<String>) = runBlocking {
    val time = measureTimeMillis {
        val channel = Channel<Int>(4)
        val sender = launch {
            repeat(10) {
                channel.send(it)
                println("Send $it")
            }
        }

        delay(500)
        println("Taking two")
        repeat(2) {
            val value = channel.receive()
            println("Received $value")
        }
        delay(500)
    }

    println("Took $time ms")
}