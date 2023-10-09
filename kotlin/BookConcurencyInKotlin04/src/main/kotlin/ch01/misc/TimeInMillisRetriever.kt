package ch01.misc

class TimeInMillisRetriever {
    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            println (System.currentTimeMillis())
        }
    }
}