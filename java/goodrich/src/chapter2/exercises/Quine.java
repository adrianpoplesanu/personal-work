package chapter2.exercises;

public class Quine {
    static char quote = 34;
    static String[] output = {
"package chapter2.exercises;",
"",
"public class Quine {",
"    static char quote = 34;",
"    static String[] output = {",
"    };",
"",
"    public static void print() {",
"        for (int i = 0; i < 5; i++) {",
"            System.out.println(output[i]);",
"        }",
"        for (int i = 0; i < output.length; i++) System.out.println(quote + output[i] + quote + ',');",
"        for (int i = 5; i < output.length; i++) {",
"	        System.out.println(output[i]);",
"        }",
"    }",
"",
"    public static void main(String[] args) {",
"        print();",
"    }",
"}",
    };

    public static void print() {
        for (int i = 0; i < 5; i++) {
            System.out.println(output[i]);
        }
        for (int i = 0; i < output.length; i++) System.out.println(quote + output[i] + quote + ',');
        for (int i = 5; i < output.length; i++) {
	        System.out.println(output[i]);
        }
    }

    public static void main(String[] args) {
        print();
    }
}
