/*
 * Created on Feb 17, 2005
 */
package noah.can;

/**
 * @author Noah
 */
public class Node {

    private double[] temperature;
    
    /**
     * 
     */
    public Node() {
       temperature = new double[3];         
    }
    
    public double getTemp(int t) {
        return temperature[t];
    }
    
    public void setTemp(int t, double temp) {
        temperature[t] = temp;
    }

}
