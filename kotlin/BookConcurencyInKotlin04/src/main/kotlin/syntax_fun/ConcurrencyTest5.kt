package syntax_fun

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ConcurrencyTest5 {

    class UI {
        var name: String = ""
        var type: String = ""
    }

    data class UI2(var name: String, var type: String) // asta are .copy() by default

    class SBResponse {
        var id: Int = 0
        var name: String = ""
    }

    class EnhTask(val baseId: Int, val baseName: String) {
        fun enh(ui: UI): SBResponse {
            val sbr = SBResponse()
            sbr.id = baseId + 1
            sbr.name = baseName + "ccc"
            ui.name += sbr.name
            return sbr
        }
    }

    suspend fun test() {
        val tasks = listOf(EnhTask(1, "aaa"), EnhTask(2, "bbb"))
        val ui = UI()

        var someBoolean = false
        var data: MutableMap<Int, String> = mutableMapOf()

        val deferredResults = tasks.map {
                task -> {
            GlobalScope.async {
                val result = task.enh(ui)
                data[result.id] = result.name
                someBoolean = true
            }
        }
        }
        deferredResults.map { it().await() }
        println(someBoolean)
        println(data)
        println(ui.name)
        println(ui.type)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val concurrencyTest5 = ConcurrencyTest5()
            concurrencyTest5.test()
        }
    }
}