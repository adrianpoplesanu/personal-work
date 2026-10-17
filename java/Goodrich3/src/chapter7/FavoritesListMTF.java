package chapter7;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class FavoritesListMTF<E> extends FavoritesList<E> {
    protected void moveUp(Position<Item<E>> p) {
        if (p != list.first()) {
            list.addFirst(list.remove(p));
        }
    }

    public Iterable<E> getFavorites(int k) throws IllegalArgumentException {
        if (k < 0 || k > size()) {
            throw new IllegalArgumentException("Invalid k");
        }
        PositionalList<Item<E>> temp = new LinkedPositionalList<>();
        for (Item<E> item: list) {
            temp.addLast(item);
        }

        PositionalList<E> result = new LinkedPositionalList<>();
        for (int j = 0; j < k; j++) {
            Position<Item<E>> highPos = temp.first();
            Position<Item<E>> walk = temp.after(highPos);
            while (walk != null) {
                if (count(walk) > count(highPos)) {
                    highPos = walk;
                }
                walk = temp.after(walk);
            }
            result.addLast(value(highPos));
            temp.remove(highPos);
        }
        return result;
    }

    public static void main(String[] args) {
        FavoritesListMTF<String> favorites = new FavoritesListMTF<>();
        InputStream input = FavoritesListMTF.class.getResourceAsStream("/alice_in_wonderland.txt");
        if (input == null) {
            throw new IllegalStateException("Missing resource: alice_in_wonderland.txt");
        }
        try (Scanner scanner = new Scanner(new InputStreamReader(input, StandardCharsets.UTF_8))) {
            scanner.useDelimiter("[^\\p{L}]+");
            while (scanner.hasNext()) {
                favorites.access(scanner.next().toLowerCase());
            }
        }
        for (String word : favorites.getFavorites(100)) {
            System.out.println(word);
        }
    }
}
