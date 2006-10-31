package cpsc542.xml;

public class TotalCreditData implements Comparable {

	private String course;
	
	private int total;
	
	public TotalCreditData(String course, int total) {
		this.total = total;
		this.course = course;
	}
	
	public String getCourse() {
		return course;
	}
	
	public int getTotal() {
		return total;
	}
	
	public int compareTo(Object d) {
		if( d instanceof TotalCreditData) {
			return this.course.compareTo(((TotalCreditData)d).getCourse());
		}
		else {
			return -1;
		}
			
	}
	
	public String toString() {
		return "Course: " + course + " Total: " + total;
	}

	
}
