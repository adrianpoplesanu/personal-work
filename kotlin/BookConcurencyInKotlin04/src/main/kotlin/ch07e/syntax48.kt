package ch07e

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.channels.actor

suspend fun main(args: Array<String>) {
    val bufferedPrinter = GlobalScope.actor<String>(capacity = 10) {
        for (message in channel) {
            println(message)
        }
    }

    bufferedPrinter.send("hello1")
    bufferedPrinter.send("world1")
    bufferedPrinter.send("hello2")
    bufferedPrinter.send("world2")
    bufferedPrinter.send("hello3")
    bufferedPrinter.send("world3")
    bufferedPrinter.send("hello4")
    bufferedPrinter.send("world4")
    bufferedPrinter.send("hello5")
    bufferedPrinter.send("world5")
    bufferedPrinter.send("hello6")
    bufferedPrinter.send("world6")
    bufferedPrinter.send("hello7")
    bufferedPrinter.send("world7")
    bufferedPrinter.send("hello8")
    bufferedPrinter.send("world8")
    bufferedPrinter.send("hello9")
    bufferedPrinter.send("world9")
    bufferedPrinter.send("hello10")
    bufferedPrinter.send("world10")
    bufferedPrinter.send("hello11")
    bufferedPrinter.send("world11")
    bufferedPrinter.send("hello12")
    bufferedPrinter.send("world12")
    bufferedPrinter.send("hello13")
    bufferedPrinter.send("world13")

    bufferedPrinter.close()
}