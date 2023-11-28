package syntax_fun

class VarargsTest1 {
    fun process(vararg args: String) {
        for (arg in args) {
            println(arg)
        }
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            var keys = arrayOf("aaa", "bbb")
            val keys2 = arrayOf("ccc", "ddd")

            val varargsTest1 = VarargsTest1()
            varargsTest1.process(*keys)

            println(keys)
            varargsTest1.process(*keys.plus(keys2))
        }
    }
}