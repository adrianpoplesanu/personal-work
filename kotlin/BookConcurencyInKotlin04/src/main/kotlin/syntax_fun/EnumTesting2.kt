package syntax_fun

class EnumTesting2 {
    enum class AnimalType {
        DOG {
            override fun getType(): String {
                return "dog_type"
            }
        },
        CAT {
            override fun getType(): String {
                return "cat_type"
            }
        },
        UNKNOWN {
            override fun getType(): String {
                return "unknown_type"
            }
        };

        abstract fun getType(): String

        companion object {
            fun getValueOf(value: String): AnimalType {
                return try {
                    AnimalType.valueOf(value)
                } catch (e: Exception) {
                    UNKNOWN
                }
            }
        }
    }

    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            println ("running...")
            println (AnimalType.getValueOf("DOG").getType())
            println (AnimalType.getValueOf("CAT").getType())
            println (AnimalType.getValueOf("HORSE").getType())
        }
    }
}