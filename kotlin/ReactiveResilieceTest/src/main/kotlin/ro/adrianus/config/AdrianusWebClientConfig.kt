package ro.adrianus.config

import org.springframework.context.annotation.Bean
import org.springframework.context.annotation.Configuration
import org.springframework.web.reactive.function.client.WebClient

@Configuration
class AdrianusWebClientConfig {

    @Bean
    fun adrianusWebClient(builder: WebClient.Builder): WebClient {
        return builder.build()
    }
}