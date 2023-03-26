package com.adrianpoplesanu.sockets2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Client2 {
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public void startConnection(String ip, int port) throws IOException {
        clientSocket = new Socket(ip, port);
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    }

    public String sendMessage(String msg) throws IOException {
        out.println(msg);
        String resp = in.readLine();
        return resp;
    }

    public void stopConnection() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Client2 client2 = new Client2();
        client2.startConnection("127.0.0.1", 5002);
        String response;
        while (true) {
            Thread.sleep(1000);
            response = client2.sendMessage("buna dimineata!");
            System.out.println("SERVER: " + response);
            if (response.equals("close")) {
                break;
            }
        }
        client2.stopConnection();
        System.out.println(response);
    }
}
