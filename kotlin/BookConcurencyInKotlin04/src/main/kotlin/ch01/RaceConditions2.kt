package ch01

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

class RaceConditions2 {

    data class UserInfo(val name: String)

    lateinit var user: UserInfo

    suspend fun getDataAsync() {
        GlobalScope.async {
            delay(1000)
            user = UserInfo("bebe dex")
        }
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) = runBlocking {
            var raceConditions2 = RaceConditions2()
            raceConditions2.getDataAsync()
            delay(1100) // this waits enough so that user gets initialized
            println (raceConditions2.user.name) // this will work
        }
    }
}