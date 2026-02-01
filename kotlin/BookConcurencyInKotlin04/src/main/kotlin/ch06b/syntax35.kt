package ch06b

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

fun main(args: Array<String>) = runBlocking {
    val time = measureTimeMillis {
        val channel = Channel<Int>(Channel.UNLIMITED)
        val sender = launch {
            repeat(5) {
                channel.send(it)
                println("Sent $it")
            }
        }
        delay(500)
    }
    println("Ran for $time ms")
}