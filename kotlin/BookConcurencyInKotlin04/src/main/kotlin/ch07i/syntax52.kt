package ch07i

import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.sync.Mutex

fun main(args: Array<String>) = runBlocking {
    val mutex = Mutex()

    mutex.lock()
    println("Mutex isLocked: ${mutex.isLocked}")
    mutex.unlock()
}