package ch04e

import kotlinx.coroutines.*

fun main(args: Array<String>) = runBlocking {
    val dispatcher = newSingleThreadContext("myThread")
    GlobalScope.launch(dispatcher) {
        println("Starting in ${Thread.currentThread().name}")
        delay(500)
        println("Resuming in ${Thread.currentThread().name}")
    }.join()
}