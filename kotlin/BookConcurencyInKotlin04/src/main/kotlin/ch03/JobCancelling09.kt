package ch03

import io.ktor.utils.io.*
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class JobCancelling09 {
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
        }
    }
}