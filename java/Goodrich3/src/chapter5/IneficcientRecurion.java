package chapter5;

class InefficientRecursion {
    public static boolean unique3(int[] data, int low, int high) {
        if (low >= high) return true;
        else if (!unique3(data, low, high - 1)) return false;
        else if (!unique3(data, low + 1, high)) return false;
        else return data[low] != data[high];
    }

    public static void main(String[] args) {
        int[] a = {1, 9, 4, 7, 2, 6, 1, 5, 3, 8};
        System.out.println(unique3(a, 0, a.length - 1));
    }
}
