package ch02

import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ExceptionTesting1 {

    private fun doSomething() {
        throw UnsupportedOperationException("oops")
    }

    fun run() = runBlocking {
        val task = async { doSomething() }
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