package ro.adrianus.controller

import org.slf4j.LoggerFactory
import org.springframework.http.HttpStatus
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RestController
import org.springframework.web.server.ResponseStatusException
import ro.adrianus.service.AdrianusService
import java.util.*

@RestController
class IndexController(val adrianusService: AdrianusService) {
    private val logger = LoggerFactory.getLogger(IndexController::class.java)

    @GetMapping("/")
    fun index(): String {
        //val text: String? = adrianusService.fetchUrl("http://adrianus.ro").block()
        //val text: String? = adrianusService.fetchUrl("http://localhost:8080/adrianus-simulation").block()
        val text: String? = adrianusService.fetchUrl("http://localhost:8080/adrianus-error").block()
        return text ?: "no value"
    }

    @GetMapping("/adrianus-simulation")
    fun simulation(): String {
        return "it works! uuid: ${UUID.randomUUID()}"
    }

    @GetMapping("/adrianus-error")
    fun error(): String {
        logger.info("calling /adrianus-error")
        throw ResponseStatusException(HttpStatus.INTERNAL_SERVER_ERROR, "This endpoint always fails")
        //return "it works! uuid: ${UUID.randomUUID()}"
    }
}