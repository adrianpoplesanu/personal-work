package com.adrianpoplesanu.RestTemplateDemo1.controller;

import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;

import org.springframework.http.HttpHeaders;
import org.springframework.web.client.RestTemplate;

import java.net.URI;
import java.util.Collections;
import java.util.Map;

public class Connector {
    private static final HttpHeaders NO_HEADERS = new ImmutableHttpHeaders();
    RestTemplate restTemplate = new RestTemplate();
    public<T> ResponseEntity<T> get(Class<T> responseType, String path, Map<String, Object> uriVariables) {
        // TODO: check mapping
        return this.get(responseType, path, uriVariables, NO_HEADERS);
    }

    public<T> ResponseEntity<T> get(Class<T> responseType, String path, Map<String, Object> uriVariables, HttpHeaders headers) {
        return this.exchange(HttpMethod.GET, (Object) null, responseType, path, uriVariables, headers);
    }

    public <S, T> ResponseEntity<T> exchange(HttpMethod method, S requestBody, Class<T> responseType, String path, Map<String, Object> uriVariables, HttpHeaders headers) {
        String url = path;
        uriVariables = Collections.emptyMap();

        URI uri = this.restTemplate.getUriTemplateHandler().expand(url, uriVariables);
        return this.exchange(method, requestBody, responseType, uri, headers);
    }

    public <S, T> ResponseEntity<T> exchange(HttpMethod method, S requestBody, Class<T> responseType, URI uri, HttpHeaders explicitHeaders) {
        HttpHeaders headers = new HttpHeaders();
        HttpEntity<S> httpEntity = new HttpEntity<>(requestBody, headers);
        return this.restTemplate.exchange(uri, method, httpEntity, responseType);
    }
}
