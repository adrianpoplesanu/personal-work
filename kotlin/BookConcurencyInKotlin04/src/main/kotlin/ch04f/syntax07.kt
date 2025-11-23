package ch04f

import kotlinx.coroutines.*

fun main(args: Array<String>) = runBlocking {
    val dispatcher = newSingleThreadContext("myThread1")
    val scope = CoroutineScope(Dispatchers.Default)
    scope.launch(dispatcher) {
        println("Starting in ${Thread.currentThread().name}")
        delay(500)
        println("Resuming in ${Thread.currentThread().name}")
    }.join()
}