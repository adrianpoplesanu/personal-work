package ch01

import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

class Readable1 {

    suspend fun asyncGetName(): String {
        delay(10)
        return "bebe dex"
    }

    suspend fun asyncGetAge(): Int {
        delay(10)
        return 12
    }

    fun execute() = runBlocking {
        val name = async { asyncGetName() }
        val age = async { asyncGetAge() }
        println ("dog: ${name.await()} ${age.await()}")
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            val readable1 = Readable1()
            readable1.execute()
        }
    }
}