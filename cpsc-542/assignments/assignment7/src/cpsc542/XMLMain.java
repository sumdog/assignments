package cpsc542;

import java.io.File;
import java.util.Arrays;
import java.util.Hashtable;

import javax.swing.JFileChooser;
import javax.swing.JFrame;

import cpsc542.gui.ReportGenerator;
import cpsc542.xml.AbstractParser;
import cpsc542.xml.SAXEngine;
import cpsc542.xml.TotalCreditData;

public class XMLMain {

	private static File xmlfile;
	
	private static AbstractParser parser;

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
		
		//now that we have the file, start parser
		parser = new SAXEngine(xmlfile);
		
		//pull total credits
		TotalCreditData[] totals = parser.getTotalCredits();
		//totals = normalizeData(totals);
		ReportGenerator r = new ReportGenerator(totals);
	}

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
