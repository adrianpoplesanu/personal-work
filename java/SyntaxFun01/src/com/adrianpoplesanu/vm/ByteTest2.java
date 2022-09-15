package com.adrianpoplesanu.vm;

import java.nio.ByteBuffer;

public class ByteTest2 {
    public static void main(String[] args) {
        System.out.println("testing the bytes");

        byte[] instruction = new byte[2];

        int offset = 0;
        ByteBuffer b = ByteBuffer.allocate(4);
        b.putInt(65534);
        byte[] result = b.array();
        instruction[offset] = result[2];
        instruction[offset + 1] = result[3];

        for (byte ins : instruction) {
            System.out.println(Byte.toUnsignedInt(ins));
        }
    }
}
