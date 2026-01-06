package ch05b

fun main(args: Array<String>) {
    val iterator1 = iterator {
        yield(1)
    }

    println("type1: ${iterator1.next().javaClass.simpleName}")

    val iterator2 : Iterator<Any> = iterator {
        yield(1)
        yield(3F)
        yield("aaa")
    }

    println("type2: ${iterator2.next().javaClass.simpleName}")
    println("type2: ${iterator2.next().javaClass.simpleName}")
    println("type2: ${iterator2.next().javaClass.simpleName}")

    val iterator3 : Iterator<Any> = iterator {
        yield(1)
        yield(3F)
        yield("aaa")
    }

    println("val3: ${iterator3.next()}")
    println("val3: ${iterator3.next()}")
    println("val3: ${iterator3.next()}")
}