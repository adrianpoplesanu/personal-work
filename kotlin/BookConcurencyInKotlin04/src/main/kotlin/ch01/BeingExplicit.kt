package ch01

import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

class BeingExplicit {

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
            val name = getName()
            val lastName = getLastName()
            println("Hello, $name $lastName")
        }
        println("Execution took $time ms")
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            val beingExplicit = BeingExplicit()
            beingExplicit.execute()
        }
    }
}