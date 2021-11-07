public class UselessTextEditor {
    public static String readFile(String filename) {
        return "adrianus per scorillo";
    }

    public static void drawMatrix(String content, int size) throws InterruptedException {
        int textPos = 0;
        int screenPos = 0;
        int a[] = new int[size];
        int count[] = new int[size];
        int max_modification = 3;
        for (int i = 0; i < a.length; i++) a[i] = 0;
        for (int i = 0; i < a.length; i++) count[i] = 0;
        while(true) {
            /*while(content.charAt(textPos) == ' ') {
                textPos++;
                if (textPos > content.length() - 1) textPos = 0;
            }*/
            Thread.sleep(100);
            String output = "\u001b[32m";
            for (int j = 0; j < a.length; j++) {
                count[j]++;
                if (a[j] == 1) {
                    output += content.charAt(textPos) + " ";
                    textPos++;
                    if (textPos > content.length() - 1) textPos = 0;
                } else {
                    output += "  ";
                }
            }
            output += "\u001b[0m";
            System.out.println(output);
            screenPos++;
            if (screenPos >= size) {
                screenPos = 0;
            }
            for (int j = 0; j < max_modification; j++) {
                int col = (int)(Math.random() * (size - 1));
                if (count[col] > 10) {
                    count[col] = 0;
                    if (a[col] == 0) a[col] = 1;
                    else a[col] = 0;
                }
            }
        }
    }

    public static void main(String[] args) {
        //System.out.println("\u001b[32mTest culoare matrix...\u001b[0m");
        String filename = args[0];
        int size = Integer.valueOf(args[1]);

        String content = readFile(filename);
        try {
            drawMatrix(content, size);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
