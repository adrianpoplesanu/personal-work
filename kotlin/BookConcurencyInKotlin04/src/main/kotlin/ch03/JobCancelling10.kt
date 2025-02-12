package ch03

import kotlinx.coroutines.*

@OptIn(InternalCoroutinesApi::class)
class JobCancelling10 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val job = GlobalScope.launch {
                println("running job...")
                delay(5000)
                println("reached end!")
            }
            delay(2000)
            job.cancel(cause = CancellationException("Timeout!"))

            job.join()
            val cancellation = job.getCancellationException()
            println(cancellation.message)
        }
    }
}