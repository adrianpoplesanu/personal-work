package ch05d

fun main(args: Array<String>) {
    val iterator1 = iterator {
        yield(1)
    }

    println(iterator1.next())
    println(iterator1.next()) // NoSuchElementException aici
}