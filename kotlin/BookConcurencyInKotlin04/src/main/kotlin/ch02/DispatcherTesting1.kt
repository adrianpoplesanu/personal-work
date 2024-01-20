package ch02

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class DispatcherTesting1 {
    fun printCurrentThread() {
        println("Running in thread [${Thread.currentThread().name}]")
    }
    suspend fun run() {
        val task = GlobalScope.launch {
            printCurrentThread()
        }
        task.join()
    }
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val dispatcherTesting1 = DispatcherTesting1()
            dispatcherTesting1.run()
        }
    }
}