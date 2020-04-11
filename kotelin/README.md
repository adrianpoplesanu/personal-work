Download Kotelin compiler and add it to PATH system variable:

https://github.com/JetBrains/kotlin/releases/tag/v1.3.71

Example of running Kotelin code:

$ cat hello.kt
fun main(args: Array<String>) {
    println("Hello, World!")
}

$ /Users/adrianpoplesanu/Documents/kotelin/kotlin-native-macos-1.3.71/bin/kotlinc hello.kt -include-runtime -d hello.jar
$ kotlinc -help
$ java -jar hello.jar
