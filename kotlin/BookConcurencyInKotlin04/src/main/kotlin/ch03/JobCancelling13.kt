package ch03

import kotlinx.coroutines.*
import kotlin.coroutines.CoroutineContext

class JobCancelling13 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val exceptionHandler = CoroutineExceptionHandler { _: CoroutineContext,
                                                               throwable: Throwable ->
                println("Job cancelled due to ${throwable.message}")
            }

            GlobalScope.launch(exceptionHandler) {
                TODO("Not implemented yet")
            }

            delay(2000)
        }
    }
}