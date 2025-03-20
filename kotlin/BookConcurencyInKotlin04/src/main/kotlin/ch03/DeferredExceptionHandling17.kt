package ch03

import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class DeferredExceptionHandling17 {
    fun run() = runBlocking {
        val deferred = async {
            TODO("Not implemented yet")
        }

        try {
            deferred.await()
        } catch (throwable: Throwable) {
            println("Deferred cancelled due to ${throwable.message}")
        }
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val deferredExceptionHandling17 = DeferredExceptionHandling17()
            deferredExceptionHandling17.run()
        }
    }
}