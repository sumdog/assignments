package sum.kb;

import java.util.StringTokenizer;
import java.util.Vector;

/**
 * This class holds and preforms operations on a first order logic sentence.
 * @author skhanna
 */
public class Sentence {
    
    
    private Vector subject;
    private Element predicate;
    
    /**
     * Creates a first order logic sentence from the given string
	 * @param s string containing sentence
	 */
	public Sentence(String s) throws KBException {
        
        String[] temp = s.split("=>");
        if(temp.length != 2) { throw new KBException("Invalid Statemnet");	}
        
        predicate = parseElement(temp[1]);
        
        subject = new Vector();
        StringTokenizer t = new StringTokenizer(temp[0],"&");
        while(t.hasMoreElements()) {
            subject.add(parseElement(t.nextToken()));
        }
       
    }// end constructor

    private Element parseElement(String s) throws KBException {
        StringTokenizer t = new StringTokenizer(s.trim(),"()");
        if(t.countTokens() != 2) { throw new KBException("Invalid syntax: "+s);  }
        String name = t.nextToken();
        String var = t.nextToken();
        if(  Character.isUpperCase(var.charAt(0))   ) {
            return new Variable(name,var);
        }
        else {
            return new Constant(name,var);
        }
    }//end parseElement()
    
    public String toString() {
        String retval = new String();
        for(int x=0; x < subject.size(); x++) {
            retval = retval + subject.elementAt(x);
            if( x < subject.size() -1 ) { retval = retval + " & ";   }
        }
        retval = retval + " => " + predicate;
        return retval;
    }

}//end Sentence class
