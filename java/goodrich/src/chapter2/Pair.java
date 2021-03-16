package chapter2;

public class Pair<TKey, TValue> {
	private TKey key;
	private TValue value;
	
	public Pair(TKey key, TValue value) {
		this.key = key;
		this.value = value;
	}
	
	public TKey GetKey() {
		return this.key;
	}
	
	public TValue GetValue() {
		return this.value;
	}
}
