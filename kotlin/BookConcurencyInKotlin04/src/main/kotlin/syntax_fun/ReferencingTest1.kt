package syntax_fun

class Dog {
    var name = "bebe"
    var address = "craiova"

    fun set2() {
        name = "dex"
        address = "berceni"
    }

    fun set3() {
        val name = "aaa"
        println(name)
        val address = "bbb"
        println(address)
    }
}

fun main() {
    val dog = Dog()
    println(dog.name)
    println(dog.address)
    dog.set2()
    println(dog.name)
    println(dog.address)
    dog.set3()
    println(dog.name)
    println(dog.address)
}