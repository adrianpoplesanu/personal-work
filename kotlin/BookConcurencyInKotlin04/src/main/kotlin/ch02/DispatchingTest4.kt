package ch02

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

class DispatchingTest4 {
    companion object {

        fun printCurrentThread() {
            println("Running in thread[${Thread.currentThread().name}]")
        }

        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val dispatcher = newSingleThreadContext("ServiceCall")
            val task = GlobalScope.launch(dispatcher) {
                printCurrentThread()
            }
            task.join()
        }
    }
}