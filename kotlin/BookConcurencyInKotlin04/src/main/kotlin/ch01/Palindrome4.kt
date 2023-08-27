package ch01

import kotlinx.coroutines.*
import kotlin.system.measureTimeMillis

class Palindrome4 {

    private fun isPalindrome(word : String): Boolean {
        return word == word.reversed()
    }

    private suspend fun filterPalindromes(words : List<String>): List<String> {
        return words.filter { word -> isPalindrome(word) }
    }

    suspend fun getAllPalindromes(n : Int): List<String> {
        var words = readWordsFromJson("/words2.json")
        var result : List<String> = mutableListOf()

        val batchSize = words.size / n
        var partialResults = mutableListOf<Deferred<List<String>>>()

        for (i in 0 until n) {
            var partialResult = GlobalScope.async { filterPalindromes(words.subList(i * batchSize, (i + 1) * batchSize - 1)) }
            partialResults.add(partialResult)
        }

        for (i in 0 until n) {
            val partial = partialResults[i].await()
            result += partial
        }
        return result
    }

    fun readWordsFromJson(fileName : String): List<String> {
        return this::class.java.getResourceAsStream(fileName)?.bufferedReader()?.readLines() ?: listOf()
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) = runBlocking {
            val time = measureTimeMillis {
                var palindrome4 = Palindrome4()
                val palindromes = palindrome4.getAllPalindromes(1)
                println(palindromes)
            }
            println ("took $time miliseconds")
        }
    }
}