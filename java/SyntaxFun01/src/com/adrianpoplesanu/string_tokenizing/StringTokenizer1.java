package com.adrianpoplesanu.string_tokenizing;

public class StringTokenizer1 {
    public static void main(String[] args) {
        String path = "/Documents/docs/notes.txt";
        String[] elements = path.split("/");
        for (int i = 0; i < elements.length; i++) {
            System.out.println(elements[i]);
        }
        System.out.println(path.split("/").length);

        String path2 = "AA-/BB";
        System.out.println(path2.split("/").length - 1);
    }
}
