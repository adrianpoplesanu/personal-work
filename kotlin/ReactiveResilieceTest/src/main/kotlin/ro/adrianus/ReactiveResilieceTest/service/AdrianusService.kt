package ro.adrianus.ReactiveResilieceTest.service

import org.springframework.stereotype.Service
import reactor.core.publisher.Mono

@Service
class AdrianusService {
    fun getHomepage(): Mono<String> {
        return Mono.empty()
    }
}