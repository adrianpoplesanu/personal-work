package elvis

class Elvis {
    fun test() {
        val a : String = "neata"
        println(a)
    }

    fun test2() {
        val a = null
        println(a ?: "aaa")
    }

    fun test3(a : String?) {
        println(a)
    }
}