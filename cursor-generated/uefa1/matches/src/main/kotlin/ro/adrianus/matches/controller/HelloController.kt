package ro.adrianus.matches.controller

import org.slf4j.LoggerFactory
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RestController
import ro.adrianus.matches.service.FootballDataService

@RestController
class HelloController(
    private val footballDataService: FootballDataService
) {

    private val log = LoggerFactory.getLogger(javaClass)

    @GetMapping("/hello")
    fun hello(): ResponseEntity<String> {
        log.info("GET /hello requested")
        return ResponseEntity.ok("Hello, World!")
    }

    @GetMapping("/matches")
    fun matches(): ResponseEntity<String> {
        log.info("GET /matches requested")
        val result = footballDataService.retrieveMatches()
        return ResponseEntity.ok(result ?: "No matches found")
    }
}
