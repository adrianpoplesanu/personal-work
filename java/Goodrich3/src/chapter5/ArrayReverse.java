package chapter5;

public class ArrayReverse {
    public static void reverArray(int[] data, int low, int high) {
        if (low < high) {
            int tmp = data[low];
            data[low] = data[high];
            data[high] = tmp;
            reverArray(data, low + 1, high - 1);
        }
    }

    public static void main(String[] args) {
        int[] data = {8, 2, 9, 4, 3, 7, 1, 6, 4, 5};
        reverArray(data, 0, 9);
        for (int el: data) {
            System.out.print(el + " ");
        }
        System.out.println();
    }
}
