package syntax_fun

class FoldTesting1 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val names = listOf("aaa", "bbb", "ccc")
            val allNames = names.fold("") { acc, s -> acc + s }
            println("all names concatenated: $allNames")
        }
    }
}