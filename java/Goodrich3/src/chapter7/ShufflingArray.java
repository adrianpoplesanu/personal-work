package chapter7;

import java.util.Arrays;
import java.util.Collections;

public class ShufflingArray {
    public static void main(String[] args) {
        Integer[] arr = {1, 2, 3, 4, 5 ,6 ,7, 8};
        java.util.List<Integer> listArr = Arrays.asList(arr);
        Collections.shuffle(listArr);
        System.out.println(listArr);
    }
}
