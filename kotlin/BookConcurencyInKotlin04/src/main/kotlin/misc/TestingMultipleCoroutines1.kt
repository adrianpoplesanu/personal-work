package misc

import kotlinx.coroutines.*
import kotlin.system.measureTimeMillis

class TestingMultipleCoroutines1 {

    private suspend fun runner(i: Int) {
        delay(1000)
        println("finished: $i")
    }

    suspend fun createCoroutines(total: Int) {
        val jobs = ArrayList<Job>()
        for (i in 0..total) {
            jobs += GlobalScope.launch {
                runner(i)
            }
        }
        jobs.forEach {
            it.join()
        }
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val testingMultipleCoroutines1 = TestingMultipleCoroutines1()
            val duration = measureTimeMillis {
                testingMultipleCoroutines1.createCoroutines(1_000_000)
            }
            println("ran took: $duration")
        }
    }
}