package com.adrianpoplesanu.process_execution;

import java.io.*;
import java.util.concurrent.Executors;
import java.util.function.Consumer;

public class ProcessExecutor4 {
    private static class StreamGobbler implements Runnable {
        private InputStream inputStream;
        private Consumer<String> consumer;

        public StreamGobbler(InputStream inputStream, Consumer<String> consumer) {
            this.inputStream = inputStream;
            this.consumer = consumer;
        }

        @Override
        public void run() {
            new BufferedReader(new InputStreamReader(inputStream)).lines()
                    .forEach(consumer);
        }
    }

    public static void testProcessExecution() throws IOException, InterruptedException {
        ProcessBuilder builder = new ProcessBuilder();
        builder.command("pwd"); // linux specific
        builder.directory(new File(System.getProperty("user.home")));
        Process process = builder.start();
        StreamGobbler streamGobbler =
                new StreamGobbler(process.getInputStream(), System.out::println);
        //Executors.newSingleThreadExecutor().submit(streamGobbler); // pisatul asta nu merge, ramane agatat procesul principal

        int exitCode = process.waitFor();
        assert exitCode == 0;
    }

    public static void main(String[] args) throws Exception {
        System.out.println("running ProcessExecutor4...");
        testProcessExecution();
    }
}
