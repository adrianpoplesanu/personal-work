package ch07j

import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.sync.Mutex

fun main(args: Array<String>) = runBlocking {
    val mutex = Mutex()

    var lockedByMe = mutex.tryLock()
    println(lockedByMe)
    mutex.unlock()

    mutex.lock()
    lockedByMe = mutex.tryLock()
    println(lockedByMe)
    mutex.unlock()
}