package ch04o

import kotlinx.coroutines.async
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

fun main(args: Array<String>) = runBlocking{
    val dispatcher = newSingleThreadContext("myThread")
    val name = async(dispatcher) {
        // do important operation here
        "Bebe Dex"
    }.await()

    println("User: $name")
}