package syntax_fun

import io.ktor.client.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import kotlinx.coroutines.async
import kotlinx.coroutines.runBlocking

class GetRequests1 {

    suspend fun retrieve(path: String): String {
        val client = HttpClient()
        val response: HttpResponse = client.get(path)
        return response.bodyAsText()
    }

    fun run(){
        runBlocking {
            val client = HttpClient()
            val response: HttpResponse = client.get("http://www.adrianus.ro")
            println(response.bodyAsText())
        }
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            println("buna dimineata")
            val getRequests1 = GetRequests1()
            //getRequests1.run() // 1st approach... working
            val action = async { getRequests1.retrieve("http://www.adrianus.ro") }
            val content = action.await()
            println (content)
        }
    }
}