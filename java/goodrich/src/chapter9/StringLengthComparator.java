package chapter9;

import java.util.Comparator;

public class StringLengthComparator implements Comparator<String> {
    @Override
    public int compare(String o1, String o2) {
        if (o1.length() < o2.length()) return -1;
        if (o1.length() == o2.length()) return 0;
        return 1;
    }
}
