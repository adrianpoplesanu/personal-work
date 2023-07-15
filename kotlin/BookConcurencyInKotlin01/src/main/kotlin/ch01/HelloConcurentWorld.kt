package ch01

import kotlinx.coroutines.*
import kotlin.system.measureTimeMillis

suspend fun createCoroutines(amount : Int) {
    //
    val jobs = ArrayList<Job>()
    for (i in 1..amount) {
        jobs += launch {
            delay(1000)
        }
    }
    jobs.forEach {
        it.join()
    }
}

fun main(args : Array<String>) = runBlocking {
    val time = measureTimeMillis {
        createCoroutines(10_000)
    }

    println("Took $time ms")
}