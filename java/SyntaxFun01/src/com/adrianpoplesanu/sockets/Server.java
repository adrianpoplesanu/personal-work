package com.adrianpoplesanu.sockets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public Server() {
        //...
    }

    public void start(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        clientSocket = serverSocket.accept();
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        String greeting = in.readLine();
        if ("hello server".equals(greeting)) {
            out.println("hello client");
            System.out.println("hello client");
        }
        else {
            out.println("unrecognised greeting");
            System.out.println("unrecognised greeting");
            System.out.println(greeting);
        }
    }

    public void stop() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
        serverSocket.close();
    }

    public static void main(String[] args) throws IOException {
        Server server = new Server();
        server.start(5002);
    }
}
