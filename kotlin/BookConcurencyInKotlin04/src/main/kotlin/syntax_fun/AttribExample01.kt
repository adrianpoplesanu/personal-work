package syntax_fun

class AttribExample01 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val a = if (5 > 2) {
                0.1
            } else {
                0.2
            }
            println(a)
        }
    }
}