package syntax_fun

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ConcurrencyTest2 {

    class SBResponse {
        var id: Int = 0
        var name: String = ""
    }

    class EnhTask(val baseId: Int, val baseName: String) {
        fun enh(): SBResponse {
            val sbr = SBResponse()
            sbr.id = baseId + 1
            sbr.name = baseName + "ccc"
            return sbr
        }
    }

    suspend fun test() {
        val tasks = listOf(EnhTask(1, "aaa"), EnhTask(2, "bbb"))

        var someBoolean = false
        var data: MutableMap<Int, String> = mutableMapOf()

        val deferredResults = tasks.map {
            task -> {
                GlobalScope.async {
                    val result = task.enh()
                    data[result.id] = result.name
                    someBoolean = true
                }
            }
        }
        deferredResults.map { it().await() }
        println(someBoolean)
        println(data)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val concurrencyTest2 = ConcurrencyTest2()
            concurrencyTest2.test()
        }
    }
}