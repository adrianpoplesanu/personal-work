package ro.adrianus.service

import io.github.resilience4j.circuitbreaker.CircuitBreakerRegistry
import io.github.resilience4j.reactor.circuitbreaker.operator.CircuitBreakerOperator
import io.github.resilience4j.retry.RetryRegistry
import org.slf4j.LoggerFactory
import org.springframework.stereotype.Service
import org.springframework.web.reactive.function.client.WebClient
import reactor.core.publisher.Mono

@Service
class AdrianusService(private val adrianusWebClient: WebClient,
                      circuitBreakerRegistry: CircuitBreakerRegistry,
                      retryRegistry: RetryRegistry
) {
    private val logger = LoggerFactory.getLogger(AdrianusService::class.java)
    private val circuitBreaker = circuitBreakerRegistry.circuitBreaker("webClientCircuitBreaker")
    private val retry = retryRegistry.retry("webClientRetry")

    fun fetchUrl(url: String): Mono<String> {
        return adrianusWebClient
            .get()
            .uri(url)
            .retrieve()
            .bodyToMono(String::class.java)
            .transformDeferred(CircuitBreakerOperator.of(circuitBreaker))
            /*.transformDeferred {
                logger.info("issue deferring")
                return@transformDeferred Mono.just("your value")
            }*/
            .onErrorResume { ex ->
                Mono.just("Fallback: could not fetch content. Reason: ${ex.message}")
            }
    }
}