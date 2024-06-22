package ch03

import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class JobVsDeferred03 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            //val job = Job() // this works but i don't know how to use it
            val job = launch {
                delay(500)
                println("aaa")
                delay(500)
            }
            println("bbb")
        }
    }
}