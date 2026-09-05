package chapter5;

public class BinarySearchIteratively {
    public static boolean binarySearchIterative(int[] data, int target) {
        int low = 0;
        int high = data.length - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (data[mid] == target) return true;
            else if (data[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        int[] a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        System.out.println(binarySearchIterative(a, 5));
        System.out.println(binarySearchIterative(a, 1));
        System.out.println(binarySearchIterative(a, 9));
        System.out.println(binarySearchIterative(a, 15));
    }
}
