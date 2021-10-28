package chapter8;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class LinkedBinaryTree<E> extends AbstractBinaryTree<E> {
	
	protected static class Node<E> implements Position<E> {
		private E element;
		private Node<E> parent;
		private Node<E> left;
		private Node<E> right;
		
		public Node(E e, Node<E> above, Node<E> leftChild, Node<E> rightChild) {
			element = e;
			parent = above;
			left = leftChild;
			right = rightChild;
		}

		@Override
		public E getElement() throws IllegalStateException {
			return element;
		}
		
		public Node<E> getParent() {
			return parent;
		}
		
		public Node<E> getLeft() {
			return left;
		}
		
		public Node<E> getRight() {
			return right;
		}
		
		public void setElement(E e) {
			element = e;
		}
		
		public void setParent(Node<E> parentNode) {
			parent = parentNode;
		}
		
		public void setLeft(Node<E> leftNode) {
			left = leftNode;
		}
		
		public void setRight(Node<E> rightNode) {
			right = rightNode;
		}
	}
	
	protected Node<E> createNode(E e, Node<E> parent, Node<E> left, Node<E> right) {
		return new Node<E>(e, parent, left, right);
	}
	
	protected Node<E> root = null;
	private int size = 0;

	public LinkedBinaryTree() {
		
	}
	
	protected Node<E> validate(Position<E> position) throws IllegalArgumentException {
		if (!(position instanceof Node)) throw new IllegalArgumentException("Invalid type of position.");
		Node<E> node = (Node<E>) position;
		// this is based on an arbitrary convention, if the node has itself as parent then it was previously deleted from the tree
		if (node == node.getParent()) throw new IllegalArgumentException("Position no longer in tree");
		return node;
	}
	
	@Override
	public Position<E> left(Position<E> p) throws IllegalArgumentException {
		Node<E> node = validate(p);
		return node.getLeft();
	}

	@Override
	public Position<E> right(Position<E> p) throws IllegalArgumentException {
		Node<E> node = validate(p);
		return node.getRight();
	}

	@Override
	public Position<E> root() {
		return root;
	}

	@Override
	public Position<E> parent(Position<E> p) throws IllegalArgumentException {
		Node<E> node = validate(p);
		return node.getParent();
	}

	@Override
	public int size() {
		return size;
	}
	
	public Position<E> addRoot(E e) throws IllegalStateException {
		if (!isEmpty()) throw new IllegalStateException("Tree is not null");
		root = createNode(e, null, null, null);
		size = 1;
		return root;
	}
	
	public Position<E> addLeft(Position<E> p, E e) throws IllegalStateException {
		Node<E> parent = validate(p);
		if (parent.getLeft() != null) throw new IllegalStateException("parent already has a left tree");
		Node<E> left = createNode(e, parent, null, null);
		parent.setLeft(left);
		size++;
		return left;
	}
	
	public Position<E> addRight(Position<E> p, E e) throws IllegalStateException {
		Node<E> parent = validate(p);
		if (parent.getRight() != null) throw new IllegalStateException("parent already has a right tree");
		Node<E> right = createNode(e, parent, null, null);
		parent.setRight(right);
		size++;
		return right;
	}
	
	public E set(Position<E> p, E e) throws IllegalArgumentException {
		Node<E> node = validate(p);
		E old = node.getElement();
		node.setElement(e);
		return old;
	}
	
	public void attach(Position<E> p, LinkedBinaryTree<E> t1, LinkedBinaryTree<E> t2) throws IllegalArgumentException {
		Node<E> node = validate(p);
		if (isInternal(node)) throw new IllegalArgumentException("p must be a leaf");
		size += t1.size() + t2.size();
		if (!t1.isEmpty()) {
			t1.root.setParent(node);
			node.setLeft(t1.root);
			t1.root = null;
			t1.size = 0;
		}
		if (!t2.isEmpty()) {
			t2.root.setParent(node);
			node.setRight(t2.root);
			t2.root = null;
			t2.size = 0;
		}
	}
	
	public E remove(Position<E> p) throws IllegalArgumentException {
		Node<E> node = validate(p);
		if (numChildren(p) == 2) throw new IllegalArgumentException("p has both children, cannot delete");
		Node<E> child = node.getLeft() != null ? node.getLeft() : node.getRight();
		if (child != null) {
			child.setParent(node.getParent());
		}
		if (node == root) {
			root = child;
		} else {
			Node<E> parent = node.getParent();
			if (node == parent.getLeft()) {
				parent.setLeft(child);
			} else {
				parent.setRight(child);
			}
		}
		size--;
		E temp = node.getElement();
		node.setElement(null);
		node.setLeft(null);
		node.setRight(null);
		node.setParent(node); // arbitrary condition that marks a node as deleted, i don't like it
		return temp;
	}
	
	private class ElementIterator implements Iterator<E> {
		Iterator<Position<E>> posIterator = positions().iterator();

		@Override
		public boolean hasNext() {
			return posIterator.hasNext();
		}

		@Override
		public E next() {
			return posIterator.next().getElement();
		}
		
		public void remove() {
			posIterator.remove();
		}
		
	}

	@Override
	public Iterator<E> iterator() {
		return new ElementIterator();
	}

	@Override
	public Iterable<Position<E>> positions() {
		//return postorder();
		//return preorder();
		return preorder_lazy_iterator();
	}
}
