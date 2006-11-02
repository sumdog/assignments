package cpsc542.xml;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;


public class SAXEngine extends AbstractParser  {
	
	private XMLReader xr;
	
	private DefaultHandler handle;
	
	public SAXEngine(File inputxml) {
		super(inputxml);
		try {
			xr = XMLReaderFactory.createXMLReader();
			handle = new SAXHandler();
			xr.setContentHandler(handle);
			try {
				xr.parse(new InputSource(new FileReader(inputxml)));
			} catch (FileNotFoundException e) {
				System.err.println("File Not Found: " +e.getMessage());
				System.exit(2);
			} catch (IOException e) {
				System.err.println("IO Exception: " +e.getMessage());
				System.exit(2);
			}
		
		} catch (SAXException e) {
			System.err.println("Fatal SAX Error: " +e.getMessage());
			System.exit(2);
		}
		
	}

	public TotalCreditData[] getTotalCredits() {
		return ((SAXHandler) handle).getTotalCredits();
	}


}

class SAXHandler extends DefaultHandler {
	
	private String currentclass;
	int current;
	int hours;
	int state;
	
	final int COURSE = 1;
	final int CURRENT = 2;
	final int HOURS = 3;
	final int CLEAR = -1;
	
	ArrayList totals;
	
	public SAXHandler() {
		currentclass = null;
		current = 0;
		hours = 0;
		state = CLEAR;
		totals = new ArrayList();
	}
	
	public TotalCreditData[] getTotalCredits() {
		TotalCreditData[] ret = new TotalCreditData[totals.size()];
		for(int i = 0; i<ret.length; i++) {
			ret[i] = (TotalCreditData) totals.get(i);
		}
		return ret;
	}
	
	public void startElement(String uri, String name, String qName, Attributes attrs) {
		if(name.equals("Course")) {
			state = COURSE;
			//currentclass = new String(qName);
		}
		else if(name.equals("Current")) {
			state = CURRENT;
			//current = Integer.parseInt(qName);
		}
		else if(name.equals("Hours")) {
			state = HOURS;
			//hours = Integer.parseInt(qName);
		}
		else {
			state = CLEAR;
		}
	}
	
	public void characters (char ch[], int start, int length) {

		String text = ""; 
		if(state != CLEAR) {
			text = new String(ch).substring(start,start+length);
		}
		
		switch(state) {
		case COURSE:
			currentclass = text;
			break;
		case CURRENT:
			current = Integer.parseInt(text);
			break;
		case HOURS:
			try {
			  hours = Integer.parseInt(text);
			}
			catch(NumberFormatException e) {
				String[] parts = text.split("-");
				hours = Integer.parseInt(parts[1]);
			}
			break;
		case CLEAR:
		default:
		}
	}
	
	public void endElement(String uri, String name, String qName) {
		state = CLEAR;
		if(name.equals("Class") && currentclass.startsWith("CPSC")) {
			totals.add(new TotalCreditData(currentclass,current*hours));
		}		
	}
}