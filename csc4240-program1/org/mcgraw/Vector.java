// An implementation of Vectors, similar to that defined in java.utils
// (c) 1998 McGraw-Hill

package org.mcgraw;

public class Vector implements Cloneable
{
    protected Object elementData[];     // the data
    protected int elementCount;         // # of elts in vec
    protected int capacityIncrement;    // the rate of growth for vector
    protected Object initialValue;      // new elements have this value
    protected final static int defaultCapacity = 10; // def't capacity, must be>0

    public Vector()
    // post: constructs an empty vector
    {
        this(10); // call one-parameter constructor
    }

    public Vector(int initialCapacity)
    // pre: initialCapacity >= 0
    // post: constructs an empty vector with initialCapacity capacity
    {
        Assert.pre(initialCapacity >= 0,"Non-negative capacity.");
        elementData = new Object[initialCapacity];
        elementCount = 0;
        capacityIncrement = 0;
        initialValue = null;
    }

    public Vector(int initialCapacity, int capacityIncr)
    // pre: initialCapacity >= 0, capacityIncr >= 0
    // post: constructs an empty vector with initialCapacity capacity
    //    that extends capacity by capacityIncr, or doubles if 0
    {
        Assert.pre(initialCapacity >= 0, "Non-negative capacity.");
        elementData = new Object[initialCapacity];
        elementCount = 0;
        capacityIncrement = capacityIncr;
        initialValue = null;
    }

    public Vector(int initialCapacity, int capacityIncr, Object initValue)
    // pre: initialCapacity, capacityIncr >= 0
    // post: constructs empty vector with capacity that begins at
    //       initialCapacity and extends by capacityIncr or doubles
    //       if 0.  New entries in vector are initialized to initValue.
    {
        Assert.pre(initialCapacity >= 0, "Non-negative capacity.");
        capacityIncrement = capacityIncr;
        elementData = new Object[initialCapacity];
        elementCount = 0;
        initialValue = initValue;
    }

    public void ensureCapacity(int minCapacity)
    // post: the capacity of this vector is at least minCapacity.
    {
        if (elementData.length < minCapacity) {
            int newLength = elementData.length; // initial guess
            if (capacityIncrement == 0) {
                // increment of 0 suggests doubling (default)
                if (newLength == 0) newLength = 1;
                while (newLength < minCapacity) {
                    newLength *= 2;
                }
            } else {
                // increment != 0 suggests incremental increase
                while (newLength < minCapacity)
                {
                    newLength += capacityIncrement;
                }
            }
            // assertion: newLength > elementData.length.
            Object newElementData[] = new Object[newLength];
            int i;
            // copy old data to array
            for (i = 0; i < elementCount; i++) {
                newElementData[i] = elementData[i];
            }
            elementData = newElementData;
            // N.B. Garbage collector will pick up old elementData
        }
        // assertion: capacity is at least minCapacity
    }

    public void addElement(Object obj)
    // post: adds new element to end of possibly extended vector
    {
        ensureCapacity(elementCount+1);
        elementData[elementCount] = obj;
        elementCount++;
    }

    public int capacity()
    // post: returns allocated size of the vector
    {
        return elementData.length;
    }

    public Object clone()
    // post: returns a copy of the vector, using same objects.
    {

        // generate new (empty) vector
        Vector copy =
            new Vector(elementData.length,capacityIncrement,initialValue);

        int i;
        for (i = 0; i < elementCount; i++) {
            copy.addElement(elementData[i]);
        }
        return copy;
    }

    public boolean contains(Object elem)
    // post: returns true iff Vector contains the value
    //       (could be faster, if orderedVector is used)
    {
        int i;
        for (i = 0; i < elementCount; i++) {
            if (elem.equals(elementData[i])) return true;
        }
        return false;
    }

    public void copyInto(Object dest[])
    // pre: dest has at least size() elements
    // post: a copy of the vector is stored in the dest array
    {
        int i;
        for (i = 0; i < elementCount; i++) {
            dest[i] = elementData[i];
        }
    }

    public Object elementAt(int index)
    // pre: 0 <= index && index < size()
    // post: returns the element stored in location index
    {
        return elementData[index];
    }

    public Iterator elements()
    // post: returns an iterator (ordered enumeration) allowing one to
    //       view elements of vector
    {
        return new VectorIterator(this);
    }

    public Object firstElement()
    // pre: vector contains an element
    // post: returns first value in vector
    {
        return elementAt(0);
    }

    public int indexOf(Object elem)
    // post: returns index of element equal to object, or -1.  Starts at 0.
    {
        return indexOf(elem,0);
    }

    public int indexOf(Object elem, int index)
    // post: returns index of element equal to object, or -1.  Starts at index.
    {
        int i;
        for (i = index; i < elementCount; i++)
        {
            if (elem.equals(elementData[i])) return i;
        }
        return -1;
    }

    public void insertElementAt(Object obj, int index)
    // pre: 0 <= index <= size()
    // post: inserts new value in vector with desired index,
    //   moving elements from index to size()-1 to right
    {
        int i;
        ensureCapacity(elementCount+1);
        // N.B. must copy from right to left to avoid destroying data
        for (i = elementCount; i > index; i--) {
            elementData[i] = elementData[i-1];
        }
        // assertion: i == index and element[index] is available
        elementData[index] = obj;
        elementCount++;
    }
    /* A recursive version of insert element at
    public void insertElementAt(Object value, int index)
    // pre: 0 <= index <= size()
    // post: inserts new value in vector with desired index
    //   moving elements from index to size()-1 to right
    {
        if (index >= size()) addElement(value); // base case
        else {
            Object previous = elementAt(index); // work
            insertElementAt(previous,index+1);  // progress
            setElementAt(value,index);  // work
        }
    }
    */

    public boolean isEmpty()
    // post: returns true iff there are no elements in the vector
    {
        return size() == 0;
    }

    public Object lastElement()
    // pre: vector is not empty
    // post: returns last element of the vector
    {
        return elementAt(elementCount-1);
    }

    public int lastIndexOf(Object obj)
    // post: returns index of last occurrence of object in the vector, or -1
    {
        return lastIndexOf(obj,elementCount-1);
    }

    public int lastIndexOf(Object obj, int index)
    // pre: index >= 0
    // post: returns the index of last occurrence of object at or before
    //       index.
    {
        int i;
        for (i = index; i >= 0; i--) {
            if (obj.equals(elementData[i])) return i;
        }
        return -1;
    }

    public void clear()
    // post: vector is empty
    {
        setSize(0);
    }

    public void removeAllElements()
    // post: vector is empty
    {
        setSize(0);
    }

    public boolean removeElement(Object element)
    // post: element equal to parameter is removed
    {
        int where = indexOf(element);
        if (where == -1) return false;
        removeElementAt(where);
        return true;
    }

    public void removeElementAt(int where)
    // pre: 0 <= where && where < size()
    // post: indicated element is removed, size decreases by 1
    {
        elementCount--;
        while (where < elementCount) {
            elementData[where] = elementData[where+1];
            where++;
        }
        elementData[elementCount] = null; // free reference
    }

    public void setElementAt(Object obj, int index)
    // pre: 0 <= index && index < size()
    // post: element value is changed to obj
    {
        elementData[index] = obj;
    }

    public void setSize(int newSize)
    // pre: newSize >= 0
    // post: vector is resized, any new elements are initialized
    {
        int i;
        if (newSize < elementCount) {
            for (i = newSize; i < elementCount; i++) elementData[i] = null;
        } else {
            for (i = elementCount; i < newSize; i++)
                elementData[i] = initialValue;
        }
        elementCount = newSize;
    }

    public int size()
    // post: returns the size of the vector
    {
        return elementCount;
    }

    public void trimToSize()
    // post: minimizes allocated size of vector
    {
        Object newElementData[] = new Object[elementCount];
        copyInto(newElementData);
        elementData = newElementData;
    }

    public String toString()
    // post: returns a string representation of vector
    {
        StringBuffer sb = new StringBuffer();
        int i;

        sb.append("<Vector:");
        for (i = 0; i < size(); i++)
        {
            sb.append(" "+elementAt(i));
        }
        sb.append(">");
        return sb.toString();
    }
    /*
    public void print()
    // post: print the elements of the vector
    {
        printFrom(0);
    }

    protected void printFrom(int index)
    // pre: index <= size()
    // post: print elements indexed between index and size()
    {
        if (index < size()) {
            System.out.println(elementAt(index));
            printFrom(index+1);
        }
    }
    */
}


class VectorIterator implements Iterator
{
    protected Vector theVector;
    protected int current;

    public VectorIterator(Vector v)
    // post: constructs an initialized iterator associated with v.
    {
        theVector = v;
        reset();
    }

    public void reset()
    // post: the iterator is reset to beginning of the traversal
    {
        current = 0;
    }

    public boolean hasMoreElements()
    // post: returns true if there is more structure to be traversed.
    {
        return current < theVector.size();
    }

    public Object value()
    // pre: traversal has more elements
    // post: returns the current value referenced by the iterator
    {
        return theVector.elementAt(current);
    }

    public Object nextElement()
    // pre: traversal has more elements
    // post: increments the iterated traversal
    {
        return theVector.elementAt(current++);
    }
}

