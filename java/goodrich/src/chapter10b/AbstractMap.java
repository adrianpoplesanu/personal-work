package chapter10b;

public class AbstractMap<K, V> implements Map<K, V> {

    protected static class MapEntry<K, V> implements Entry<K, V> {
        private K key;
        private V value;

        @Override
        public K getKey() {
            return null;
        }

        @Override
        public V getValue() {
            return null;
        }
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public V get(K key) {
        return null;
    }

    @Override
    public V put(K key, V value) {
        return null;
    }

    @Override
    public V remove(K key) {
        return null;
    }

    @Override
    public Iterable<K> keySet() {
        return null;
    }

    @Override
    public Iterable<V> values() {
        return null;
    }

    @Override
    public Iterable<Entry<K, V>> entrySet() {
        return null;
    }
}
