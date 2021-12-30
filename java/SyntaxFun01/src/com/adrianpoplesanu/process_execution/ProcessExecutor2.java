package com.adrianpoplesanu.process_execution;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ProcessExecutor2 {
    public static void test() throws IOException, InterruptedException {
        Runtime r = Runtime.getRuntime();
        Process p = r.exec("ls -la");
        p.waitFor();
        BufferedReader b = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = "";

        while ((line = b.readLine()) != null) {
            System.out.println(line);
        }

        b.close();
    }
}
