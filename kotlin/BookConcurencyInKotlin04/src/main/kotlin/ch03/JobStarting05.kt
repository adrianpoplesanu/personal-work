package ch03

import kotlinx.coroutines.CoroutineStart
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch

class JobStarting05 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val job = GlobalScope.launch(start= CoroutineStart.LAZY) {
                delay(3000)
            }
            job.start()
        }
    }
}