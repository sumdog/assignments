/*
 * Assignment #8 for cpsc-542
 * 
 * Utility to search though Hamlet in XML using SAX2 parser
 * 
 * @author Sumit Khanna
 */


import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Date;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;

/*
 * program entry point.
 */
public class Search {
	
	private static AbstractSearch search; 
	private static Date start,end;
	
	public static void main(String[] args) {
		if(args.length != 3 ) {
			printUsage();
		}
				
		if(args[0].equals("SAX")) {
			search = new SAXSearch(new File(args[1]),args[2]);
		}
		else if(args[0].equals("DOM")) {
			search = new DOMSearch(new File(args[1]),args[2]);
		}
		else {
			printUsage();
		}
		
		start = new Date();
		search.processSearch();
		end = new Date();
		
		System.err.println("Execution Time: " + (end.getTime() - start.getTime()) + "ms");
	}
	
	/*
	 * prints program usage and exits with a return code of 1.
	 */
	public static void printUsage() {
		System.out.println("\nUsage: java HamletSearch [SAX|DOM] <file> <phrase>");
		System.out.println("\t<phrase> - phrase to search for in Hamlet\n");
		System.exit(1);
	}
}


