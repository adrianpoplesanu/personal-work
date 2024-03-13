package syntax_fun

import kotlinx.coroutines.*
import java.lang.Thread.sleep

class ConcurrencyTest1 {
    suspend fun doSomething(i: Int) {
        println("started: $i")
        sleep(1000)
        println("finish: $i")
    }

    suspend fun doSomethingElse(i: Int): Int {
        sleep(1000)
        return i + 1
    }

    suspend fun test1() {
        for (i in 0 until 10) {
            doSomething(i)
        }
    }

    suspend fun test2() {
        val tasks = mutableListOf<Deferred<Unit>>()
        for (i in 0 until 10) {
            val task = GlobalScope.async {
                doSomething(i)
            }
            tasks.add(task)
        }
        for (i in 0 until 10) {
            tasks[i].await()
        }
    }

    suspend fun test3() {
        val tasks = mutableListOf<Deferred<Int>>()
        for (i in 0 until 10) {
            val task = GlobalScope.async {
                doSomethingElse(i)
            }
            tasks.add(task)
        }
        for (i in 0 until 10) {
            val a = tasks[i].await()
            println(a)
        }
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val concurrencyTest1 = ConcurrencyTest1()
            //concurrencyTest1.test1()
            //concurrencyTest1.test2()
            concurrencyTest1.test3()
        }
    }
}