package com.adrianpoplesanu.RestTemplateDemo1.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.client.RestTemplate;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

@Controller
public class HomeController {
    @GetMapping
    @ResponseBody
    public String index() {
        Connector connector = new Connector();
        Object response = connector.get(ResponseMessage.class, "http://localhost:8080/data-mapping", Collections.emptyMap()).getBody();
        List<Object> messages = ((ResponseMessage) response).getMessages(); // asta merge
        System.out.println("unable errors=%s".formatted(messages));
        List<Object> messages2 = new ArrayList<>();
        messages2.add(new ErrorMessage("bedus", "catelus"));
        System.out.println("unable errors2=%s".formatted(messages2));
        return response.toString();
    }

    @GetMapping("index2")
    @ResponseBody
    public List<TestEntity> index2() {
        Connector connector = new Connector();
        List<TestEntity> response = asList(connector.get(TestEntity[].class, "http://localhost:8080/multi-data", Collections.emptyMap()).getBody());
        for (TestEntity testEntity : response) {
            System.out.println(testEntity.getAaa());
        }
        return response;
    }

    @GetMapping("data-mapping")
    @ResponseBody
    public String mappingtest() {

        //return "{\"code\":\"aaa\", \"value\":\"bbb\", \"messages\":[\"dex\", \"ham ham ham\"]}";
        return "{\"code\":\"aaa\", \"value\":\"bbb\", \"messages\":[{\"code\":\"dex\", \"info\":\"ham ham ham\"}]}";
    }

    @GetMapping("multi-data")
    @ResponseBody
    public String multimappingtest() {
        return "[{\"aaa\": \"01\"}, {\"aaa\": \"02\"}]";
    }

    private static <T> List<T> asList(T... a) {
        return a == null ? Collections.emptyList() : Arrays.asList(a);
    }
}
