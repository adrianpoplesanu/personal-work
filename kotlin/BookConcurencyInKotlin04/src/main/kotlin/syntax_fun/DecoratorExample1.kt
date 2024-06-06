package syntax_fun

class DecoratorExample1 {

    private fun <T> withSomething(block: () -> T): T {
        println("in decorator")
        return block()
    }

    private fun test() = withSomething {
        println("in test")
    }

    private fun test2() = withSomething {
        println("in test2")
    }

    fun run() {
        test()
        test2()
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val decoratorExample1 = DecoratorExample1()
            decoratorExample1.run()
        }
    }
}