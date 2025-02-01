package syntax_fun

import kotlinx.coroutines.*

class InvokeAndAwaitTest01 {
    class SpecialResponse {
        var age: Int = 0
        var name: String = "no name"

        constructor(age: Int, name: String) {
            this.age = age
            this.name = name
        }
    }

    private suspend fun generate(): () -> SpecialResponse {
        delay(1000)
        return { SpecialResponse(15, "bebe dex") }
    }

    fun run() = runBlocking {
        val tasks = mutableListOf<Deferred<() -> SpecialResponse>>()
        for (i in 0 until 10) {
            tasks.add(GlobalScope.async {
                generate()
            })
        }
        val tasksResponse = tasks.awaitAll()
        val names = mutableListOf<String>()
        tasksResponse.forEach{
            val response  = it.invoke()
            names.add(response.name)
        }
        println(names)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val invokeAndAwaitTest01 = InvokeAndAwaitTest01()
            invokeAndAwaitTest01.run()
        }
    }
}