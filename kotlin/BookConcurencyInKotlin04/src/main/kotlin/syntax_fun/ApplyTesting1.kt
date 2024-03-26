package syntax_fun

class ApplyTesting1 {
    class Elev {
        var nume: String = "aaa"
        var nota: Int = 12

        override fun toString(): String {
            return "Elev(nume='$nume', nota=$nota)"
        }
    }

    fun run() {
        //var nume = "ccc"
        val e = Elev().apply {
            nume = "bbb" // daca las linia 14 atunci asta nu se executa
            nota = 13
        }
        println(e)
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val applyTesting1 = ApplyTesting1()
            applyTesting1.run()
        }
    }
}