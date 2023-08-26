package ch01

import java.io.File

class Palindrome3 {
    fun isPalindrome(word : String) : Boolean {
        return word == word.reversed()
    }

    fun filterPalindromes(words : List<String>) : List<String> {
        return words.filter { word -> isPalindrome(word) }
    }

    fun readWordsFromJson(fileName : String) : String {
        //return this::class.java.getResource(fileName)?.readText(Charsets.UTF_8) ?: "not found"
        return File(fileName).readText(Charsets.UTF_8)
    }

    fun readWordsFromJson2(fileName : String) : String {
        return this::class.java.getResource(fileName)?.readText(Charsets.UTF_8) ?: "not found"
    }
}

fun main(args : Array<String>) {
    var palindrome3 = Palindrome3()
    val words = palindrome3.readWordsFromJson("/Users/adrianpoplesanu/Documents/git-projects/personal-work/kotlin/BookConcurencyInKotlin04/src/main/resources/words.json")
    println(words)

    val words2 = palindrome3.readWordsFromJson2("/words.json")
    println(words2)

    //val palindromes = palindrome3.filterPalindromes(words)
    //println(palindromes)
}