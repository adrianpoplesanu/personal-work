package ch04p

import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext

fun main(args: Array<String>) = runBlocking {
    val dispatcher = newSingleThreadContext("myThread")
    val name = withContext(dispatcher) {
        // some important work here
        "Bebe Dex"
    }
    println("User: $name")
}