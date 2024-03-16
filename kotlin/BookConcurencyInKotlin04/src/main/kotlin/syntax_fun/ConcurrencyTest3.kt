package syntax_fun

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class ConcurrencyTest3 {

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

        val deferredResults = tasks.map {
                task -> {
            GlobalScope.async {
                //val result = task.enh()
                //data.also { it[result.id] = result.name }
                //data[result.id] = result.name
                //someBoolean = true
                task.enh() // ultima linie drept urmare asta se returneaza
            }
        }
        }
        val finalResults = deferredResults.map { it().await() }
        for (finalResult in finalResults) {
            println("${finalResult.id} ${finalResult.name}")
        }
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val concurrencyTest3 = ConcurrencyTest3()
            concurrencyTest3.test()
        }
    }
}