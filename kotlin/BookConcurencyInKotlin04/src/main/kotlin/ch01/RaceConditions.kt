package ch01

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

class RaceConditions {

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
            var raceConditions = RaceConditions()
            raceConditions.getDataAsync()
            println (raceConditions.user.name)
            // this will fail
        }
    }
}