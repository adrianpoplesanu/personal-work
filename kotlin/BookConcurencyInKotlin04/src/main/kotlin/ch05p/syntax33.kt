package ch05p

import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.flow.consumeAsFlow
import kotlinx.coroutines.flow.take
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>): Unit = runBlocking {
    val context = newSingleThreadContext("myThread")

    val producer = produce(context) {
        send(1L)
        var current = 1L
        var next = 1L
        while(true) {
            send(next)
            val tmpNext = current + next
            current = next
            next = tmpNext
        }
    }

    producer.consumeAsFlow().take(10).collect { println(it) }
}