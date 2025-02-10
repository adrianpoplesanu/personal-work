package ch03

import kotlinx.coroutines.*

class JobInstantiation07 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val job = Job()
            val scope = CoroutineScope(Dispatchers.Default + job)
            scope.launch {
                println("running manual job")
                delay(1500)
                println("end manual job")
            }
            delay(3000)
            println("cancelling...")
            job.cancel()
            println("cancelled!")
        }
    }
}