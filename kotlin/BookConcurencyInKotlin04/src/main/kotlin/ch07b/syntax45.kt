package ch07b

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

var counter = 0
val dispatcher = newSingleThreadContext("myThread")

fun asyncIncrement(by: Int) = GlobalScope.async(dispatcher) {
    for (i in 0 until by) {
        counter++
    }
}

fun main(args: Array<String>) = runBlocking {
    val workerA = asyncIncrement(2000)
    val workerB = asyncIncrement(100)

    workerA.await()
    workerB.await()

    println("counter $counter")
}