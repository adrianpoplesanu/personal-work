package ch02

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class DispatcherTesting2 {
    companion object {
        fun printCurrentThread() {
            println("Running in thread[${Thread.currentThread().name}]")
        }

        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            // cu GlobalScope Running in thread[DefaultDispatcher-worker-1]
            // val task = GlobalScope.launch {
            // fara GlobalScope Running in thread[main]
            val task = launch {
                printCurrentThread()
            }
            task.join()
        }
    }
}