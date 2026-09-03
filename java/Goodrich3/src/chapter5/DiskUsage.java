package chapter5;

import java.io.File;

public class DiskUsage {
    public static long diskUsage(File root) {
        long total = root.length();
        if (root.isDirectory()) {
            for (String childname: root.list()) {
                File child = new File(root, childname);
                total += diskUsage(child);
            }
        }
        System.out.printf("%10d\t%s%n", total, root);
        return total;
    }

    public static void main(String[] args) {
        File file = new File("/Users/adrianpoplesanu/Documents/git-projects/personal-work/java/Goodrich3/src");
        diskUsage(file);
    }
}
