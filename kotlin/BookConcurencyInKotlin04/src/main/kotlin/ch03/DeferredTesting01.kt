package ch03

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class DeferredTesting01 {
    private fun getHeadlines() : List<String> {
        return listOf("aaa", "bbb")
    }

    suspend fun run() {
        val headlinesTask = GlobalScope.async {
            getHeadlines()
        }

        val result = headlinesTask.await()
        println(result)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val deferredTesting01 = DeferredTesting01()
            deferredTesting01.run()
        }
    }
}