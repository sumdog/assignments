/*
 * Created on Oct 13, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.kb;

import java.util.Vector;

/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class KnowledgeBase {
    
    private Vector rules;
    
    public KnowledgeBase() {
        rules = new Vector();        
    }
    
    public void addRule(Sentence s) {
        rules.add(s);
    }

    public String dumpKB() {
        String retval = new String();
        for(int x=0; x< rules.size(); x++) {
            retval = retval + rules.elementAt(x) + "\n";
        }
        return retval;
    }
}
