package syntax_fun

class SliceTesting1 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val names = listOf("adina", "anca", "andreea", "alexandra", "alina", "antonia")
            println(
                names
                    .slice(2 until names.size)
                    .filterNotNull()
                    .map { "${it}AAA" }
                    //.associateBy { it to "bbb" }
                    .associate { it to "bbb" }
            )
        }
    }
}