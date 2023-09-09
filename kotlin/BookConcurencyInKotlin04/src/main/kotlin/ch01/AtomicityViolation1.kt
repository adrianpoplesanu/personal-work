package ch01

import kotlinx.coroutines.Deferred
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class AtomicityViolation1 {

    var counter = 0

    suspend fun asyncIncrement(by : Int): Deferred<Unit> {
        return GlobalScope.async {
            for (i in 0 until by) {
                counter++
            }
        }
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) = runBlocking {
            // run this multiple times, not always displaying 3000
            var atomicityViolation1 = AtomicityViolation1()
            val worker1 = atomicityViolation1.asyncIncrement(2000)
            val worker2 = atomicityViolation1.asyncIncrement(1000)
            worker1.await()
            worker2.await()
            print ("counter [" + atomicityViolation1.counter + "]")
        }
    }
}