package ch03

import kotlinx.coroutines.*

@OptIn(InternalCoroutinesApi::class)
fun main() = runBlocking {
    val job = launch {
        try {
            repeat(10) { i ->
                println("Job is working... $i")
                delay(300)
            }
        } finally {
            println("Job is cancelled. Cleaning up...")
        }
    }

    delay(1000) // Let the job run for a bit

    // Cancel the job with a specific exception
    val cancellationException = CancellationException("Job was cancelled intentionally")
    job.cancel(cancellationException)

    // Wait for the job to finish
    job.join()

    // Retrieve and print the cancellation exception
    println("Cancellation reason: ${job.getCancellationException().message}")
}