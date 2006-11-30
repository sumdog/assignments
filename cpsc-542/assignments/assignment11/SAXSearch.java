import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;


public class SAXSearch extends AbstractSearch {

	public SAXSearch(File f, String q) {
		super(f, q);
	}

	@Override
	public void processSearch() {
		File f = xmlfile;
		String q = query;
		
		try {
			XMLReader xr = XMLReaderFactory.createXMLReader();
			DefaultHandler handle = new HamletSaxHandler(q);
			xr.setContentHandler(handle);
			try {
				xr.parse(new InputSource(new FileReader(f)));
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

}


class HamletSaxHandler extends DefaultHandler {
	
	/*
	 * string to search for.
	 */
	private String searchq;
	
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
	 * initalize variables for handler object's state.
	 * @param q search string
	 */
	public HamletSaxHandler(String q) {
		searchq = q;
		act = "";
		scene = "";
		speaker = "";
		state = CLEAR;
		tstate = CLEAR;
	}
	
	public void startElement(String uri, String name, String qName, Attributes attrs) {
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
	}
	public void characters (char ch[], int start, int length) {
		String data = new String(ch,start,length);
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
	public void endElement(String uri, String name, String qName) {
	  state = CLEAR;
	}
}