package ch05f

fun main(args: Array<String>) {
    val sequence1: Sequence<Any> = sequence {
        yield("A")
        yield(1)
        yield(32F)
    }

    println("element at 0: ${sequence1.elementAt(0)}")
    println("element at 1: ${sequence1.elementAt(1)}")
    println("element at 2: ${sequence1.elementAt(2)}")
}