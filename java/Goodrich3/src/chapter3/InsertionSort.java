package chapter3;

public class InsertionSort {
    public static void insertionSort(char[] data) {
        int n = data.length;
        for (int k = 1; k < n; k++) {
            char cur = data[k];
            int j = k;
            while(j > 0 && data[j - 1] > cur) {
                data[j] = data[j - 1];
                j--;
            }
            data[j] = cur;
        }
    }

    public static void main(String[] args) {
        char[] a = {8, 3, 9, 2, 7, 1, 6, 4, 5};
        insertionSort(a);
        for(char el: a) {
            System.out.print((int)el + " ");
        }
    }
}
