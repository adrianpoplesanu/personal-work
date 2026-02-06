package ch06e

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val channel1 = Channel<Int>()
    println("${channel1.isClosedForSend}")
    channel1.close()
    println("${channel1.isClosedForSend}")

    val channel2 = Channel<Int>(1)
    val result1 = channel2.trySend(42)
    println(result1.isSuccess)
    val result2 = channel2.trySend(5)
    println(result2.isSuccess)
}