// An implementation of priority queues that makes use of ordering vectors.
// (c) 1998 McGraw-Hill
package org.mcgraw;

public class PriorityVector implements PriorityQueue
{
    protected Vector data;

    public PriorityVector()
    // post: constructs a new priority queue
    {
        data = new Vector();
    }

    public Comparable peek()
    // pre: !isEmpty()
    // post: returns the minimum value in the priority queue
    {
        return (Comparable)data.elementAt(0);
    }

    public Comparable remove()
    // pre: !isEmpty()
    // post: removes and returns minimum value in priority queue
    {
        Comparable result = (Comparable)data.elementAt(0);
        data.removeElementAt(0);
        return result;
    }
    public void add(Comparable value)
    // pre: value is non-null
    // post: inserts value in priority queue
    //       leaves elements in order
    {
        int position = indexOf(value);
        data.insertElementAt(value,position);
    }

    protected int indexOf(Comparable target)
    // pre: value is a non-null comparable object
    // post: returns ideal position of value in vector
    {
        Comparable midValue;
        int low = 0;  // lowest possible location
        int high = data.size(); // highest possible location
        int mid = (low + high)/2; // low <= mid <= high
        // mid == high iff low == high
        while (low < high) {
            Assert.condition(mid < high,"Middle element exists.");
            midValue = (Comparable)data.elementAt(mid);
            if (midValue.compareTo(target) < 0) {
                low = mid+1;
            } else {
                high = mid;
            }
            mid = (low+high)/2;
        }
        return low;
    }

    public boolean isEmpty()
    // post: returns true iff the priority queue is empty
    {
        return data.size() == 0;
    }

    public int size()
    // post: returns number of elements in priority queue
    {
        return data.size();
    }

    public void clear()
    // post: removes all elements from priority queue.
    {
        data.clear();
    }

    public String toString()
    // post: returns string representation of priority vector
    {
        return "<PriorityVector: "+data+">";
    }
}
