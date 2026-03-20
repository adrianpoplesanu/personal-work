package ch07g

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.async
import kotlinx.coroutines.awaitAll
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock

var counter = 0

var mutex = Mutex()

fun CoroutineScope.asyncIncrement(by: Int) = async {
    for(i in 0 until by) {
        mutex.withLock {
            counter++
        }
    }
}

fun main(args: Array<String>) = runBlocking {
    val jobs = listOf(
        asyncIncrement(1001),
        asyncIncrement(1102),
        asyncIncrement(1203)
    )

    // Wait for all to finish
    jobs.awaitAll()

    println("Counter = $counter")
}