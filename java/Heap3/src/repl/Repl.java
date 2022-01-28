package repl;

import heap.HeapInterface;

import java.util.Scanner;

public class Repl {
    private HeapInterface heap;
    private Scanner scanner;

    public Repl(HeapInterface heap) {
        this.heap = heap;
        scanner = new Scanner(System.in);
    }

    public void loop() {
        String command;
        while(true) {
            System.out.print(">> ");
            command = scanner.nextLine();
            if (command.equals("exit")) {
                break;
            }
            if (command.equals("print")) {
                heap.print();
            }
            if (command.equals("min")) {
                System.out.println(heap.min());
            }
            if (command.equals("remove")) {
                System.out.println(heap.remove());
            }
            if (command.startsWith("add")) {
                int val = Integer.valueOf(command.split(" ")[1]);
                heap.insert(val);
            }
        }
    }
}
