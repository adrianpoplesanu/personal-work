package com.adrianpoplesanu.vm;

public class ByteTest3 {
    public static void main(String[] args) {
        System.out.println(OpcodeEnum.OP_CONSTANT);
        System.out.println(OpcodeEnum.OP_CONSTANT.ordinal());
        System.out.println(Byte.toUnsignedInt((byte) OpcodeEnum.OP_CONSTANT.ordinal()));

        System.out.println(OpcodeEnum.OP_ADD);
        System.out.println(OpcodeEnum.OP_ADD.ordinal());
        System.out.println(Byte.toUnsignedInt((byte) OpcodeEnum.OP_ADD.ordinal()));
    }
}
