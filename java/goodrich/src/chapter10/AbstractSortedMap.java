package chapter10;

import chapter9.DefaultComparator;

import java.util.Comparator;

public abstract class AbstractSortedMap<K, V> extends AbstractMap<K, V> {
    private Comparator<K> comp;

    protected AbstractSortedMap(Comparator<K> c) {
        comp = c;
    }

    protected AbstractSortedMap() {
        this(new DefaultComparator<K>());
    }

    protected int compare(Entry<K,V> a, Entry<K,V> b) {
        return comp.compare(a.getKey(), b.getKey());
    }

    protected int compare(K a, Entry<K,V> b) {
        return comp.compare(a, b.getKey());
    }

    protected int compare(Entry<K,V> a, K b) {
        return comp.compare(a.getKey(), b);
    }

    protected int compare(K a, K b) {
        return comp.compare(a, b);
    }

    protected boolean checkKey(K key) throws IllegalArgumentException {
        try {
            return comp.compare(key, key) == 0;
        } catch (ClassCastException e) {
            throw new IllegalArgumentException("Incompatible key");
        }
    }

    public abstract Entry<K, V> firstEntry();
    public abstract Entry<K, V> lastEntry();
    public abstract Entry<K, V> ceilingEntry(K k);
    public abstract Entry<K, V> floorEntry(K k);
    public abstract Entry<K, V> lowerEntry(K k);
    public abstract Entry<K, V> higherEntry(K k);
    public abstract Iterable<Entry<K, V>> subMap(K k1, K k2);
}
