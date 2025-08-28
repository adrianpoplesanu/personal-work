package ro.adrianus.ReactiveResilieceTest.controller

import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RestController
import ro.adrianus.ReactiveResilieceTest.service.AdrianusService

@RestController
class IndexController(val adrianusService: AdrianusService) {

    @GetMapping("/")
    fun index(): String {
        val text: String? = adrianusService.getHomepage().block()
        return text ?: "no value"
    }
}