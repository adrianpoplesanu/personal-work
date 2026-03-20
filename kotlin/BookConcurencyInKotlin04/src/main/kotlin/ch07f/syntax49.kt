package ch07f

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.channels.actor
import kotlinx.coroutines.newFixedThreadPoolContext

suspend fun main(args: Array<String>) {
    val dispatcher = newFixedThreadPoolContext(3, "pool-name")
    val actor1 = GlobalScope.actor<String> (dispatcher) {
        for (msg in channel) {
            println("Running in ${Thread.currentThread().name}")
        }
    }

    for (i in 1..100) {
        actor1.send("a")
    }
}