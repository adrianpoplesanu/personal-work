package ch01

class OperatorOverloading {

    class Name {
        lateinit var value : String

        operator fun plus(other : Name) : Name {
            val result = Name()
            result.value = value + ":::" + other.value
            return result
        }

        operator fun plus(other : String) : Name {
            val result = Name()
            result.value = "$value:::$other"
            return result
        }
    }

    fun execute() {
        val bebe = Name()
        val dex = Name()

        bebe.value = "bebe"
        dex.value = "dex"

        println((bebe + dex).value)
        println((bebe + "dex" + "12").value)
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            val operatorOverloading = OperatorOverloading()
            operatorOverloading.execute()
        }
    }
}