package ch03

import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

class DeferredExceptionHandling15 {
    fun run() = runBlocking {
        val deferred = async {
            TODO("Not implemented yet!")
        }

        delay(2000)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val program = DeferredExceptionHandling15()
            program.run()
        }
    }
}