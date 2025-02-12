package ch03

import kotlinx.coroutines.*

class JobCancelling12 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val job = GlobalScope.launch {
                try {
                    repeat(10) { i ->
                        println("Job is working... $i")
                        delay(300)
                    }
                } catch (e: CancellationException) {
                    println("Job was cancelled. Reason: ${e.message}")
                    throw e // Always rethrow CancellationException to propagate cancellation
                } finally {
                    println("Job is cleaning up!")
                }
            }

            delay(1000) // Let the job run for a bit

            // Cancel the job with a specific exception
            job.cancel(CancellationException("Custom cancellation reason"))

            // Wait for the job to finish
            job.join()

            println("Main program finished.")
        }
    }
}