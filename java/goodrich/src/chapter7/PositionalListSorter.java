package chapter7;

public class PositionalListSorter {
	
	public static void insertionSort(PositionalList<Integer> list) {
		Position<Integer> marker = list.first();
		while(marker != list.last()) {
			Position<Integer> pivot = list.after(marker);
			int value = pivot.getElement();
			if (value > marker.getElement()) {
				marker = pivot;
			} else {
				Position<Integer> walk = marker;
				while(walk != list.first() && list.before(walk).getElement() > value) {
					walk = list.before(walk);
				}
				list.remove(pivot);
				list.addBefore(walk, value);
			}
		}
	}

	public static void main(String[] args) {
		LinkedPositionalList<Integer> numbers = new LinkedPositionalList<Integer>();
		numbers.addFirst(55);
		numbers.addAfter(numbers.first(), 46);
		numbers.addLast(5);
		numbers.addAfter(numbers.last(), 3);
		numbers.addFirst(34);
		numbers.addLast(2);
		insertionSort(numbers);
		
		for(Integer number : numbers) {
			System.out.print(number);
			System.out.print(" ");
		}
		System.out.println("");
	}
}
