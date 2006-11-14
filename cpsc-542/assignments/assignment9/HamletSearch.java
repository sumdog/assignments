/*
 * Assignment #9 for cpsc-542
 * 
 * Utility to search though Hamlet in XML using DOM parser
 * 
 * @author Sumit Khanna
 */


import java.io.File;
import java.io.IOException;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.apache.xerces.parsers.DOMParser;
import org.xml.sax.SAXException;

/*
 * program entry point.
 */
public class HamletSearch {
	
	public static void main(String[] args) {
		if(args.length != 1) {
			printUsage();
		}
		else {
			processSearch(new File("hamlet.xml"),args[0]);
		}
	}
	
	/*
	 * creates a parsing object that outputs results of search.
	 * @param f XML file that contains hamlet
	 * @param q search query string
	 */
	public static void processSearch(File f, String q) {
		try{
			  DOMParser parser = new DOMParser();
			  parser.parse(f.getPath());
			  Document doc = parser.getDocument();
			  parseTree(doc, q);
		}
		catch(SAXException e) {
			System.out.println("Fatal Error: SAX Exception " + e.getMessage());
			System.exit(2);
		}
		catch(IOException e) {
			System.out.println("IO Error: "+ e.getMessage());
			System.exit(3);
		}

	}
	
	/*
	 * prints program usage and exits with a return code of 1.
	 */
	public static void printUsage() {
		System.out.println("\nUsage: java HamletSearch <phrase>");
		System.out.println("\t<phrase> - phrase to search for in Hamlet\n");
		System.exit(1);
	}
	
	/*
	 * parses tree for search terms and outputs results to console
	 * @parm Node n document root
	 * @parm String q string to search for
	 */
	public static void parseTree(Node n, String q) {
		switch(n.getNodeType()) {
		case Node.DOCUMENT_NODE:
			break;
		case Node.ELEMENT_NODE:
			break;
		case Node.TEXT_NODE:
			break;
		}
	}
}


