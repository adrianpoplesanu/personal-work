package ch01

import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

class BeingExplicit2 {

    suspend fun getName(): String {
        delay(1000)
        return "bebe"
    }

    suspend fun getLastName(): String {
        delay(1000)
        return "dex"
    }

    fun execute() = runBlocking {
        val time = measureTimeMillis {
            val name = async { getName() }
            val lastName = async { getLastName() }
            println("hello, ${name.await()} ${lastName.await()}")
        }
        println ("Execution took $time ms")
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            val beingExplicit2 = BeingExplicit2()
            beingExplicit2.execute()
        }
    }
}