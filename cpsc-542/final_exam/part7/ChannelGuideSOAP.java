/**
 * CPSC-542 / Sumit Khanna / Final Exam 
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


public class ChannelGuideSOAP {

  public String[][] hexCast(int hour) {

    	
	int hours = -1;
	//What hour do we want?
	if (hour < 0) {
	    hours = new Date().getHours();
	}
	else {
	    hours = hour; 
	}

	//Start SAX Reader
	String[][] err = new String[1][1];
	err[0][0] = "none";
	try {
	    XMLReader xr = XMLReaderFactory.createXMLReader();
	    DefaultHandler handle = new SAXHandler(hours);
	    xr.setContentHandler(handle);

		xr.parse(new InputSource(new FileReader(getClass().getResource("programs.xml").getFile())));
		return ((SAXHandler) handle).getResults();
	}
	catch (FileNotFoundException e) {
		err[0][0] = "File Not Found";
	}
	catch (IOException e) {
		err[0][0] = "IO Exception";
	} 
	catch (SAXException e) {
	    err[0][0] = "Fatal SAX Error: ";
	}
	catch(Exception e) {
		err[0][0] = "Other Error";
	}
	return err;
  }
}




class SAXHandler extends DefaultHandler {

    private Vector<String[]> results;

    public String[][] getResults() {
    	String[][] ret = new String[results.size()][8];
    	
    	for(int i=0; i<results.size(); i ++) {
    		for(int j=0; j < 8; j++) {
    			ret[i][j] = results.get(i)[j];
    		}
    	}
    	
    	return ret;
    }

    /**
     * state tags for item section.
     */
    private final int TITLE = 1, CHANNEL=2, STIME=4, ETIME=5;

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
	actors = new Vector<String>();
	results = new Vector<String[]>();
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
     * chunk the actors into one string and save a string aray to the result set.
     */
    private void printShow() {

		String act = "";
		for(int i=0; i<actors.size(); i++) {
			act = act + actors.elementAt(i);
			if(i < actors.size() -1) {
				act = act + ", ";
			}
		}
		
		results.add( new String[] { channel, chanum, stime, etime,title, cat, rating, act } );
    }

}
