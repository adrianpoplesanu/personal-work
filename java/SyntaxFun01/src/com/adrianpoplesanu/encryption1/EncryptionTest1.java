package com.adrianpoplesanu.encryption1;

import java.security.*;

public class EncryptionTest1 {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
        keyPairGenerator.initialize(2048);
        KeyPair keyPair = keyPairGenerator.generateKeyPair();

        PublicKey publicKey = keyPair.getPublic();
        PrivateKey privateKey = keyPair.getPrivate();

        System.out.println(publicKey);
        System.out.println(privateKey);

        System.out.println("Public Key: " + java.util.Base64.getEncoder().encodeToString(publicKey.getEncoded()));
        System.out.println("Private Key: " + java.util.Base64.getEncoder().encodeToString(privateKey.getEncoded()));
    }
}
