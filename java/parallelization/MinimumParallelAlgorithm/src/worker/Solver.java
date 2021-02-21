package worker;

public class Solver {
	int findMinimum(int a[]) {
		int min = Integer.MAX_VALUE;
		for (int i = 0; i < a.length; i++)
			if (min > a[i]) min = a[i];
		return min;
	}
}
