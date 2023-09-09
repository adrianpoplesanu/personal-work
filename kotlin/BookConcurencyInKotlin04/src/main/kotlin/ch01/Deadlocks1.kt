package ch01

import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class Deadlocks1 {

    lateinit var jobA : Job
    lateinit var jobB : Job

    companion object {
        @JvmStatic
        fun main(args : Array<String>) = runBlocking {
            // programul asta cicleaza pentru ca a asteapta b, iar b asteapta a
            val deadlocks1 = Deadlocks1()
            deadlocks1.jobA = launch {
                delay(1000)
                // wait for jobB to finish
                deadlocks1.jobB.join()
            }
            deadlocks1.jobB = launch {
                // wait for jobA to finish
                deadlocks1.jobA.join()
            }
            // wait for jobA to finish
            deadlocks1.jobA.join()
            println ("finished")
        }
    }
}