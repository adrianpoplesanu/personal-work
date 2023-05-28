import elvis.Elvis

fun main(args: Array<String>) {
    println("Hello World!")

    println("Program arguments: ${args.joinToString()}")

    val elvis = Elvis();
    elvis.test()
    elvis.test2()
    elvis.test3(null)
}