package ch05m

import kotlinx.coroutines.channels.ReceiveChannel
import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking {
    val context = newSingleThreadContext("myThread")

    val producer : ReceiveChannel<Any> = produce(context) {
        send(1)
        send("aaa")
    }

    println("${producer.receive()}")
    println("${producer.receive()}")
}