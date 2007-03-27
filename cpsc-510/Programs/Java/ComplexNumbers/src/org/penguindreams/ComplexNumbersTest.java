/*
 * Sumit Khanna / cpsc-510 / Assignment #6 / Thompson
 * 
 *   Main program to test ComplexNumber data type using
 *   a predefined set of complex numbers. 
 */
package org.penguindreams;
import org.penguindreams.math.ComplexNumber;

public class ComplexNumbersTest {
	
	private static final ComplexNumber[] testset = {
		new ComplexNumber(5,4),
		new ComplexNumber(3,2),
		new ComplexNumber(5.42,3.57),
		new ComplexNumber(6.23,4.78),
		new ComplexNumber(-4.32,-7.65),
		new ComplexNumber(-4,3.23),
		new ComplexNumber(8.2,-5)
	};
	
	public static void main(String[] args) {
		for(int i=0; i<testset.length; i++) {
			for(int j=0; j<testset.length; j++) {
				System.out.print("Adding ");
				System.out.print(testset[i] + " to " + testset[j]);
				System.out.print(" Results in "+ testset[i].add(testset[j])+"\n");
				
				System.out.print("Subtracting ");
				System.out.print(testset[i] + " from " + testset[j]);
				System.out.print(" Results in "+ testset[i].subtract(testset[j])+"\n");
				
				System.out.print("Multiplying ");
				System.out.print(testset[i] + " by " + testset[j]);
				System.out.print(" Results in "+ testset[i].multiply(testset[j])+"\n");
				
				System.out.print("Dividing ");
				System.out.print(testset[i] + " by " + testset[j]);
				System.out.print(" Results in "+ testset[i].divide(testset[j])+"\n");
				
				System.out.print("\n");
			}
			System.out.println("--------------------------------");
		}
	}
	
}
