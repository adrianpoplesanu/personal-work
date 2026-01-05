package ch05a

fun main(args: Array<String>) {
    val iterator = iterator {
        yield("Susan")
        yield("Olivia")
        yield("Carla")
    }
    println(iterator.next())
    println(iterator.next())
    println(iterator.next())
}