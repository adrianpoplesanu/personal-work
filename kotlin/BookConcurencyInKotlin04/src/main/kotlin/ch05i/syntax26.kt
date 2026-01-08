package ch05i

fun main(args: Array<String>) {
    val fibonacci = sequence {
        yield(1L)
        var current = 1L
        var next = 1L
        while(true) {
            yield(next)
            val tmpNext = current + next
            current = next
            next = tmpNext
        }
    }

    val indexed = fibonacci.take(50).withIndex()

    for ((index, value) in indexed) {
        println("$index: $value")
    }
}