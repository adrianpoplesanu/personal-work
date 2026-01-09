package ch05o

import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.flow.consumeAsFlow
import kotlinx.coroutines.flow.take
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>): Unit = runBlocking {
    val context = newSingleThreadContext("myThread")

    val producer = produce(context) {
        for (i in 0..9) {
            send(i)
        }
    }

    producer.consumeAsFlow().take(3).collect { println(it) }
    producer.consumeAsFlow().take(3).collect { println(it) }
}