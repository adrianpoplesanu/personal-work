package ch02

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ExceptionTesting1 {
    // ATTENTION: add GlobalScope, else the code does not work

    private fun doSomething() {
        throw UnsupportedOperationException("oops")
    }

    fun run() = runBlocking {
        val task = GlobalScope.async { doSomething() }
        task.join()
        println("completed")
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val exceptionTesting1 = ExceptionTesting1()
            exceptionTesting1.run()
        }
    }
}