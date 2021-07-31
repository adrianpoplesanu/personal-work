package chapter5.exercises;

import java.util.ArrayList;

public class ArraySubsets2 {
	
	public static <T> void back(ArrayList<T> elements, ArrayList<T> result, int start) {
		System.out.println(result);
		for (int i = start; i < elements.size(); i++) {
			result.add(elements.get(i));
			back(elements, result, i + 1);
			result.remove(result.size() -1);
		}
	}

	public static void main(String[] args) {
		ArrayList<Integer> numbers = new ArrayList<Integer>();
		numbers.add(1);
		numbers.add(2);
		numbers.add(3);
		numbers.add(4);
		ArrayList<Integer> walking_numbers = new ArrayList<Integer>();
		back(numbers, walking_numbers, 0);
		
		ArrayList<String> names = new ArrayList<String>();
		names.add("dexiciul");
		names.add("ram");
		names.add("adrianus");
		ArrayList<String> walking_names = new ArrayList<String>();
		back(names, walking_names, 0);
	}
}
