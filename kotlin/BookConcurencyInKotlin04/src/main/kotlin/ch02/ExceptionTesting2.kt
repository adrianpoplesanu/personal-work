package ch02

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.InternalCoroutinesApi
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ExceptionTesting2 {
    // ATTENTION: add GlobalScope, else the code does not work
    companion object {
        @OptIn(InternalCoroutinesApi::class)
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val task = GlobalScope.async {
                doSomething()
            }
            task.join()
            if (task.isCancelled) {
                val e = task.getCancellationException()
                println("auch")
            } else {
                println("completed")
            }
        }

        private fun doSomething() {
            throw UnsupportedOperationException("oops2")
        }
    }
}