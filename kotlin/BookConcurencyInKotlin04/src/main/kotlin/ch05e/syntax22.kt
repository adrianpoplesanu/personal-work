package ch05e

fun main(args: Array<String>) {
    val iterator1 = iterator {
        println("yielding 1")
        yield(1)
        println("yielding 2")
        yield(2)
    }

    iterator1.next()

    if (iterator1.hasNext()) {
        println("iterator has next")
        iterator1.next()
    }
}