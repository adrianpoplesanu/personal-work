package syntax_fun

class FilterOrNullTesting1 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val a = mapOf<String, Int>()
            //val a = mapOf<String, Int>("aaa" to 55, "bbb" to 33)
            val res = a.filter { it.value != 0}.map { it.value }.minOrNull()
            println(res)
        }
    }
}