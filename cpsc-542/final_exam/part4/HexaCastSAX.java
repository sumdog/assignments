/**
 * CPSC-542 / Sumit Khanna / Final Exam / Assignment #4 
 * 
 * This program parses an XML file using SAX and displays
 * information for TV shows that are either playing
 * during the current hour or shows that will be playing 
 * at the hour specified on the command line.
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Date;
import java.util.Vector;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;


public class HexaCastSAX {

	public static void main(String[] args) {
		
		//check args
		if(args.length == 2 || args.length == 1) {

		}
		
		//read hour var
		int hours = -1;
		if(args.length == 2 ) {
			try {
				hours = Integer.parseInt(args[1]);
			}
			catch(NumberFormatException e) {
				printUsage();
				System.exit(3);
			}
		}
		//if one not specified, use the current 
		else if(args.length == 1) {
			hours = new Date().getHours();
		}
		else {
			printUsage();
			System.exit(2);
		}
		
		//Start SAX Reader
		try {
			XMLReader xr = XMLReaderFactory.createXMLReader();
			DefaultHandler handle = new SAXHandler(hours);
			xr.setContentHandler(handle);
			try {
				xr.parse(new InputSource(new FileReader(new File(args[0]))));
			} catch (FileNotFoundException e) {
				System.err.println("File Not Found: " +e.getMessage());
				System.exit(4);
			} catch (IOException e) {
				System.err.println("IO Exception: " +e.getMessage());
				System.exit(5);
			}
		
		} catch (SAXException e) {
			System.err.println("Fatal SAX Error: " +e.getMessage());
			System.exit(6);
		}
	}
	
	/**
	 * prints program usage (does not exit).
	 */
	public static void printUsage() {
		System.err.println("Usage: java HexaCastSAX <file> <hour>");
		System.err.println("\t<file> - XML File with program information");
		System.err.println("\t<hour> - Hour to get results for [0..23] (optional)");
		System.err.println("\t         *if no hour specified, the current hour is used\n");
	}
}


class SAXHandler extends DefaultHandler {
	
	/**
	 * state tags for item section.
	 */
	private final int TITLE = 1, CHANNEL=2, CNUM = 3, STIME=4, ETIME=5;
	
	/**
	 * state tags for info section.
	 */
	private final int CAT = 6, ACTOR=7, RATING=8;
	
	/**
	 * state for clear.
	 */
	private final int CLEAR=0;
	
	/**
	 * search time.
	 */
	private int hour;
	
	/**
	 * current state.
	 */
	private int state;
	
	/**
	 * TV Program Elements.
	 */
	private String channel, chanum, stime, etime, title, cat, rating;
	
	/**
	 * TV program actors.
	 */
	private Vector<String> actors;
	
	
	/**
	 * Creates a handler object for the SAX parser to display TV shows for a given hour.
	 * Shows that are starting within the current hour or are currently playing during
	 * the hour will be output to <code>System.out</code>
	 * @param q Hour to search for (0..23).
	 */
	public SAXHandler(int q) {
		hour = q;
		actors = new Vector();
	}
	
	/*
	 * (non-Javadoc)
	 * @see org.xml.sax.helpers.DefaultHandler#startElement(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes)
	 */
	public void startElement(String uri, String name, String qName, Attributes attrs) {
		if(qName.equals("channel")) {
			state = CHANNEL;
			channel = attrs.getValue("name");
			chanum = attrs.getValue("number");
		}
		else if(qName.equals("startTime")) {
			state = STIME;
		}
		else if(qName.equals("endTime")) {
			state = ETIME;
		}
		else if(qName.equals("showTitle")) {
			state = TITLE;
		}
		else if(qName.equals("category")) {
			state = CAT;
		}
		else if(qName.equals("criticRating")) {
			state = RATING;
		}
		else if(qName.equals("actor")) {
			state = ACTOR;
		}

	}
	
	/*
	 * (non-Javadoc)
	 * @see org.xml.sax.helpers.DefaultHandler#characters(char[], int, int)
	 */
	public void characters (char ch[], int start, int length) {
		String data = new String(ch,start,length);
		switch(state) {
		case TITLE:
			title = data;
			break;
		case STIME:
			stime = data;
			break;
		case ETIME:
			etime = data;
			break;
		case CAT:
			cat = data;
			break;
		case RATING:
			rating = data;
			break;
		case ACTOR:
			actors.add(data);
			break;
		}
	}
	
	/*
	 * (non-Javadoc)
	 * @see org.xml.sax.helpers.DefaultHandler#endElement(java.lang.String, java.lang.String, java.lang.String)
	 */
	public void endElement(String uri, String name, String qName) {
		state = CLEAR;
		if(qName.equals("program")) {
			
			int starthour = Integer.parseInt(stime.split(":")[0]);
			int endhour = Integer.parseInt(etime.split(":")[0]);
			
			if(hour == starthour || (hour > starthour && hour <= endhour) ) {
			  printShow();
			}
			
			actors.clear();
		}
	}
	
	/*
	 * prints show data if show is within current hour.
	 * Uses the hour private variable and print out show information
	 * if show airs within the current hour or is currently airing. 
	 */
	private void printShow() {
		System.out.println("Show: " + title);
		System.out.println("Channel: " + channel + " (" + chanum + ")");
		System.out.println("Show Time: " + stime+" - "+etime);
		System.out.println("Genre : " + cat);
		if(actors.size() > 0) {
			System.out.print("Staring: ");
			for(int i=0;i<actors.size(); i++){
				System.out.print(actors.elementAt(i));
				if(i < actors.size() -1) {
					System.out.print(", ");
				}
				else {
					System.out.print("\n");
				}
			}
		}
		System.out.print("\n");
	}
	
}