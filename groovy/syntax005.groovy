class LoopsFun {
    static void main(String[] args) {
        def elements = ["1", "2", "3"]
        println elements[0..-2]
        println elements[0..-1]
        elements.each {
            println it
        }
        elements.each {
            println "aaa ${it} bbb"
        }
    }
}
