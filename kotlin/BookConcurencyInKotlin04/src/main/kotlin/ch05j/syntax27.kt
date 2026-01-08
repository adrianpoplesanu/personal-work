package ch05j

fun main(args: Array<String>) {
    val fibonacci = iterator {
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

    for(i in 0..91) {
        println("$i is ${fibonacci.next()}")
    }
}