package com.adrianpoplesanu.process_execution;

import java.io.*;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.function.Consumer;
import java.util.stream.Collectors;

public class ProcessExecutor {
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

    public static void test2() throws IOException, InterruptedException {
        //ProcessBuilder processBuilder = new ProcessBuilder("/bin/sh", "-c", "echo hello");
        ProcessBuilder processBuilder = new ProcessBuilder("ls", "-la");

        //processBuilder.inheritIO();
        Process process = processBuilder.start();
        String result = readOutput(process.getInputStream());
        System.out.println(result);

        int exitCode = process.waitFor();
        //assertEquals("No errors should be detected", 0, exitCode);
    }

    private static String readOutput(InputStream inputStream) {
        String result = new BufferedReader(new InputStreamReader(inputStream))
                .lines().collect(Collectors.joining("\n"));
        return result;
    }
}
