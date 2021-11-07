import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class UselessTextEditor {
    public static String readFile(String filename) {
        StringBuilder contentBuilder = new StringBuilder();

        try (Stream<String> stream = Files.lines( Paths.get(filename), StandardCharsets.UTF_8)) {
            //stream.forEach(s -> contentBuilder.append(s).append("\n")); // asta e originalul de a copia continutul unui fisier intr-un String
            stream.forEach(s -> contentBuilder.append(s));
        }
		catch (IOException e) {
            e.printStackTrace();
        }

        return contentBuilder.toString();
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
            while(content.charAt(textPos) == ' ' || content.charAt(textPos) == '\n' || content.charAt(textPos) == '\r' || content.charAt(textPos) == '\t') {
                textPos++;
                if (textPos > content.length() - 1) textPos = 0;
            }
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
