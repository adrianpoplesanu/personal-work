package chapter2;

public class GenericDemo {
    public static <T> void reverse(T[] data) {
        int low = 0, high = data.length - 1;
        while(low < high) {
            T tmp = data[low];
            data[low++] = data[high];
            data[high--] = tmp;
        }
    }

    public static void main(String[] args) {
        Integer[] numbers = {11, 22, 33, 44, 55};
        GenericDemo.reverse(numbers);
        for (int number: numbers) {
            System.out.print(number + " ");
        }
    }
}
