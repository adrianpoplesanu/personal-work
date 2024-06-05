package syntax_fun

class InvocationExample1 {

    private fun test(): () -> String {
        return { "bebe dex" }
    }

    private fun test2(): (a: String) -> String {
        return { a -> "bebe dex2 $a" }
    }

    private fun test3(): (a: String, b: String) -> String {
        return { a, b ->  "bebe dex3 $a $b" }
    }

    fun run() {
        val res = test().invoke()
        println(res)

        val res2 = test2().invoke("cel micutz")
        println(res2)

        val res3 = test3().invoke("cel micutz", "si drabutz")
        println(res3)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val invocationExample1 = InvocationExample1()
            invocationExample1.run()
        }
    }
}