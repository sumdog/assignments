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
    
    public void addFact(Element e) {
        forewardChain(e);
    }
    
    public Object forewardChain(Element e) {
        //loop over rules and find matches
         Vector matches = new Vector();
         for(int i=0; i<rules.size();i++){
             if(  ((Sentence) rules.elementAt(i)).containsSubject(e) ) {
                 matches.addElement(rules.elementAt(i));
             }
         }
        
        //substitutions
         Vector sub = new Vector();
        
        //itertate through all matches
         while(!matches.isEmpty()) {
             Sentence poped = (Sentence) matches.remove(0);
             Vector subject = poped.getSubject();
             //iterate through each Element in the subject of rule
             for(int q=0; q< subject.size(); q++) {
                 Element o = (Element) subject.elementAt(q);
                 //if argument sizes don't match, give up on this rule
                 if(o.getArguments().length != e.getArguments().length ) { continue; }
                 //compare arguments and make substitutions
                 for(int w=0; w< o.getArguments().length; w++) {
                     Argument r = o.getArguments()[w];
                     if(o.getIdentifer().equals(e.getIdentifer())) {
                        sub.add(new Substitution((Variable)r,(Constant)e.getArguments()[w],o.getIdentifer()));
                     }
                 }
             }
             //now see if out substitutions work
            Sentence foo = new Sentence(poped,sub);
            System.out.println(sub);
            System.out.println(foo);
            //if foo contains variables, we'll need to do this again
            System.out.println(foo.containsVariables());
         }
         return null;      
    }
    
    public boolean askQuestion(Element s) {
        //sanity check
        if(!s.isValidQuestion()) { throw new KBException("Invlaid Question"); }
        


        //check to see if any matches satisfy question
        /*for(int t=0; t<matches.size(); t++) {
            Sentence temp = (Sentence) matches.elementAt(t);
            Vector tv = temp.getSubject();
            if(tv.size() == 1) {
                Argument a[] = ((Element) tv.elementAt(0)).getArguments();
                if(a.length == 1 && a[0] instanceof Variable) {
                    //add new rule to kb and return true
                }
                else if(a[0] instanceof Constant && a[0].getArg() == s.)
            }
        }*/

        //debug
        //for(int t=0; t<matches.size(); t++) {
        //    System.out.println(matches.elementAt(t));
        //}
        return true;
    }
    

    public String dumpKB() {
        String retval = new String();
        for(int x=0; x< rules.size(); x++) {
            retval = retval + rules.elementAt(x) + "\n";
        }
        return retval;
    }
}
