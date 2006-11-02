/*
 * Assignment #7 - cpsc-542 - Professor Smullen
 * 
 *  A java program that uses both SAX and DOM APIs 
 *  to calculate the total number of class hours
 *  for CPSC courses from an XML file.
 * 
 *  @author Sumit Khanna
 *  @author Feiqiong Liu
 *  @author Ryan Mauldin 
 */
package cpsc542;

import java.io.File;
import java.util.Arrays;
import java.util.Hashtable;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import cpsc542.gui.ReportGenerator;
import cpsc542.xml.AbstractParser;
import cpsc542.xml.DOMEngine;
import cpsc542.xml.SAXEngine;
import cpsc542.xml.TotalCreditData;

public class XMLMain { 

	/*
	 * XML data file.
	 */
	private static File xmlfile;
	
	/*
	 * parser that has both SAX and DOM implementation.
	 */
	private static AbstractParser parser;
	
	/*
	 * array that holds total number of credits.
	 */
	private static TotalCreditData[] totals;

	/*
	 * program entry point.
	 */
	public static void main(String[] args) {
		
		//get XML firename
		if(args.length == 1) {
			xmlfile = new File(args[0]);
		}
		else {
			 JFileChooser jf = new JFileChooser(); 
			 if(jf.showOpenDialog(new JFrame()) == JFileChooser.APPROVE_OPTION) {
				 xmlfile = jf.getSelectedFile();
			 }
			 else {
				 System.exit(0);
			 }
		}
		
		//present user with SAX/DOM option
		String[] parseroptions = {"SAX","DOM"};
		switch(JOptionPane.showOptionDialog(new JFrame(),"Which parser do you want to use?",
				"Choose Parser", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE,
				null, parseroptions, null)) {
		case 0:
			//now that we have the file, start parser
			parser = new SAXEngine(xmlfile);
			
			//pull total credits
			totals = parser.getTotalCredits();
			totals = normalizeData(totals);
			break;
		case 1:
			parser = new DOMEngine(xmlfile);
			totals = parser.getTotalCredits();
			totals = normalizeData(totals);
			break;
		case -1:
			System.exit(0);
		}
		

		ReportGenerator r = new ReportGenerator(totals);
	}

	/*
	 * combines the total scores of all classes with the same name.
	 */
	private static TotalCreditData[] normalizeData(TotalCreditData[] data) {
		
		Hashtable ht = new Hashtable();
		
		for(int x=0; x< data.length; x++) {
			if (ht.containsKey(data[x].getCourse())) {
				int i = ((Integer) ht.get(data[x].getCourse())).intValue();
				ht.put(data[x].getCourse(), new Integer(data[x].getTotal() + i));
			}
			else {
				ht.put(data[x].getCourse(),new Integer(data[x].getTotal()));
			}
		}
		
		Object[] keys = ht.keySet().toArray();
		Arrays.sort(keys);
		TotalCreditData[] ret = new TotalCreditData[keys.length];
		for(int z=0; z < ret.length; z++) {
			
			ret[z] = new TotalCreditData((String)keys[z],((Integer) ht.get(keys[z])).intValue());
		}
		return ret;
	}
}
