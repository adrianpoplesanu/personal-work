package ch01

import kotlinx.coroutines.*
import kotlin.system.measureTimeMillis

class Palindrome5 {

    private fun isPalindrome(word : String): Boolean {
        return word == word.reversed()
    }

    private suspend fun filterPalindromes(words : List<String>): List<String> {
        return words.filter { word -> isPalindrome(word) }
    }

    suspend fun getAllPalindromes(batchSize : Int): List<String> {
        var words = readWordsFromJson("/words2.json")
        var result : List<String> = mutableListOf()

        val steps = words.size / batchSize + if (words.size % batchSize != 0) 1 else 0
        var partialResults = mutableListOf<Deferred<List<String>>>()

        for (i in 0 until steps) {
            println("step ${i}: ${words.subList(i * batchSize, Math.min((i + 1) * batchSize, words.size))}")
            var partialResult = GlobalScope.async { filterPalindromes(words.subList(i * batchSize, Math.min((i + 1) * batchSize, words.size))) }
            partialResults.add(partialResult)
        }

        for (i in 0 until steps) {
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
                var palindrome5 = Palindrome5()
                val palindromes = palindrome5.getAllPalindromes(5)
                println(palindromes)
            }
            println ("took $time miliseconds")
        }
    }
}