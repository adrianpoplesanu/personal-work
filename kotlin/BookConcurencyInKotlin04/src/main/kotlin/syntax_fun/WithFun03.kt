package syntax_fun

import kotlinx.coroutines.runBlocking
import kotlin.coroutines.coroutineContext

class BeverlyHillsController {
    suspend fun getUrl() : String = withTimestampAndContext(coroutineContext) {
        println("Thread: ${Thread.currentThread().name}")
        return "https://adrianus.ro"
    }
}

fun main(args: Array<String>) = runBlocking {
    val controller = BeverlyHillsController()
    println(controller.getUrl())
}