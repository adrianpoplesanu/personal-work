package chapter6;

public class ParenthesesValidator {
    public static boolean isMatched(String expression) {
        final String opening = "({[";
        final String closing = ")}]";

        Stack<Character> buffer = new LinkedStack<>();
        for (char c: expression.toCharArray()) {
            if (opening.indexOf(c) != -1) {
                buffer.push(c);
            } else if (closing.indexOf(c) != -1) {
                if (buffer.isEmpty()) {
                    return false;
                }
                if (closing.indexOf(c) != opening.indexOf(buffer.pop())) {
                    return false;
                }
            }
        }
        return buffer.isEmpty();
    }

    public static void main(String[] args) {
        System.out.println(isMatched(""));
        System.out.println(isMatched("(){[]}"));
        System.out.println(isMatched(")(){}[]"));
        System.out.println(isMatched("(((([{}]))))"));
        System.out.println(isMatched("ala bala portocala"));
    }
}
