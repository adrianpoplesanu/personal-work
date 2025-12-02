package ch04m

import kotlinx.coroutines.*

fun main(args: Array<String>) = runBlocking {
    val dispatcher = newSingleThreadContext("myDispatcher")
    val handler = CoroutineExceptionHandler { _, throwable ->
        println("Error captured")
        println("Message: ${throwable.message}")
    }

    val scope = CoroutineScope(Dispatchers.Default)
    val context = dispatcher + handler
    scope.launch(context) {
        println("Running in ${Thread.currentThread().name}")
        TODO("Not implemented!")
    }.join()
}