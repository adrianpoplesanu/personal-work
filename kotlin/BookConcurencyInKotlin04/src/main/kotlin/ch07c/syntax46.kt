package ch07c

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.channels.actor
import kotlinx.coroutines.runBlocking

var counter = 0

fun getCounterValue() = counter

val actorCounter = GlobalScope.actor<Unit?>(Dispatchers.Default) {
    for (msg in channel) {
        counter++
    }
}

fun asyncIncrement(by: Int) = GlobalScope.async(Dispatchers.Default) {
    for (i in 0 until by) {
        actorCounter.send(null)
    }
}

fun main(args: Array<String>) = runBlocking {
    val workerA = asyncIncrement(2000)
    val workerB = asyncIncrement(100)

    workerA.await()
    workerB.await()

    println("counter ${getCounterValue()}")
}