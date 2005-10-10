package sum.main;

import sum.datasets.DataSet;
import sum.algorithms.MaxInvest;

public class MaxInvestHomework {
	
	public static void main(String[] args) {
		MaxInvest algor = new MaxInvest(DataSet.generateHomeworkData());
		algor.printData();
	}
	
}
