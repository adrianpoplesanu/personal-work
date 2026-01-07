package ch05g

fun main(args: Array<String>) {
    val sequence1 = sequence {
        yield(1)
        yield(1)
        yield(2)
        yield(3)
        yield(5)
        yield(8)
        yield(13)
        yield(21)
    }

    sequence1.forEach {
        print("$it ")
    }

    sequence1.forEachIndexed { index, value ->
        println("element at $index is $value")
    }

    println("element at 4: ${sequence1.elementAt(4)}")
    println("element at 10: ${sequence1.elementAtOrElse(10) { it * 2 }}")
    println("element at 11: ${sequence1.elementAtOrNull(11)}")

    val firstFive = sequence1.take(5)
    println(firstFive.joinToString())
}