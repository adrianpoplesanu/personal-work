package ch01

class SimpleHelloWorld {
    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            println ("running a static main void in a class...")
        }
    }
}