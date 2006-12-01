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
		if(args.length != 2 ) {
			printUsage();
		}
				

		System.err.print(new File(args[0]).getName()+",");
		search = new SAXSearch(new File(args[0]),args[1]);
		doSearch();
		System.err.print(',');
		search = new DOMSearch(new File(args[0]),args[1]);
		doSearch();
		System.err.print('\n');
		
		start = new Date();
		search.processSearch();
		end = new Date();
		
		//System.err.println("Execution Time: " + (end.getTime() - start.getTime()) + "ms");
	}
	
	private static void doSearch() {
		start = new Date();
		search.processSearch();
		end = new Date();
		System.err.print(end.getTime() - start.getTime());
	}
	
	/*
	 * prints program usage and exits with a return code of 1.
	 */
	public static void printUsage() {
		System.out.println("\nUsage: java HamletSearch <file> <phrase>");
		System.out.println("\t<phrase> - phrase to search for in Hamlet\n");
		System.out.println("\nOutput: (coma seperated to stderr)");
		System.out.println("<filename>,<execution time for SAX>,<execution time for DOM>\n");
		System.exit(1);
	}
}


