package ro.adrianus.chapter8

import kotlinx.coroutines.CoroutineName
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.newFixedThreadPoolContext
import kotlinx.coroutines.newSingleThreadContext
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext
import java.util.Calendar

fun main(args: Array<String>) = runBlocking {
    val pool = newFixedThreadPoolContext(3, "myPool")
    val ctx = newSingleThreadContext("ctx")

    for (i in 0..5) {
        GlobalScope.async(pool + CoroutineName("main")) {
            val year = Calendar.getInstance().get(Calendar.YEAR)

            withContext(ctx + CoroutineName("inner")) {
                println("aaa")
                println(year)
            }
        }.await()
    }
}