package com.adrianpoplesanu.parallel_repl;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;

    public Repl() {
        this.scanner = new Scanner(System.in);
    }

    public void loop() {
        while(true) {
            System.out.print(">> ");
            String source = scanner.nextLine();
            if (!source.equals("")) System.out.println(source);
            if (source.equals("exit()")) break;
        }
    }
}
