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
        
        String[] temp = s.split("->");
        if(temp.length > 2) { throw new KBException("Invalid Statemnet");	}
        else if (temp.length == 2) {  predicate = parseElement(temp[1]); }
        else { predicate = null; }
                    
        subject = new Vector();
        StringTokenizer t = new StringTokenizer(temp[0],"&");
        while(t.hasMoreElements()) {
            subject.add(parseElement(t.nextToken()));
        }
       
    }// end constructor
    
    public Sentence(Sentence s, Vector subs) {
        //we're gonna change this, so make a copy
        this(s.toString());

        // don't make a copy of this, it really shouldn't change
        predicate = s.getPredicate(); 
        
        //loop though substitutions
        for(int x=0; x<subs.size(); x++) {
            changeArg(((Substitution)subs.elementAt(x)).getVariable(),
                ((Substitution)subs.elementAt(x)).getConstant());
        }
    }
    
    private void changeArg(Variable var, Constant sub) {
        for(int x=0; x<subject.size(); x++) {
            Element e = (Element) subject.elementAt(x);
            for(int y=0; y<e.getArguments().length; y++) {
                Argument a = e.getArguments()[y];
                if( a instanceof Variable && a.getArg().equals(var.getArg())  ) {
                    e.getArguments()[y] = sub;
                }
            }
        }
    }//end changeArg
    
    public Vector getSubject() { return subject; }
    public Element getPredicate() { return predicate; }

    private Element parseElement(String s) throws KBException {
        return new Element(s);
    }//end parseElement()
    
    public String toString() {
        String retval = new String();
        for(int x=0; x < subject.size(); x++) {
            retval = retval + subject.elementAt(x);
            if( x < subject.size() -1 ) { retval = retval + " & ";   }
        }
        if(predicate != null) { retval = retval + " -> " + predicate; }
        return retval;
    }

	public boolean containsSubject(Element s) {
        for(int i=0; i < subject.size(); i++) {
            if( ((Element)subject.elementAt(i)).getIdentifer().equals(s.getIdentifer())  ) {
                return true;
            }
        }
		return false;
	}

	/**
	 * 
	 */
	public boolean containsVariables() {
		for(int x=0; x<subject.size(); x++) {
            Element s = (Element) subject.elementAt(x);
            for(int y=0; y<s.getArguments().length; y++) {
                if( s.getArguments()[y] instanceof Variable) { return true;  }
            }
		}
        return false;
	}

}//end Sentence class
