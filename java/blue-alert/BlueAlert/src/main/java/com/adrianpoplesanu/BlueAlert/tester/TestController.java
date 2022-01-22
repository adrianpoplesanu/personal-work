package com.adrianpoplesanu.BlueAlert.tester;

import com.adrianpoplesanu.BlueAlert.model.Message;
import org.springframework.messaging.handler.annotation.Header;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;

@Controller
public class TestController {
    @MessageMapping("/hello")
    @SendTo("/topic/greetings")
    public Message index(Message message, @Header("simpSessionId") String sessionId) {
        System.out.println(sessionId);
        return new Message("buna dimineata");
    }
}
