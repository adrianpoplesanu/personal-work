package ch06f

import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val channel = Channel<Int>(1)
    channel.close()
    channel.send(1)
}