import kotlinx.coroutines.*

suspend fun doWorld() {
    delay(1000L)
    println("World!")
}

fun main() = runBlocking { // this: CoroutineScope
    launch { doWorld() }
    println("Hello")
}

/*fun main(args: Array<String>) {
    println("Hello World!")

    println("Program arguments: ${args.joinToString()}")
}*/