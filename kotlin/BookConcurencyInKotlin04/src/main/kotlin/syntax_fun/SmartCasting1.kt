package syntax_fun

class SmartCasting1 {
    private fun transform(a: Any) {
        val b = a as String // java.lang.Integer cannot be cast to java.lang.String
        println(b)
    }

    fun test() {
        val a = 123
        transform(a)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val smartCasting1 = SmartCasting1()
            smartCasting1.test()
        }
    }
}