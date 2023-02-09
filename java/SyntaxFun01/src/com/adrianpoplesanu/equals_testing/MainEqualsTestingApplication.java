package com.adrianpoplesanu.equals_testing;

public class MainEqualsTestingApplication {
    public static void main(String[] args) {
        System.out.println("running equals testing...");

        Client1 client1 = new Client1("Alina", 23);
        Client1 client2 = new Client1("Mara", 25);
        System.out.println(client1.equals(client2));
        System.out.println(client1 == client2);

        System.out.println("============");

        Client1 client3 = new Client1("Alina", 23);
        Client1 client4 = new Client1("Alina", 23);
        System.out.println(client3.equals(client4));
        System.out.println(client3 == client4);

        System.out.println("============");

        Client2 client5 = new Client2("Alina", 23);
        Client2 client6 = new Client2("Mara", 25);
        System.out.println(client5.equals(client6));
        System.out.println(client5 == client6);

        System.out.println("============");

        Client2 client7 = new Client2("Alina", 23);
        Client2 client8 = new Client2("Alina", 23);
        System.out.println(client7.equals(client8));
        System.out.println(client7 == client8);
    }
}
