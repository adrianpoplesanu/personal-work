package ch03

import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking

class JobVsDeferred02 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            launch {
                TODO("Not implementd!")
            }
            delay(5000)
        }
    }
}