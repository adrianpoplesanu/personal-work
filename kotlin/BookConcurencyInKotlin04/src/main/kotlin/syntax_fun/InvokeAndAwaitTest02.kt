package syntax_fun

import kotlinx.coroutines.runBlocking

class InvokeAndAwaitTest02 {
    fun run() = runBlocking {
        println("running...")
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val invokeAndAwaitTest02 = InvokeAndAwaitTest02()
            invokeAndAwaitTest02.run()
        }
    }
}