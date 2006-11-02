package cpsc542.xml;

import java.io.File;
import java.util.ArrayList;
import org.w3c.dom.*;
import org.apache.xerces.parsers.DOMParser;

class DOMCredits
{
	final int COURSE = 1;
	final int CURRENT = 2;
	final int HOURS = 3;
	final int UNKNOWN = -1;
	
	int field = 0;
	
	int hours = 0;
	int current = 0; 
	String course;
	
	ArrayList<TotalCreditData> totals;
	
	public DOMCredits(String uri) {
		totals = new ArrayList<TotalCreditData>();
		try {
			DOMParser parser = new DOMParser();
			parser.parse(uri);
			Document doc = parser.getDocument();
			traverse_tree(doc);
	    } catch (Exception e) {
			e.printStackTrace(System.err);
	    }
		
	}
	
	private void traverse_tree(Node node) {
		if( node == null ) {
			return;
	    }
		int type = node.getNodeType();
	    switch (type) {
	    case Node.DOCUMENT_NODE: {
				traverse_tree(((Document)node).getDocumentElement());
				break;
			}
	    case Node.ELEMENT_NODE: {
				String elementName = node.getNodeName();
				field = UNKNOWN;
				if(elementName.equals("Hours"))
				    field = HOURS;
				else if(elementName.equals("Current"))
				    field = CURRENT;
				else if(elementName.equals("Course"))
					field = COURSE;

				NodeList childNodes = node.getChildNodes();	
				if(childNodes != null) {
				    int length = childNodes.getLength();
				    for (int loopIndex = 0; loopIndex < length ; loopIndex++)
				    {
						traverse_tree(childNodes.item(loopIndex));
				    }
				}
				break;
			}
	    case Node.TEXT_NODE: {
				String chData = node.getNodeValue().trim();
				if(chData.indexOf("\n") < 0 && chData.length() > 0) {
				    if(field == HOURS)
						try {
							hours = Integer.parseInt(chData);
						}
						catch(NumberFormatException e) {
							String[] parts = chData.split("-");
							hours = Integer.parseInt(parts[1]);
						}
					else if(field == CURRENT) {
						current = Integer.parseInt(chData);
						if(course.startsWith("CPSC")) {
							totals.add(new TotalCreditData( course, current*hours ));
						}
					}
					else if(field == COURSE)
						course = chData;
				}
			}
	    }
	}
	
	public TotalCreditData[] getTotalCredits() {
		TotalCreditData[] ret = new TotalCreditData[totals.size()];
		for(int i = 0; i<ret.length; i++) {
			ret[i] = (TotalCreditData) totals.get(i);
		}
		return ret;
	}
} 
public class DOMEngine extends AbstractParser {

	DOMCredits dom;
	public DOMEngine(File inputxml) {
		super(inputxml);
		dom = new DOMCredits(inputxml.getPath());
	}

	
	public TotalCreditData[] getTotalCredits() {
		return(dom.getTotalCredits());
	}
}
