package ch03

import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

class StatesMoving1 {
    fun run() = runBlocking {
        val time = measureTimeMillis {
            val job = launch {
                delay(2000)
            }
            job.join()

            job.start()
            job.join()
        }
        println("took $time ms")
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val statesMoving1 = StatesMoving1()
            statesMoving1.run()
        }
    }
}