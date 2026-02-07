package ch06i

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val channel = Channel<Int>()
    println("${channel.isClosedForReceive}")
    channel.close()
    println("${channel.isClosedForReceive}")

    val channel2 = Channel<Int>()
    channel2.close()
    val element = channel2.receive()
}

