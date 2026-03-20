package ch07a

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

var counter = 0

fun asyncIncrement(by: Int) = GlobalScope.async(Dispatchers.Default) {
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