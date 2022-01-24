package com.adrianpoplesanu.BlueAlert.tester;

import com.adrianpoplesanu.BlueAlert.StompPrincipal;
import com.adrianpoplesanu.BlueAlert.model.Message;
import com.adrianpoplesanu.BlueAlert.model.User;
import com.adrianpoplesanu.BlueAlert.service.UserService;
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

    //@Autowired
    //private UserService userService;

    @MessageMapping("/register")
    @SendTo("/topic/register")
    public Message index(Message message, Principal principal, @Header("simpSessionId") String sessionId) {
        //System.out.println(sessionId);
        //System.out.println(principal.getName());
        //System.out.println(message.getData());

        //System.out.println(userService.size());
        StompPrincipal stompPrincipal = (StompPrincipal) principal;
        if (stompPrincipal.getUser() != null) {
            System.out.println(stompPrincipal.getUser().getName());
        } else {
            System.out.println("user not set for this principal, setting it now");
            stompPrincipal.setUser(new User("bedush"));
        }
        //userService.addEntry(principal.getName(), "bedush");
        simpMessagingTemplate.convertAndSendToUser(principal.getName(), "topic/reply", "neata");
        System.out.println(simpUserRegistry.getUserCount());
        return new Message("buna dimineata");
    }
}
