/**
 * CPSC-542 / Sumit Khanna / Final Exam / Assignment #5 
 * 
 * This program parses an XML file using DOM and displays
 * information for TV shows that are either playing
 * during the current hour or shows that will be playing 
 * at the hour specified on the command line.
 */
import java.util.Date;
import java.util.Vector;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.sun.org.apache.xerces.internal.parsers.DOMParser;


public class HexaCastDOM {

	/**
	 * hour of programs to list.
	 */
	private static int hour;
	
	/**
	 * Program entry point.
	 * @param args command line arguments
	 */
	public static void main(String[] args) {
		//check args
		if(args.length == 2 || args.length == 1) {

		}
		
		//read hour var
		hour = -1;
		if(args.length == 2 ) {
			try {
				hour = Integer.parseInt(args[1]);
			}
			catch(NumberFormatException e) {
				printUsage();
				System.exit(3);
			}
		}
		//if one not specified, use the current 
		else if(args.length == 1) {
			hour = new Date().getHours();
		}
		else {
			printUsage();
			System.exit(2);
		}
		
		actors = new Vector();
		
		try {
			DOMParser parser = new DOMParser();
			parser.parse(args[0]);
			Document doc = parser.getDocument();
			traverse_tree(doc);
	    } catch (Exception e) {
			e.printStackTrace(System.err);
	    }
	}
	
	/**
	 * prints program usage (does not exit).
	 */
	public static void printUsage() {
		System.err.println("\nUsage: java HexaCastDOM <file> <hour>");
		System.err.println("\t<file> - XML File with program information");
		System.err.println("\t<hour> - Hour to get results for [0..23] (optional)");
		System.err.println("\t         *if no hour specified, the current hour is used\n");
	}
	
	private static int state;
	
	/**
	 * state tags for item section.
	 */
	private static final int TITLE = 1, CHANNEL=2, CNUM = 3, STIME=4, ETIME=5;
	
	/**
	 * state tags for info section.
	 */
	private static final int CAT = 6, ACTOR=7, RATING=8;
	
	/**
	 * state for clear.
	 */
	private static final int CLEAR=0;
	
	/**
	 * TV Program Elements.
	 */
	private static String channel, chanum, stime, etime, title, cat, rating;
	
	/**
	 * TV program actors.
	 */
	private static Vector<String> actors;
	
	private static void traverse_tree(Node node) {
		if( node == null ) {
			return;
	    }
		int type = node.getNodeType();
	    switch (type) {
	    case Node.DOCUMENT_NODE: 
				traverse_tree(((Document)node).getDocumentElement());
				break;
			
	    case Node.ELEMENT_NODE: 
				String qName = node.getNodeName();
				state = CLEAR;
				
				if(qName.equals("startTime")) {
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
				else if(qName.equals("channel")) {
					state = CHANNEL;
					channel = node.getAttributes().getNamedItem("name").getNodeValue();
					chanum = node.getAttributes().getNamedItem("number").getNodeValue();
				}
				else if(qName.equals("program")) {
					if(title != null) {
					  
					  int starthour = Integer.parseInt(stime.split(":")[0]);
					  int endhour = Integer.parseInt(etime.split(":")[0]);
					  
					  if(hour == starthour || (hour > starthour && hour <= endhour) ) {
					     printShow();
					  }
					  
					  actors.clear();
					}
				}
				
				NodeList childNodes = node.getChildNodes();	
				if(childNodes != null) {
				    int length = childNodes.getLength();
				    for (int loopIndex = 0; loopIndex < length ; loopIndex++)
				    {
						traverse_tree(childNodes.item(loopIndex));
				    }
				}
				break;
			
	    case Node.TEXT_NODE: 
				String chData = node.getNodeValue().trim();
				if(chData.indexOf("\n") < 0 && chData.length() > 0) {
				    switch(state) {
				    case STIME:
				    	stime = chData;
				    	break;
				    case ETIME:
				    	etime = chData;
				    	break;
				    case TITLE:
				    	title = chData;
				    	break;
				    case CAT:
				    	cat = chData;
				    	break;
				    case RATING:
				    	rating = chData;
				    	break;
				    case ACTOR:
				    	actors.add(chData);
				    	break;
				    }
				}
			    break;
	    case Node.ATTRIBUTE_NODE:
	    	if (state == CHANNEL) {
	    		
	    	}
	    	break;
	    }
	}
		
	/*
	 * prints show data if show is within current hour.
	 * Uses the hour private variable and print out show information
	 * if show airs within the current hour or is currently airing. 
	 */
	private static void printShow() {
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
