package type_issues

class ContainerTest {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            val values = mapOf(ContainerType.LINUX to 123L)
            val container = Container(values)
            println(container.params)
        }
    }
}