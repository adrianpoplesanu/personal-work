import runners.SimpleEmptyRunner;

import java.util.Scanner;

public class MainApplication {
    public static void main(String[] args) {
        System.out.println("running Threading v.1");
        boolean running = true;
        Scanner scanner = new Scanner(System.in);
        while(running) {
            System.out.print(">> ");
            String line = scanner.nextLine();
            if ("exit".equals(line)) running = false;
            if ("run empty".equals(line)) {
                SimpleEmptyRunner runnable = new SimpleEmptyRunner();
                Thread thread = new Thread(runnable);
                thread.start();
            }
        }
    }
}
