package cpsc542.xml;

import java.io.File;

public abstract class AbstractParser {

	protected File inputxml;
	
	public AbstractParser(File inputxml) {
		this.inputxml = inputxml;
	}
	
	public abstract TotalCreditData[] getTotalCredits();
}
