package chapter5;

import java.io.File;

public class FileHandler {
	
	public static long diskUsage(File root) {
		long total = root.length();
		if (root.isDirectory()) {
			for(String childPath : root.list()) {
				File child = new File(root, childPath);
				total += diskUsage(child);
			}
		}
		System.out.println(total + "\t" + root);
		return total;
	}

	public static void main(String[] args) {
		File root = new File("/Users/adrianpoplesanu/Documents/git-projects/personal-work");
		System.out.println(Long.toString(diskUsage(root) / (1024 * 1024)) + " MB");
	}
}
