package syntax_fun

import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking

val context1 = newSingleThreadContext("Adish01Thread")

class CostaRica {
    suspend fun someMethod() = withTimestampAndContext2(context1) {
        println("Thread: ${Thread.currentThread().name}")
    }
}

fun main(args: Array<String>) = runBlocking {
    val costaRica = CostaRica()
    costaRica.someMethod()
}