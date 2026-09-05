package chapter5;

public class BinaryRecursion {
    public static int binarySum(int[] data, int low, int high) {
        if (low > high) {
            return 0;
        } else if (low == high) {
            return data[low];
        } else {
            int mid = (low + high) / 2;
            return binarySum(data, low, mid) + binarySum(data, mid + 1, high);
        }
    }

    public static void main(String[] args) {
        int[] a = {1, 3, 5, 6, 8, 9, 2, 4, 7};
        System.out.println(binarySum(a, 0, a.length - 1));
    }
}
