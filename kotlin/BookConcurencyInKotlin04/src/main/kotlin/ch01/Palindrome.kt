package ch01

fun isPalindrome(word : String) : Boolean {
    return word == word.reversed()
}

fun filterPalindromes(words : List<String>) : List<String> {
    return words.filter { word -> isPalindrome(word) }
}

fun main(args : Array<String>) {
    var words = listOf("aaa", "aaab", "bbb", "baaa", "aba", "abaa", "bab")
    var palindromes = filterPalindromes(words)
    println(palindromes)
}