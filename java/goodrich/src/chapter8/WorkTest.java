package chapter8;

import java.util.ArrayList;

public class WorkTest {
    public static void main(String[] args) {
        //System.out.println("bla bla bla");
        LinkedBinaryTree<String> tree = new LinkedBinaryTree<String>();
        tree.addRoot("one");
        tree.addLeft(tree.root(), "two");
        tree.addRight(tree.root(), "three");
        tree.addLeft(tree.left(tree.root()), "four");
        tree.addRight(tree.left(tree.root()), "five");
        /*for (Position<String> p : tree.positions()) {
            System.out.println(p.getElement());
        }*/

        tree.SimplePrint();

        LinkedBinaryTreeUtils.IndentationPrint(tree, tree.root(), 0);
        for (String p : tree) { // tree is iterable, so it has an iterator() method that returns an iterable which instantiates the Iterator interface
            System.out.println(p);
        }

        ArrayList<Integer> path = new ArrayList<>();
        LinkedBinaryTreeUtils.IndentationLabeledPrint(tree, tree.root(), path);
        LinkedBinaryTreeUtils.parenthesize(tree, tree.root());
    }
}
