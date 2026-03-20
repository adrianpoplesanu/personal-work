package ch07d

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.channels.actor
import kotlinx.coroutines.runBlocking

var counter = 0

fun getCounterValue() = counter

enum class Action {
    INCREASE,
    DECREASE
}

var actorCounter = GlobalScope.actor<Action>(Dispatchers.Default) {
    for (action in channel) {
        when (action) {
            Action.INCREASE -> counter++
            Action.DECREASE -> counter--
        }
    }
}

fun asyncIncrement(by: Int) = GlobalScope.async(Dispatchers.Default) {
    for (i in 0 until by) {
        actorCounter.send(Action.INCREASE)
    }
}

fun asyncDecrement(by: Int) = GlobalScope.async(Dispatchers.Default) {
    for (i in 0 until by) {
        actorCounter.send(Action.DECREASE)
    }
}

fun main(args: Array<String>) = runBlocking {
    val workerA = asyncIncrement(2000)
    val workerB = asyncIncrement(100)
    val workerC = asyncDecrement(1000)

    workerA.await()
    workerB.await()
    workerC.await()

    println("counter ${getCounterValue()}")
}