import virtualmachine.VirtualMachine;

public class StackMachine {
    public static void main(String[] args) {
        String[] commands = {
                "PUSH", "3",
                "PUSH", "4",
                "ADD",
                "PUSH", "5",
                "MINUS"
        };

        VirtualMachine vm = new VirtualMachine(commands);
        vm.execute();
    }
}
