package ch06h

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking{
    val channel = Channel<Int>(1)
    channel.trySend(2)
    val value = channel.receive()
    println("value: $value")
}