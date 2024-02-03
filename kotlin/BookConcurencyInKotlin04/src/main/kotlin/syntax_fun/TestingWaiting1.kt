package syntax_fun

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import java.lang.Thread.sleep

class TestingWaiting1 {

    private fun doSomething() {
        println("aaa")
        sleep(5000)
        println("bbb")
    }

    fun run1() = runBlocking {
        val task1 = GlobalScope.launch {
            doSomething()
        }
        val task2 = GlobalScope.launch {
            doSomething()
        }
        task1.join()
        task2.join()
        println("ccc")
    }

    fun run2() = runBlocking {
        val task1 = GlobalScope.async {
            doSomething()
        }
        val task2 = GlobalScope.async {
            doSomething()
        }
        task1.await()
        task2.await()
        println("ccc")
    }

    fun run3() = runBlocking {
        println("------------")
        GlobalScope.launch {
            doSomething()
        }
        GlobalScope.launch {
            doSomething()
        }
        println("ccc")
    }

    fun run4() = runBlocking {
        println("-----------")
        GlobalScope.async {
            doSomething()
        }
        GlobalScope.async {
            doSomething()
        }
        println("ccc")
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val testingWaiting1 = TestingWaiting1()
            testingWaiting1.run1()
            testingWaiting1.run2()
            testingWaiting1.run3()
            testingWaiting1.run4()
        }
    }
}