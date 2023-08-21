package ch01

import kotlinx.coroutines.*
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

suspend fun getName() : String {
    for (i in 1..10) {
        delay(100)
        println("sleeping 1")
    }
    return "bebe dex"
}

suspend fun getAge() : Int {
    for (i in 1..10) {
        delay(100)
        println("sleeping 2")
    }
    return 12
}

suspend fun getData() {
    var name = GlobalScope.async { getName() }
    var age = GlobalScope.async { getAge() }
    println(name.await() + ": " + age.await())
}

fun main(args : Array<String>) = runBlocking {
    val time = measureTimeMillis {
        getData()
    }
    println ("took $time seconds")
}