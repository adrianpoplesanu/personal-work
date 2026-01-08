package ch05h

fun main(args: Array<String>) {
    val sequence1 = sequence {
        for (i in 0..9) {
            println("Yielding $i")
            yield(i)
        }
    }

    println("Requesting index 1")
    sequence1.elementAt(1)

    println("Requesting index 2")
    sequence1.elementAt(2)

    println("Taking 3")
    sequence1.take(3).joinToString()
}