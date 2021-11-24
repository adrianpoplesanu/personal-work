package repl;

import heap.GenericHeap;
import heap.Heap;

import java.util.Scanner;

public class Repl {
    private Scanner scanner;
    private Heap<Integer> heap;

    public Repl() {
        scanner = new Scanner(System.in);
        heap = new GenericHeap<>();
    }

    public void loop() {
        String command;
        while(true) {
            System.out.print(">> ");
            command = scanner.nextLine();
            if (command.equals("exit")) {
                break;
            } else if (command.equals("print")) {
                heap.print();
            } else if (command.equals("min")) {
                int result = heap.min();
                System.out.println(result);
            } else if (command.equals("remove")) {
                int result = heap.remove();
                System.out.println(result);
            } else if (command.startsWith("add")) {
                int val = Integer.valueOf(command.split(" ")[1]);
                heap.insert(val);
            }
        }
    }
}
