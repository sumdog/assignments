// Abstract iteration class.  Like enumerable, but values are ordered.
// (c) 1998 McGraw-Hill

package org.mcgraw;
import java.util.Enumeration;

public interface Iterator extends Enumeration
{
    public boolean hasMoreElements();
    // post: returns true if there is more structure to be viewed:
    //       ie, if value (nextElement) can return a useful value.

    public Object nextElement();
    // pre: traversal has more elements
    // post: returns current value and increments the iterator

    public void reset();
    // post: the iterator is reset to the beginning of the traversal

    public Object value();
    // pre: traversal has more elements
    // post: returns the current value referenced by the iterator
}

