package chapter8;

public class WorkTest {
    public static void main(String[] args) {
        //System.out.println("bla bla bla");
        LinkedBinaryTree<String> tree = new LinkedBinaryTree<String>();
        tree.addRoot("1");
        tree.addLeft(tree.root(), "2");
        tree.addRight(tree.root(), "3");
        tree.addLeft(tree.left(tree.root()), "4");
        tree.addRight(tree.left(tree.root()), "5");
        /*for (Position<String> p : tree.positions()) {
            System.out.println(p.getElement());
        }*/

        tree.SimplePrint();

        LinkedBinaryTreeUtils.IndentationPrint(tree, tree.root(), 0);
    }
}
