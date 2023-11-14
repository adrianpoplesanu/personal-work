package syntax_fun

class QualifierSplitter {

    private val ccc = "ccc"

    fun buildQualifiers(raw: String): Map<String, String> {
        val qualifiers = mutableMapOf<String, String>()
        try {
            raw.split(";").forEach {
                val keyPairValues = it.split("=")
                qualifiers[keyPairValues[0]] = keyPairValues[1]
            }
        } catch(e: Exception) {
            return emptyMap()
        }
        return qualifiers
    }

    fun printCCC() {
        val qualifierMap = buildQualifiers("aaa=bbb;ccc=ddd")
        println (qualifierMap[ccc] ?: "null")
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val qualifierSplitter = QualifierSplitter()
            val qualifierMap = qualifierSplitter.buildQualifiers("aaa=bbb;ccc=ddd")
            for (q in qualifierMap) {
                println ("${q.key}@${q.value}")
            }
            qualifierSplitter.printCCC()
        }
    }
}