package ch03

import kotlinx.coroutines.*

class JobVsDeferred04 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            GlobalScope.launch(start=CoroutineStart.LAZY) {
                TODO("Not implemented yet!")
            }

            delay(1500)
        }
    }
}