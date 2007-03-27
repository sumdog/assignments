/*
 * Sumit Khanna / cpsc-510 / Assignment #6 / Thompson
 * 
 * Abstract Data Type of ComplexNumber used to 
 *  perform arithmetic operations on imaginary numbers
 *   
 */
package org.penguindreams.math;

public class ComplexNumber {
	
	//member variables
	
	private double real, imaginary;
	
	//Constructors
	
	public ComplexNumber(double real, double imaginary) {
		this.real = real;
		this.imaginary = imaginary;
	}
	
	public ComplexNumber(String s) {
		String[] parts = s.split("+");
		real = Double.parseDouble(parts[0]);
		imaginary = Double.parseDouble(parts[1]);
	}
	
	//Get and Set Methods
	
	public double getReal() {
		return real;
	}
	
	public double getImaginary() {
		return imaginary;
	}
	
	public void setReal(double r) {
		real = r;
	}
	
	public void setImaginary(double i) {
		imaginary = i;
	}
	
	//Math functions
	public ComplexNumber add(ComplexNumber c) {
		return new ComplexNumber(this.real+c.getReal(),this.imaginary+c.getImaginary());
	}
	
	public ComplexNumber subtract(ComplexNumber c) {
		return new ComplexNumber(this.real-c.getReal(),this.imaginary-c.getImaginary());
	}
	
	public ComplexNumber multiply(ComplexNumber c) {
		return new ComplexNumber( (this.real * c.getReal()) - (this.imaginary * c.imaginary),
								  (this.real * c.getImaginary()) + (this.imaginary * c.real) );
	}
	
	public ComplexNumber divide(ComplexNumber c) {
		return new ComplexNumber(
				((this.real*c.getReal()) + (this.imaginary * c.getImaginary())) / ( Math.pow(c.real, 2) + Math.pow(c.imaginary, 2) ),
				((this.imaginary*c.getReal()) - (this.real * c.getImaginary())) / ( Math.pow(c.real, 2) + Math.pow(c.imaginary, 2) ));
	}
	
	//Display
	public String toString() {
		return Double.toString(real) + " + " + Double.toString(imaginary) +"i";
	}
}




