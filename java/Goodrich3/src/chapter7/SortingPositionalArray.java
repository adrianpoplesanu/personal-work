package chapter7;

public class SortingPositionalArray {
    public static void insertionSort(PositionalList<Integer> list) {
        Position<Integer> marker = list.first();
        while (marker != list.last()) {
            Position<Integer> pivot = list.after(marker);
            int value = pivot.getElement();
            if (value > marker.getElement()) {
                marker = pivot;
            } else {
                Position<Integer> walk = marker;
                while (walk != list.first() && list.before(walk).getElement() > value) {
                    walk = list.before(walk);
                }
                list.remove(pivot);
                list.addBefore(walk, value);
            }
        }
    }

    public static void main(String[] args) {
        LinkedPositionalList<Integer> list = new LinkedPositionalList<>();
        list.addLast(6);
        list.addLast(2);
        list.addLast(5);
        list.addLast(3);
        list.addLast(7);
        list.addLast(1);
        list.addLast(9);
        list.addLast(4);
        list.addLast(8);

        insertionSort(list);

        System.out.print("[ RESULT ] ");
        for (Integer i: list) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}
