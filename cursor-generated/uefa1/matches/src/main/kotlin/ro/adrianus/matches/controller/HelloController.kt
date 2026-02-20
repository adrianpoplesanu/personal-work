package ro.adrianus.matches.controller

import org.slf4j.LoggerFactory
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RestController

@RestController
class HelloController {

    private val log = LoggerFactory.getLogger(javaClass)

    @GetMapping("/hello")
    fun hello(): ResponseEntity<String> {
        log.info("GET /hello requested")
        return ResponseEntity.ok("Hello, World!")
    }
}
