package chapter10;

import java.util.ArrayList;
import java.util.Comparator;

public class SortedTableMap<K, V> extends AbstractSortedMap<K, V> {
    private ArrayList<MapEntry<K, V>> table = new ArrayList<>();

    public SortedTableMap() {
        super();
    }

    public SortedTableMap(Comparator<K> comp) {
        super(comp);
    }

    private int findIndex(K key, int low, int high) {
        if (high < low) return high + 1;
        int mid = (low + high) / 2;
        int comp = compare(key, table.get(mid));
        if (comp == 0) return mid;
        else if (comp < 0) {
            return findIndex(key, low, mid - 1);
        } else {
            return findIndex(key, mid + 1, high);
        }
    }

    private int findIndex(K key) {
        return findIndex(key, 0, table.size() - 1);
    }

    @Override
    public int size() {
        return table.size();
    }

    @Override
    public V get(K key) {
        int j = findIndex(key);
        if (j == size() || compare(key, table.get(j)) != 0) return null;
        return table.get(j).getValue();
    }

    @Override
    public V put(K key, V value) {
        int j = findIndex(key);
        if (j < size() && compare(key, table.get(j)) == 0) {
            return table.get(j).setValue(value);
        }
        table.add(j, new MapEntry<>(key, value));
        return null;
    }

    @Override
    public V remove(K key) {
        int j = findIndex(key);
        if (j == size() || compare(key, table.get(j)) != 0) return null;
        return table.remove(j).getValue();
    }

    private Entry<K, V> safeEntry(int j) {
        if (j < 0 || j >= table.size()) return null;
        return table.get(j);
    }

    @Override
    public Entry<K, V> firstEntry() {
        return safeEntry(0);
    }

    @Override
    public Entry<K, V> lastEntry() {
        return safeEntry(table.size() - 1);
    }

    @Override
    public Entry<K, V> ceilingEntry(K k) {
        return safeEntry(findIndex(k));
    }

    @Override
    public Entry<K, V> floorEntry(K k) {
        int j = findIndex(k);
        if (j == size() || !k.equals(table.get(j).getKey())) j--;
        return safeEntry(j);
    }

    @Override
    public Entry<K, V> lowerEntry(K k) {
        return safeEntry(findIndex(k) - 1);
    }

    @Override
    public Entry<K, V> higherEntry(K k) {
        int j = findIndex(k);
        if (j < size() && k.equals(table.get(j).getKey())) j++;
        return safeEntry(j);
    }

    private Iterable<Entry<K, V>> snapshot(int startIndex, K stop) {
        ArrayList<Entry<K, V>> buffer = new ArrayList<>();
        int j = startIndex;
        while (j < table.size() && (stop != null || compare(stop, table.get(j)) > 0)) {
            buffer.add(table.get(j++));
        }
        return buffer;
    }

    public Iterable<Entry<K, V>> entrySet() {
        return snapshot(0, null);
    }

    @Override
    public Iterable<Entry<K, V>> subMap(K k1, K k2) {
        return snapshot(findIndex(k1), k2);
    }
}
