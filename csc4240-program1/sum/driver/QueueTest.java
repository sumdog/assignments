/*
 * Created on Sep 11, 2003
 *  Don't worry about this file. It's just used to test the Priority Queue
 */
package sum.driver;
import org.mcgraw.*;


public class QueueTest {

	public static void main(String[] args) {
		
		PriorityQueue pq = new PriorityVector();
		pq.add(new MyLittleObject(12));
		pq.add(new MyLittleObject(2));
		pq.add(new MyLittleObject(7));
		pq.add(new MyLittleObject(18));
		
		MyLittleObject o = (MyLittleObject) pq.remove();
		System.out.println(o);
	}
}


class MyLittleObject implements Comparable {

	public int yo;

	public MyLittleObject(int a) {
		yo = a;
	}

	public int compareTo(Object o) {
		return yo - ((MyLittleObject) o).yo;
	}
	
	public String toString() { return new Integer(yo).toString(); }
}
