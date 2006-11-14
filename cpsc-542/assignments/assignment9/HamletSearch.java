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
import org.w3c.dom.NodeList;
import org.apache.xerces.parsers.DOMParser;
import org.xml.sax.SAXException;

/*
 * program entry point.
 */
public class HamletSearch {
	
	/*
	 * parsing states to determine tag location.
	 * tstate can be either ACT or SCENE since they both exist in TITLE 
	 */
	private int state, tstate;
	
	/*
	 * values for state and tstate.
	 */
	private final int TITLE = 1, ACT = 2, SCENE = 3, SPEAKER = 4, LINE = 5, CLEAR = -1;
	
	/*
	 * current act, scene and speaker.
	 */
	private String act, scene, speaker;
	
	/*
	 * string to search for.
	 */
	private String searchq;
	
	
	public static void main(String[] args) {
		if(args.length != 1) {
			printUsage();
		}
		else {
			HamletSearch h = new HamletSearch(new File("hamlet.xml"),args[0]);
			//processSearch(new File("hamlet.xml"),args[0]);
		}
	}
	
	public HamletSearch(File f, String q) {
		searchq = q;
		act = "";
		scene = "";
		speaker = "";
		state = CLEAR;
		tstate = CLEAR;
		processSearch(f);
	}
	
	/*
	 * creates a parsing object that outputs results of search.
	 * @param f XML file that contains hamlet
	 * @param q search query string
	 */
	private void processSearch(File f) {
		try{
			  DOMParser parser = new DOMParser();
			  parser.parse(f.getPath());
			  Document doc = parser.getDocument();
			  parseTree(doc);
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
	public void parseTree(Node n) {
		
		//base case
		if(n == null) { return; }
		
		switch(n.getNodeType()) {
		case Node.DOCUMENT_NODE:
			parseTree(((Document)n).getDocumentElement());
			break;
		case Node.ELEMENT_NODE:
			String qName = n.getNodeName();
			
			if (qName.equals("SCENE")) {
				tstate = SCENE;
			}
			else if(qName.equals("SPEAKER")) {
				state = SPEAKER;
			}
			else if(qName.equals("TITLE")) {
				state = TITLE;
				
			}
			else if(qName.equals("LINE")) {
				state = LINE;
			}
			else if(qName.equals("ACT")) {
				tstate = ACT;
			}
			
			//deal with children
			NodeList childNodes = n.getChildNodes();	
			if(childNodes != null) {
			    int length = childNodes.getLength();
			    for (int i = 0; i < length ; i++)
			    {
					parseTree(childNodes.item(i));
			    }
			}
			
			break;
		case Node.TEXT_NODE:
			String data = n.getNodeValue().trim();
			if(data.indexOf("\n") < 0 && data.length() > 0) {
				switch(state) {
				case SPEAKER:
					speaker = data;
					break;
				case LINE:
					if (data.toLowerCase().contains(searchq.toLowerCase())) {
						System.out.println("Act: " + act +"\nScene: "+scene+ "\nSpeaker: " + speaker + "\nLine: " + data+"\n");
					}
					break;
				case TITLE:
					switch(tstate) {
					case ACT:
						act = data;
						break;
					case SCENE:
						scene = data;
						break;
					}
					break;
				default:
				case CLEAR:
					break;
				}
			}
			break;
		}
	}
}


