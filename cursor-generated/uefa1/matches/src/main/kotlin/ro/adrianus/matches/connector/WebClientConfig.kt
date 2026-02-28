package ro.adrianus.matches.connector

import org.springframework.beans.factory.annotation.Value
import org.springframework.context.annotation.Bean
import org.springframework.context.annotation.Configuration
import org.springframework.web.reactive.function.client.WebClient

@Configuration
class WebClientConfig {

    @Bean
    fun webClient(
        @Value("\${football-data.base-url:https://api.football-data.org}") baseUrl: String,
        @Value("\${football-data.auth-token:}") authToken: String
    ): WebClient {
        val builder = WebClient.builder().baseUrl(baseUrl)
        if (authToken.isNotBlank()) {
            builder.defaultHeader("X-Auth-Token", authToken)
        }
        return builder.build()
    }
}
