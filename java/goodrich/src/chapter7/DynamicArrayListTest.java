package chapter7;

public class DynamicArrayListTest {

	public static void main(String[] args) {
		DynamicArrayList<String> dal = new DynamicArrayList<String>();
		System.out.println(dal.getSize());
		System.out.println(dal.getCapacity());
		
		dal.add(0, "dex");
		dal.add(0, "bebe");
		dal.add(0, "dimineata");
		dal.add(0, "buna");
		dal.add(0, "aaa");
		
		for (int i = 0; i < dal.getSize(); i++) {
			System.out.println(dal.get(i));
		}
		
		System.out.println(dal.getSize());
		System.out.println(dal.getCapacity());
	}
}
