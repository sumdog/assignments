// An interface for an ordered structure that allows you to remove min elts
// (c) 1998 McGraw-Hill
package org.mcgraw;

// ideally this would extend linear, but there are problems....
public interface PriorityQueue
{
    public Comparable peek();
    // pre: !isEmpty()
    // post: returns the minimum value in priority queue

    public Comparable remove();
    // pre: !isEmpty()
    // post: returns and removes minimum value from queue

    public void add(Comparable value);
    // pre: value is non-null comparable
    // post: value is added to priority queue

    public boolean isEmpty();
    // post: returns true iff no elements are in queue

    public int size();
    // post: returns number of elements within queue

    public void clear();
    // post: removes all elements from queue
}
