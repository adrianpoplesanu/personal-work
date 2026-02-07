package ch06j

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val channel = Channel<Int>(1)
    println("${channel.isEmpty}")
    channel.send(10)
    println("${channel.isEmpty}")
}

