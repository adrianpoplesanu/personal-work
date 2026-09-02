package chapter3;

public class DeepCloneMatrix {
    public static int[][] deepClone(int[][] original) {
        int[][] backup = new int[original.length][];
        for (int k = 0; k < original.length; k++) {
            backup[k] = original[k].clone();
        }
        return backup;
    }

    public static void parse(int[][] matrix) {
        for (int[] ints : matrix) {
            for (int anInt : ints) {
                System.out.print(anInt + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] original = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        int[][] copy1;
        int[][] copy2;
        copy1 = original;
        copy2 = deepClone(original);
        System.out.println(original);
        parse(original);
        System.out.println(copy1);
        parse(copy1);
        System.out.println(copy2);
        parse(copy2);
    }
}
