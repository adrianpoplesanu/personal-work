package aaa

import java.io.File

fun isPalindrome(word : String) : Boolean {
    return word == word.reversed()
}

fun filterPalindromes(words : List<String>) : List<String> {
    return words.filter { word -> isPalindrome(word) }
}

fun readWordsFromJson(fileName : String) : String {
    return File(fileName).readText(Charsets.UTF_8)
}

fun main(args : Array<String>) {
    val words = readWordsFromJson("resources/words.json")
    println(words)
}