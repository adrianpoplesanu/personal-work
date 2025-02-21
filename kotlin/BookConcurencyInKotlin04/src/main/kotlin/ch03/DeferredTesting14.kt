package ch03

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

class DeferredTesting14 {
    private suspend fun getHeadlines() : List<String> {
        // cand am pus delay aici m-a obligat sa fac getHeadlines suspend
        // daca delay e comentat atunci suspend poate lipsi din antet
        delay(1500)
        return mutableListOf("aaa", "bbb")
    }

    fun run() = runBlocking {
        val headlinesTask = GlobalScope.async {
            getHeadlines()
        }

        headlinesTask.await()
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val deferredTesting14 = DeferredTesting14()
            deferredTesting14.run()
        }
    }
}