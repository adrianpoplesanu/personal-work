package ch05c

fun main(args: Array<String>) {
    val iterator1 = iterator {
        for (i in 0 .. 4) {
            yield(i * 4)
        }
    }
    for (i in 0..5) {
        if (iterator1.hasNext()) {
            println("element $i is ${iterator1.next()}")
        } else {
            println("no more elements")
        }
    }
}