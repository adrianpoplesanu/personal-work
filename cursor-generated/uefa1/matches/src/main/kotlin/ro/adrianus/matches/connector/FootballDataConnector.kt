package ro.adrianus.matches.connector

import org.slf4j.LoggerFactory
import org.springframework.stereotype.Component
import org.springframework.web.reactive.function.client.WebClient

@Component
class FootballDataConnector(
    private val webClient: WebClient
) {

    private val log = LoggerFactory.getLogger(javaClass)

    fun get(uri: String): String? {
        log.info("GET {}", uri)
        return webClient.get()
            .uri(uri)
            .retrieve()
            .bodyToMono(String::class.java)
            .block()
    }
}
