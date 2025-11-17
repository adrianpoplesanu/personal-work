package ch04

import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

suspend fun greetDelayed(delayMillis: Long) {
    delay(delayMillis)
    println("Hello, adrianus.ro!")
}

fun main(args: Array<String>) {
    runBlocking {
        greetDelayed(1000)
    }
}