package adrian3;

import java.util.Iterator;

public interface Tree<E> extends Iterable<E> {
    Iterator<E> iterator();
}
