package syntax_fun

class ForEachTesting1 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            println("running...")
            val data = mutableMapOf("aaa" to "bbb", "ccc" to "ddd")
            println(data)
            data.forEach { (t, u) ->
                println(t)
                println(u)
            }
        }
    }
}