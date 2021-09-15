package chapter7;

public class FavoritesListMTF<E> extends FavoritesList<E> {
	protected void moveUp(Position<Item<E>> p) {
		if (p != list.first()) list.addFirst(list.remove(p));
	}
	
	public Iterable<E> getFavorites(int k) throws IllegalArgumentException {
		if (k < 0 || k > size()) throw new IllegalArgumentException("Invalid k");
		
		PositionalList<Item<E>> temp = new LinkedPositionalList<>();
		for (Item<E> item : (LinkedPositionalList<Item<E>>)list) { // if PositionalList<E> would extend Iterable<E> then this would not be needed
			temp.addLast(item);
		}
		
		PositionalList<E> result = new LinkedPositionalList<>();
		for (int j = 0; j < k; j++) {
			Position<Item<E>> highPos = temp.first();
			Position<Item<E>> walk = temp.after(highPos);
			while(walk != null) {
				if (count(highPos) < count(walk)) {
					highPos = walk;
				}
				walk = temp.after(walk);
			}
			result.addLast(value(highPos));
			temp.remove(highPos);
		}
		return (Iterable<E>) result; // if PositionalList<E> would extend Iterable<E> then this would not be needed
	}
}
