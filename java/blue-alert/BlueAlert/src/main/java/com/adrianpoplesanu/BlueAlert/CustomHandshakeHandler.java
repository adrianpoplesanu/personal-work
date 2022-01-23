package com.adrianpoplesanu.BlueAlert;

import org.springframework.http.HttpHeaders;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServletServerHttpRequest;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.server.support.DefaultHandshakeHandler;

import javax.servlet.http.HttpServletRequest;
import java.io.IOException;
import java.security.Principal;
import java.util.Map;

public class CustomHandshakeHandler extends DefaultHandshakeHandler {
    // Custom class for storing principal
    @Override
    protected Principal determineUser(
            ServerHttpRequest request,
            WebSocketHandler wsHandler,
            Map<String, Object> attributes
    ) {
        // Generate principal with UUID as name
        //return new StompPrincipal(UUID.randomUUID().toString());
        /*ServletServerHttpRequest servletRequest = (ServletServerHttpRequest) request;
        HttpServletRequest httpServletRequest = servletRequest.getServletRequest();
        System.out.println(httpServletRequest.getParameter("username"));
        HttpHeaders headers = request.getHeaders();*/
        try {
            System.out.println(request.getBody().toString());
        } catch (IOException e) {
            System.out.println("nu stiu ce s-a intamplat!");
        }
        return new StompPrincipal("aici trebuie sa fie ceva unic, care ar trebui sa vina de la client");
    }
}
