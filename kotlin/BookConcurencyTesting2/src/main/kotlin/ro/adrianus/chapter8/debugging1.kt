package ro.adrianus.chapter8

import kotlinx.coroutines.Deferred
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.newFixedThreadPoolContext
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext

fun threadName() = Thread.currentThread().name

fun main(args: Array<String>) = runBlocking {
    val pool = newFixedThreadPoolContext(3, "myPool")
    val ctx = newSingleThreadContext("ctx")

    val tasks = mutableListOf<Deferred<Unit>>()
    for (i in 0..5) {
        val task = GlobalScope.async(pool) {
            println("Processing $i in ${threadName()}")

            withContext(ctx) {
                println("Step two of $i happening in thread ${threadName()}")
            }

            println("Finishing $i in ${threadName()}")
        }
        tasks.add(task)
    }

    for (task in tasks) {
        task.await()
    }
}