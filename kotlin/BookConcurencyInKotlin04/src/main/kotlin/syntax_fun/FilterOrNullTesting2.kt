package syntax_fun

fun main() {
    val a = mapOf<String, Int>()
    //val a = mapOf("aaa" to 1, "bbb" to 3)
    val res = a.filter { it.value != 0 }.map { it.value }.minOrNull()
    println(res)
}