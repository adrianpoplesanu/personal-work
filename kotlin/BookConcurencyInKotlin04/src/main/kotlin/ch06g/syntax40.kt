package ch06g

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val channel = Channel<Int>(1)
    channel.close()
    println("channel1: ${channel.trySend(11).isSuccess}")


    val channel2 = Channel<Int>(1)
    println("channel2 trySend: ${channel2.trySend(11).isSuccess}")
    println("channel2 trySend: ${channel2.trySend(11).isSuccess}")
}