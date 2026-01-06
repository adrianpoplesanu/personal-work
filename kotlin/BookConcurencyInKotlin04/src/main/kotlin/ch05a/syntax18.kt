package ch05a

fun main(args: Array<String>) {
    val iterator1 = iterator {
        yield("Susan")
        yield("Olivia")
        yield("Carla")
    }
    println(iterator1.next())
    println(iterator1.next())
    println(iterator1.next())
}