package ch02

import kotlinx.coroutines.launch
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

class DispatchingTest3 {
    companion object {
        fun printCurrentThread() {
            println("Running in thread[${Thread.currentThread().name}]")
        }

        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val dispatcher = newSingleThreadContext("ServiceCall")
            val task = launch(dispatcher) {
                printCurrentThread()
            }
            task.join()
        }
    }
}