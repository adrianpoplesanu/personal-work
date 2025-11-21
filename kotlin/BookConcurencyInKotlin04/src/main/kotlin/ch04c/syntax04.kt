package ch04c

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

fun launchExample1() {
    // CommonPool nu mai exista in kotlin a fost inlocuit cu Dispatchers.Default
    GlobalScope.launch(Dispatchers.Default) {
        // TODO: implement CPU-bound algorithm
        println("TODO: implement CPU-bound algorithm")
    }
}

fun launchExample2() {
    GlobalScope.launch {
        // TODO: implement suspending lambda here
        println("TODO: implement suspending lambda here")
    }
}

fun launchExample3() {
    // this was recommended by chatgpt
    val scope = CoroutineScope(Dispatchers.Default)
    scope.launch(Dispatchers.Default) {
        // TODO: implement suspending lambda here
        println("TODO: implement suspending lambda here")
    }
}

fun main(args: Array<String>) {
    launchExample1()
    launchExample2()
    launchExample3()
}