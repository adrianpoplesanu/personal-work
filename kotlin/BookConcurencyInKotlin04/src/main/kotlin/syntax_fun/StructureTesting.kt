// s/usr/asr/ ... lowercase + uppercase

package syntax_fun

class UsrResiliencyFeatures(name: String, threshold: Int) {
    companion object {
        fun builder(): UsrResiliencyFeatures {
            return UsrResiliencyFeatures("undefined", 1)
        }
    }

    var name: String = name
    var threshold: Int = threshold

    fun build(): UsrResiliencyFeatures {
        return UsrResiliencyFeatures("undefined", 1)
    }

    fun build(name: String, threshold: Int): UsrResiliencyFeatures {
        return UsrResiliencyFeatures(name, threshold)
    }
}

fun <T> UsrResiliencyFeatures.circuitBreaker(block: () -> T): T {
    println(name)
    println(threshold)
    return block()
}

class UsrResiliencyFeaturesDsl(name: String) {
    private val builder = UsrResiliencyFeatures.builder()
    var threshold: Int = 0
    var name = name

    internal fun build() = builder.build(name, threshold)
}

fun resiliency2(name: String, dsl: UsrResiliencyFeaturesDsl.() -> Unit): UsrResiliencyFeatures =
    UsrResiliencyFeaturesDsl(name).also(dsl).build()

class UcpService {
    private val resiliency = resiliency2("ucp-service") {
        threshold = 10
    }

    fun upload() {
        resiliency.circuitBreaker {
            println("running something through a circuit breaker wrapper")
        }
    }
}

fun main(args: Array<String>) {
    val ucpService = UcpService()
    ucpService.upload()
}