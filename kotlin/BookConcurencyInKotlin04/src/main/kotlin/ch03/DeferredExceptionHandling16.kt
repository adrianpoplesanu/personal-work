package ch03

import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class DeferredExceptionHandling16 {
    fun run() = runBlocking<Unit> {
        val deferred = async {
            TODO("Not implemented yet!")
        }
        deferred.await()
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val program = DeferredExceptionHandling16()
            program.run()
        }
    }
}