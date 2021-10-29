package chapter8;

import java.util.ArrayList;

public class LinkedBinaryTreeUtils {
    public static String spaces(int d) {
        String out = "";
        while(d-- > 0) out += " ";
        return out;
    }

    public static <E> void IndentationPrint(Tree<E> tree, Position<E> p, int d) {
        System.out.println(spaces(2*d) + p.getElement());
        for (Position<E> c : tree.children(p)) {
            IndentationPrint(tree, c, d + 1);
        }
    }

    public static <E> void IndentationLabeledPrint(Tree<E> tree, Position<E> p, ArrayList<Integer> path) {
        int d = path.size();
        System.out.println(spaces(2 * d));
        for (int j = 0; j < d; j++) System.out.print(path.get(j) + (j == d - 1 ? " " : "."));
        System.out.println(p.getElement());
        path.add(1);
        for (Position<E> c : tree.children(p)) {
            IndentationLabeledPrint(tree, c, path);
            path.set(d, 1 + path.get(d));
        }
        path.remove(d);
    }

    public static int diskUsage(Tree<Integer> tree, Position<Integer> p) {
        int subtotal = p.getElement();
        for (Position<Integer> c : tree.children(p)) {
            subtotal += diskUsage(tree, c);
        }
        return subtotal;
    }
}
