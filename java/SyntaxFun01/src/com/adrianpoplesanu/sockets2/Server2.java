package com.adrianpoplesanu.sockets2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server2 {
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public Server2() {
        //...
    }

    public void start(int port) throws IOException, InterruptedException {
        serverSocket = new ServerSocket(port);
        clientSocket = serverSocket.accept();
        // https://stackoverflow.com/questions/10131377/socket-programming-multiple-client-to-one-server
        System.out.println("connection established");
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        while(true) {
            String request = in.readLine();
            System.out.println("CLIENT: " + request);
            out.println("ping");
            if (request.equals("exit")) break;
        }
        stop();
    }

    public void stop() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
        serverSocket.close();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Server2 server2 = new Server2();
        server2.start(5002);
    }
}
