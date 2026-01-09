package ch05l

import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val context = newSingleThreadContext("myThread")

    val producer = produce(context) {
        send(1)
    }

    println("${producer.receive()}")
}