package syntax_fun

class ExampleClass {
    fun exampleMethod(): Int = withTimestamp {
        // Do something here
        val result = (1..1000).sum() // Example operation
        result
    }

    fun anotherMethod(): String = withTimestamp {
        // Another example operation
        Thread.sleep(1000) // Simulating some work
        "Hello, World!"
    }
}

fun main() {
    val example = ExampleClass()
    val result1 = example.exampleMethod()
    println("Result of exampleMethod(): $result1")

    val result2 = example.anotherMethod()
    println("Result of anotherMethod(): $result2")
}
