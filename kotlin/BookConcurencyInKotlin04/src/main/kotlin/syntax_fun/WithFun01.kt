package syntax_fun

class Controller01 {
    inline fun withTimestamp() {

    }

    fun index(): String {
        val result = (1..1000).sum()
        return "<html>${result}</html>"
    }
}

fun main() {
    val controller01 = Controller01()
    println(controller01.index())
}