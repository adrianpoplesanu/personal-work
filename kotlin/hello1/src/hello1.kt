data class Money(val amount: Int, val currency: String)

fun main() {
    println("fun with Kotelin!!!")
    val tickets = Money(100, "$")
    println (tickets)
}