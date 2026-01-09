package ch05k

import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val producer = produce<Int> {
        send(122)
    }

    println("value: ${producer.receive()}")
}