package syntax_fun

class EnumTesting {
    enum class AnimalType {
        DOG,
        CAT,
        HORSE,
        UNKNOWN
    }

    companion object {
        @JvmStatic
        fun main(args : Array<String>) {
            println("running enum testing...")
            var animalType : AnimalType = AnimalType.valueOf("DOG")
            println(animalType)
            animalType = AnimalType.valueOf("CAT")
            println(animalType)
            try {
                animalType = AnimalType.valueOf("CACA_MACA")
            } catch (e: Exception) {
                animalType = AnimalType.UNKNOWN
            }
            println(animalType)
        }
    }
}