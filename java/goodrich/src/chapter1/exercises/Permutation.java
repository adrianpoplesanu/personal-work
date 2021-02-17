package chapter1.exercises;

public class Permutation { 
    public static void main(String[] args) { 
        char[] elements = new char[]{'c','a','r','b','o','n'};
        String str = String.valueOf(elements);
        int len = str.length();
        Permutation permutation = new Permutation();
        permutation.combine(str, 0, len - 1);
    }

    private void combine(String str, int left, int right) {
        if (left == right)
            System.out.println(str); 
        else {
            for (int i = left; i <= right; i++) { 
                str = swap(str, left, i);
                combine(str, left + 1, right); 
                str = swap(str, left, i);
            }
        }
    }

    public String swap(String a, int i, int j) { 
        char temp;
        char[] c_Array = a.toCharArray(); 
        temp = c_Array[i];
        c_Array[i] = c_Array[j]; 
        c_Array[j] = temp;
        return String.valueOf(c_Array); 
    }
}