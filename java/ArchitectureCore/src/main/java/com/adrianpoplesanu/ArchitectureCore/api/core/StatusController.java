package com.adrianpoplesanu.ArchitectureCore.api.core;

import com.adrianpoplesanu.ArchitectureCore.api.core.response.ApiResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

@RestController
@RequestMapping("/api/core")
public class StatusController {
    @GetMapping("/status")
    public Mono<ApiResponse<String>> status() {
        ApiResponse<String> apiResponse = new ApiResponse<>();
        apiResponse.setData("status: OK 200");
        return Mono.just(apiResponse);
    }

    @GetMapping("/check")
    public Flux<ApiResponse<String>> check() {
        ApiResponse<String> apiResponse = new ApiResponse<>();
        apiResponse.setData("it's working");
        return Flux.just(apiResponse);
    }

    @GetMapping("/void")
    public Mono<Void> nothing() {
        return Mono.empty();
    }
}
