package chapter7;

public class ArrayListTest {
    public static void main(String[] args) {
    	ArrayList<String> list = new ArrayList<String>();
    	list.add(0, "buna");
    	list.add(1, "dimineata");
    	list.add(2, "bebe");
    	list.add(3, "dex");
    	
    	/*list.add(0, "buna");
    	list.add(0, "dimineata");
    	list.add(0, "bebe");
    	list.add(0, "dex");*/
    	
    	for (int i = 0; i < list.getSize(); i++) {
    		System.out.println(list.get(i));
    	}
    	
    	list.remove(2);
    	
    	for (int i = 0; i < list.getSize(); i++) {
    		System.out.println(list.get(i));
    	}
    }
}
