package chapter7;

import java.util.Iterator;

public class ArrayListTest {
    public static void main(String[] args) {
    	ArrayList<String> words = new ArrayList<String>();
    	words.add(0, "buna");
    	words.add(1, "dimineata");
    	words.add(2, "bebe");
    	words.add(3, "dex");
    	
    	/*list.add(0, "buna");
    	list.add(0, "dimineata");
    	list.add(0, "bebe");
    	list.add(0, "dex");*/
    	
    	for (int i = 0; i < words.getSize(); i++) {
    		System.out.println(words.get(i));
    	}
    	
    	words.remove(2);
    	
    	for (int i = 0; i < words.getSize(); i++) {
    		System.out.println(words.get(i));
    	}
    	
    	System.out.println("=== Iterator test ============ ");
    	
    	Iterator<String> iter = words.iterator();
    	while(iter.hasNext()) {
    		String word = iter.next();
    		System.out.println(word);
    	}
    	
    	System.out.println("=== Iterator test #2 ========= ");
    	
    	for (String word : words) {
    		System.out.println(word);
    	}
    }
}
