package chapter2;

public class Portofolio<T> {
	T[] data;
	
	@SuppressWarnings("unchecked")
	Portofolio(int capacity) {
		data = (T[]) new Object[capacity];
	}
	
	public T GetAt(int index) {
		return data[index];
	}
	
	public void SetAt(T element, int index) {
		data[index] = element;
	}
	
	public void GetMatches() {
		Portofolio<Match> p = new Portofolio<Match>(4);
		p.SetAt(new Match("rma - ata"), 2);
		System.out.println(p.GetAt(2).description);
	}
	
	public static class Etapa {
		public String name;
		
		Etapa(String n) {
			name = n;
		}
	}
	
	public class Match {
		public String description;
		
		Match(String d) {
			description = d;
		}
	}
	
	public static void main(String[] args) {
		Portofolio<String> p = new Portofolio<String>(10);
		p.SetAt("teeest", 7);
		System.out.println(p.GetAt(7));
		
		Portofolio<Etapa> e = new Portofolio<Etapa>(5);
		e.SetAt(new Etapa("aaa"), 3);
		System.out.println(e.GetAt(3).name);
		e.GetMatches(); // trebuie incapsulat altfel
	}
}
