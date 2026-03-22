package ro.adrianus.chapter8

import kotlinx.coroutines.CoroutineName
import kotlinx.coroutines.newFixedThreadPoolContext
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext

fun threadName2() = Thread.currentThread().name

fun main(args: Array<String>) = runBlocking {
    val pool = newFixedThreadPoolContext(3, "myPool")
    val ctx = newSingleThreadContext("ctx")

    withContext(pool + CoroutineName("main")) {
        println("Running in ${threadName2()}")

        withContext(ctx + CoroutineName("inner")) {
            println("Switching to ${threadName2()}")
        }
    }
}