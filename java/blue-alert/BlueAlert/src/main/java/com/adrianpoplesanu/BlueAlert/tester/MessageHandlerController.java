package com.adrianpoplesanu.BlueAlert.tester;

import com.adrianpoplesanu.BlueAlert.model.Message;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.Header;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.messaging.simp.user.SimpUserRegistry;
import org.springframework.stereotype.Controller;

import java.security.Principal;

@Controller
public class MessageHandlerController {
    @Autowired
    private SimpMessagingTemplate simpMessagingTemplate;
    @Autowired
    private SimpUserRegistry simpUserRegistry;

    @MessageMapping("/register")
    @SendTo("/topic/register")
    public Message index(Message message, Principal principal, @Header("simpSessionId") String sessionId) {
        System.out.println(sessionId);
        System.out.println(principal.getName());
        simpMessagingTemplate.convertAndSendToUser(principal.getName(), "topic/reply", "neata");
        System.out.println(simpUserRegistry.getUserCount());
        return new Message("buna dimineata");
    }
}
