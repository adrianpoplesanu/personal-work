package syntax_fun

class ResiliencyFeatureDsl {
    var name = "resiliency-name"

    fun also2(block: (ResiliencyFeatureDsl) -> Unit): ResiliencyFeatureDsl {
        block(this)
        return this
    }
}

fun resiliency(name: String, dsl: ResiliencyFeatureDsl.() -> Unit): ResiliencyFeatureDsl {
    return ResiliencyFeatureDsl().also(dsl)
}

fun resiliency(dsl: ResiliencyFeatureDsl.() -> Unit) {
    ResiliencyFeatureDsl().also2(dsl)
}

fun main() {
    val resiliencyFeatureDsl = resiliency("ala bala portocala") {
        println("buna dimineata!")
        name = "resiliency-name-test"
    }
    println(resiliencyFeatureDsl)
    println(resiliencyFeatureDsl.name)

    val resiliencyFeatureDsl2 = resiliency("ala bala portocala") {
        name = "resiliency-also2"
    }

    println(resiliencyFeatureDsl2)
    println((resiliencyFeatureDsl2 as ResiliencyFeatureDsl).name)
}