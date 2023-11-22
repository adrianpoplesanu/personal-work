package syntax_fun

class SpecialOperatorsTest1 {
    fun generate(op: Int): String? {
        if (op > 5) {
            return "aaa"
        }
        return null
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            println("running SpecialOperatorsTest1...")
            val specialOperatorsTest1 = SpecialOperatorsTest1()
            var result = specialOperatorsTest1.generate(7)
            result?.let {
                println(it)
            }
            result = specialOperatorsTest1.generate(4)
            result?.let {
                println(it)
            } ?: run {
                println ("nothing")
            }
        }
    }
}