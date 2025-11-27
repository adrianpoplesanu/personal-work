package ch04i

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
                println("cancelled, will end now")
            }
        }

        delay(1200)
        job.cancelAndJoin()
    }

    println("Took $duration ms")
}