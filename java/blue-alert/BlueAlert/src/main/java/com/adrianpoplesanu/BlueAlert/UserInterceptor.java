package com.adrianpoplesanu.BlueAlert;

import org.springframework.messaging.Message;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.simp.SimpMessageHeaderAccessor;
import org.springframework.messaging.simp.stomp.StompCommand;
import org.springframework.messaging.simp.stomp.StompHeaderAccessor;
import org.springframework.messaging.support.ChannelInterceptor;
import org.springframework.messaging.support.MessageHeaderAccessor;

import java.util.ArrayList;
import java.util.Map;

public class UserInterceptor implements ChannelInterceptor {
    // https://huongdanjava.com/send-stomp-message-to-a-specific-user-with-spring-websocket.html
    // https://www.baeldung.com/websockets-spring
    // https://docs.spring.io/spring-framework/docs/4.3.x/spring-framework-reference/html/websocket.html

    @Override
    public Message<?> preSend(Message<?> message, MessageChannel channel) {
        StompHeaderAccessor accessor = MessageHeaderAccessor.getAccessor(message, StompHeaderAccessor.class);

        if (StompCommand.CONNECT.equals(accessor.getCommand())) {
            Object raw = message.getHeaders().get(SimpMessageHeaderAccessor.NATIVE_HEADERS);

            if (raw instanceof Map) {
                Object name = ((Map) raw).get("username");
                System.out.println(name);

                if (name instanceof ArrayList) {
                    accessor.setUser(new StompPrincipal(((ArrayList<String>) name).get(0).toString()));
                }
            }
        }
        return message;
    }
}
