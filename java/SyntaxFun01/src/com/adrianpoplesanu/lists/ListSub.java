package com.adrianpoplesanu.lists;

import java.util.ArrayList;
import java.util.List;

public class ListSub {
    public static void main(String[] args) {
        String folderName = "/users/apoplesanu/Documents";
        List<String> names = new ArrayList<>();
        for (String s : folderName.split("/")) {
            names.add(s);
        }

        for (int i = 1; i <= names.size(); i++) {
            System.out.println(String.join("-", names.subList(0, i)));
        }
    }
}
