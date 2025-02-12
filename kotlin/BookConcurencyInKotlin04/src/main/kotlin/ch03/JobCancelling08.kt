package ch03

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class JobCancelling08 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val job = GlobalScope.launch {
                println("running job...")
                delay(5000)
                println("reached end!")
            }
            delay(2000)
            job.cancel()
        }
    }
}