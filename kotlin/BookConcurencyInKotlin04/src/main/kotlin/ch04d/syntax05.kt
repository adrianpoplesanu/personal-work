package ch04d

import kotlinx.coroutines.*

fun main(args: Array<String>) = runBlocking {
    val scope = CoroutineScope(Dispatchers.Default)
    scope.launch(Dispatchers.Unconfined) {
        println("Starting in ${Thread.currentThread().name}")
        delay(500)
        println("Resuming in ${Thread.currentThread().name}")
    }.join()
}