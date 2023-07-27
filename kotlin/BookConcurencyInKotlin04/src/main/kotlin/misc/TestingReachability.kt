package misc

fun test1() {
    println("test1")
    test2()
}

fun test2() {
    print ("test2")
}

fun main(args : Array<String>) {
    println("running reachability test")
    test1()
}