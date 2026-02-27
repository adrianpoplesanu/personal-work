package ro.adrianus.matches.connector

import org.springframework.beans.factory.annotation.Value
import org.springframework.context.annotation.Bean
import org.springframework.context.annotation.Configuration
import org.springframework.web.reactive.function.client.WebClient

@Configuration
class WebClientConfig {

    @Bean
    fun webClient(
        @Value("\${football-data.base-url:https://api.football-data.org}") baseUrl: String
    ): WebClient = WebClient.builder()
        .baseUrl(baseUrl)
        .build()
}
