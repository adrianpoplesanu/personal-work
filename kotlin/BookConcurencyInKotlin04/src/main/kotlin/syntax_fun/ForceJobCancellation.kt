package syntax_fun

import kotlinx.coroutines.*

class ForceJobCancellation {
    fun run() = runBlocking {
        val job = Job()
        val scope = CoroutineScope(Dispatchers.Default + job)
        val something = scope.async {
            delay(1000)
        }
        delay(10)
        scope.cancel()
        something.await()
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val program = ForceJobCancellation()
            program.run()
        }
    }
}