package chapter10;

import java.util.Scanner;

public class WordCount {
    public static void main(String[] args) {
        Map<String, Integer> freq = new ChainHashMap<>();
        Scanner doc = new Scanner(System.in).useDelimiter("[^a-zA-Z]+");
        while(doc.hasNext()) {
            String word = doc.next().toLowerCase();
            Integer count = freq.get(word);
            if (count == null) {
                count = 0;
            }
            freq.put(word, count + 1);
        }

        int maxCount = 0;
        String maxWord = "no word";
        for (Entry<String, Integer> entry : freq.entrySet()) {
            if (entry.getValue() > maxCount) {
                maxCount = entry.getValue();
                maxWord = entry.getKey();
            }
        }
        System.out.print("The mos frequent word is: " + maxWord);
        System.out.println(" which occurs " + maxCount + " times.");
    }
}
