package chapter8;

import chapter6.LinkedListQueue;
import chapter6.Queue;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public abstract class AbstractTree<E> implements Tree<E> {
	public boolean isInternal(Position<E> p) {
		return numChildren(p) > 0;
	}
	
	public boolean isExternal(Position<E> p) {
		return numChildren(p) == 0;
	}
	
	public boolean isRoot(Position<E> p) {
		return p == root();
	}
	
	public boolean isEmpty() {
		return size() == 0;
	}
	
	public int depth(Position<E> p) {
		if (isRoot(p)) {
			return 0;
		} else {
			return 1 + depth(parent(p));
		}
	}
	
	private int heightBad() {
		int h = 0;
		for (Position<E> p : positions()) {
			if (isExternal(p)) {
				h = Math.max(h, depth(p));
			}
		}
		return h;
	}
	
	public int height(Position<E> p) {
		int h = 0;
		for (Position<E> c : children(p)) {
			h = Math.max(h, 1 + height(c));
		}
		return h;
	}

	private void preorderSubtree(Position<E> p, List<Position<E>> snapshot) {
		snapshot.add(p);
		for (Position<E> c : children(p)) {
			preorderSubtree(c, snapshot);
		}
	}

	public Iterable<Position<E>> preorder() {
		List<Position<E>> snapshot = new ArrayList<>();
		if (!isEmpty()) preorderSubtree(root(), snapshot);
		return snapshot;
	}

	private class PreorderLazyIterator implements Iterator<Position<E>> {
		Queue<Position<E>> nodes = new LinkedListQueue<>();

		public PreorderLazyIterator() {
			nodes.enqueue(root());
		}

		@Override
		public boolean hasNext() {
			return !nodes.isEmpty();
		}

		@Override
		public Position<E> next() {
			Position<E> p = nodes.dequeue();
			LinkedBinaryTree.Node<E> node = (LinkedBinaryTree.Node<E>) p;
			if (node.getLeft() != null) nodes.enqueue(node.getLeft());
			if (node.getRight() != null) nodes.enqueue(node.getRight());
			return p;
		}
	}

	private class PreorderLazyIterable implements Iterable<Position<E>> {
		@Override
		public Iterator<Position<E>> iterator() {
			return new PreorderLazyIterator();
		}
	}

	public Iterable<Position<E>> preorder_lazy_iterator() {
		return new PreorderLazyIterable();
	}

	private void postorderSubtree(Position<E> p, List<Position<E>> snapshot) {
		for (Position<E> c : children(p)) {
			postorderSubtree(c, snapshot);
		}
		snapshot.add(p);
	}

	public Iterable<Position<E>> postorder() {
		List<Position<E>> snapshot = new ArrayList<>();
		if (!isEmpty()) postorderSubtree(root(), snapshot);
		return snapshot;
	}

	public Iterable<Position<E>> breadthfirst() {
		List<Position<E>> snapshot = new ArrayList<>();
		if (!isEmpty()) {
			Queue<Position<E>> fringe = new LinkedListQueue<>();
			fringe.enqueue(root());
			while (!fringe.isEmpty()) {
				Position<E> p = fringe.dequeue();
				snapshot.add(p);
				for (Position<E> c : children(p)) {
					fringe.enqueue(c);
				}
			}
		}
		return snapshot;
	}
}
