package syntax_fun

import kotlinx.coroutines.withContext

inline fun <T> withTimestamp(block: () -> T): T {
    val startTime = System.nanoTime()
    val result = block()
    val endTime = System.nanoTime()
    println("Execution took ${endTime - startTime} ns")
    return result
}

inline fun <T> withTimestampAndWait(block: () -> T): T {
    val startTime = System.nanoTime()
    return try {
        block()
    } finally {
        val endTime = System.nanoTime()
        println("Execution took ${endTime - startTime} ns")
    }
}

inline fun <T> withTimestampAndContext(context: kotlin.coroutines.CoroutineContext, block: () -> T): T {
    val startTime = System.nanoTime()
    return try {
        block()
    } finally {
        val endTime = System.nanoTime()
        println("Execution took ${endTime - startTime} ns")
    }
}

suspend inline fun <T> withTimestampAndContext2(context: kotlin.coroutines.CoroutineContext, crossinline block: () -> T): T {
    val startTime = System.nanoTime()
    return try {
        withContext(context) {
            block()
        }
    } finally {
        val endTime = System.nanoTime()
        println("Execution took ${endTime - startTime} ns")
    }
}

class Controller01 {
    fun index(): String = withTimestampAndWait {
        val result = (1..1000).sum()
        return "<html>${result}</html>"
    }
}

fun main() {
    val controller01 = Controller01()
    val rendered = controller01.index()
    println(rendered)
}