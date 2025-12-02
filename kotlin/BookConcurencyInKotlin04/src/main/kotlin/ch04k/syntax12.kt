package ch04k

import kotlinx.coroutines.*
import kotlin.system.measureTimeMillis

fun main(args: Array<String>) = runBlocking{
    val scope = CoroutineScope(Dispatchers.Default)

    val duration = measureTimeMillis {
        val job = scope.launch {
            try {
                while(isActive) {
                    delay(500)
                    println("still running")
                }
            } finally {
                withContext(NonCancellable) {
                    println("cancelled, will delay finalization now")
                    delay(5000)
                    println("delay completed, bye bye")
                }
            }
        }

        delay(1200)
        job.cancelAndJoin()
    }

    println("Took $duration ms")
}