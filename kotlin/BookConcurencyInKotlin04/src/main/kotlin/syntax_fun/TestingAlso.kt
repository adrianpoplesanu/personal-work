package syntax_fun

class ResiliencyFeatureDsl {
    var name = "resiliency-name"
}

fun resiliency(name: String, dsl: ResiliencyFeatureDsl.() -> Unit): ResiliencyFeatureDsl {
    return ResiliencyFeatureDsl().also(dsl)
}

fun resiliency(dsl: ResiliencyFeatureDsl.() -> Unit) {
    ResiliencyFeatureDsl().also(dsl)
}

fun main() {
    val resiliencyFeatureDsl = resiliency("ala bala portocala") {
        println("buna dimineata!")
        name = "resiliency-name-test"
    }
    println(resiliencyFeatureDsl)
    println(resiliencyFeatureDsl.name)
}