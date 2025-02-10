package ch03

import kotlinx.coroutines.*

class JobJoining06 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val job = GlobalScope.launch(start= CoroutineStart.LAZY) {
                delay(3000)
            }
            job.join()
        }
    }
}