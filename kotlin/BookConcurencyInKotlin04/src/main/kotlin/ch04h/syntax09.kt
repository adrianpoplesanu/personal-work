package ch04h

import kotlinx.coroutines.*

fun main(args: Array<String>) = runBlocking {
    val scope = CoroutineScope(Dispatchers.Default)
    val handler = CoroutineExceptionHandler { context, throwable ->
        println("Error captures in $context")
        println("Message: ${throwable.message}")
    }

    scope.launch(handler) {
        TODO("Not implemented yet!")
    }

    delay(500)
}