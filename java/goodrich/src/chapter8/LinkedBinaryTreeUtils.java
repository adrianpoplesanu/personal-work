package chapter8;

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
}
