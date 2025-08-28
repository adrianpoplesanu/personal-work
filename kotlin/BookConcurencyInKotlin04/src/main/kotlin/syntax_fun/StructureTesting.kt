// s/usr/asr/ ... lowercase + uppercase

package syntax_fun

class UsrResiliencyFeatures {
    companion object {
        fun builder(): UsrResiliencyFeatures {
            return UsrResiliencyFeatures()
        }
    }

    fun build(): UsrResiliencyFeatures {
        return UsrResiliencyFeatures()
    }
}

fun <T> UsrResiliencyFeatures.circuitBreaker(block: () -> T): T {
    return block()
}

class UsrResiliencyFeaturesDsl(name: String) {
    private val builder = UsrResiliencyFeatures.builder()
    var threshold: Int = 0

    internal fun build() = builder.build()
}

fun resiliency2(name: String, dsl: UsrResiliencyFeaturesDsl.() -> Unit): UsrResiliencyFeatures =
    UsrResiliencyFeaturesDsl(name).also(dsl).build()

class UcpService {
    private val resiliency = resiliency2("acp-service") {
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