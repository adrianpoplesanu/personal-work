package com.adrianpoplesanu.process_execution;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ProcessExecutor6 {
    private static void printResults(Process process) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line = "";
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }

    private static void testExecution() throws IOException {
        Process process = Runtime.getRuntime()
                .exec("ls -la");
        printResults(process);
    }

    public static void main(String[] args) throws IOException {
        testExecution();
    }
}
