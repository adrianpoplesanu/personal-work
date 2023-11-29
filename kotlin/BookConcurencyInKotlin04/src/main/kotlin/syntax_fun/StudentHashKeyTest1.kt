package syntax_fun

class StudentHashKeyTest1 {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            println(StudentHashKey1.HK_STUDENT)
            println(StudentHashKey1.HK_STUDENT.value)

            /*val keys = mutableListOf<String>()
            for (key in StudentHashKey1.values()) {
                keys.add(key.value)
            }*/
            val keys = StudentHashKey1.values().map { it.value }.toList() as MutableList<String>
            println(keys)
        }
    }
}