package chapter1.exercises;

public class Backtracking {
    public static void main(String[] args) { 
        char[] elements = new char[] {'c','a','r', 'b'};
        Backtracking backtracking = new Backtracking();
        backtracking.solve(elements);
    }
    
    public void solve(char[] elements) {
    	int[] a = new int[elements.length];
    	back(elements, a, 0);
    }
    
    public void back(char[] elements, int[] a, int k) {
    	if (k == elements.length) {
    		output(elements, a, k);
    	} else {
    		a[k] = 0;
    		while(a[k] < elements.length) {
    			if (accept(a, k)) {
    				back(elements, a, k + 1);
    			}
    			a[k]++;
    		}
    	}
    }
    
    public boolean accept(int[] a, int k) {
    	for (int i = 0; i < k; i++) if (a[i] == a[k]) return false;
    	return true;
    }
    
    public void output(char[] elements, int[] a, int n) {
    	for (int i = 0; i < n; i++) {
    		System.out.print(elements[a[i]]);
    	}
    	System.out.print('\n');
    }
}
