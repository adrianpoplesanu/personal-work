package ch07h

import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.sync.Mutex

fun main(args: Array<String>) = runBlocking {
    val mutex = Mutex()

    mutex.lock()
    print("I am an atomic operation")
    mutex.unlock()
}