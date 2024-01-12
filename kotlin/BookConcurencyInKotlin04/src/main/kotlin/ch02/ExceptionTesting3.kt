package ch02

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ExceptionTesting3 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val task = GlobalScope.async {
                doSomething()
            }
            task.await()
            println("completed")
        }

        private fun doSomething() {
            throw UnsupportedOperationException("oops3")
        }
    }
}