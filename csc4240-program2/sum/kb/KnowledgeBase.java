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
    
    //sentences
    private Vector facts;
    
    public KnowledgeBase() {
        rules = new Vector();
        facts = new Vector();        
    }
    
    public void addRule(Sentence s) {
        rules.add(s);
    }
    
    public Vector findSub(Vector subject, Element e) {
        Vector sub = new Vector();
        //iterate through each Element in the subject of rule
         for(int q=0; q< subject.size(); q++) {
             Element o = (Element) subject.elementAt(q);
             //if argument sizes don't match, give up on this rule
             if(o.getArguments().length != e.getArguments().length ) { continue; }
             //compare arguments and make substitutions
             for(int w=0; w< o.getArguments().length; w++) {
                 Argument r = o.getArguments()[w];
                 if(o.getIdentifer().equals(e.getIdentifer()) && r instanceof Variable) {
                    sub.add(new Substitution((Variable)r,(Constant)e.getArguments()[w],o.getIdentifer()));
                 }
             }
         }
         return sub;        
    }
    
    public void addFact(Element e) {
        
        //loop over rules and find matches
         Vector matches = new Vector();
         for(int i=0; i<rules.size();i++){
             if(  ((Sentence) rules.elementAt(i)).containsSubject(e) ) {
                 matches.addElement(rules.elementAt(i));
             }
         }
        
        //substitutions
         Vector sub;
        
        //itertate through all matches
         while(!matches.isEmpty()) {
             Sentence poped = (Sentence) matches.remove(0);
             Vector subject = poped.getSubject();
            //find substution
             sub = findSub(subject,e);
             //now see if out substitutions work
            Sentence foo = new Sentence(poped,sub);
            if(!foo.containsVariables()) {
                Sentence b = new Sentence(foo.getPredicate().toString());
                facts.add(  (new Sentence(b,sub)).getSubject().elementAt(0) );
            }
            //if we need have unbound symbols, loop through existing facts 
            // and attempt to bind them
            else {
                secondStageSubstitution(foo,sub,-1);
            }
 
            //if foo contains variables, we'll need to do this again
            /*while(foo.containsVariables()) {
                //go through list of facts and make more substitutions
                for(int n=0; n<facts.size(); n++) {
                    Element fact = (Element) facts.elementAt(n);
                    
                }
            }*/
         } //end while( !matches.isEmpty() )
         
         //add our original fact 
         facts.add(e);
    }//end addFact()
    
    public void secondStageSubstitution(Sentence s, Vector sub, int skip) {
        for(int n=0; n<facts.size(); n++) {
            Element fact = (Element) facts.elementAt(n);
            if(n != skip && s.containsSubject(fact)) {
                //preform substitution
                Sentence ns = new Sentence(s,findSub(s.getSubject(),fact));
                if(ns.containsVariables()) {
                    secondStageSubstitution(ns,sub,n);
                } else {
                    //if everything in fully substituted sentence is true, add fact
                    boolean bar = true;
                    for(int k=0; k<ns.getSubject().size(); k++){
                        if(! askQuestion((Element) ns.getSubject().elementAt(k))) { bar = false;}
                    }
                    if(bar){
                        facts.add( new Sentence(new Sentence(ns.getPredicate().toString()),sub).getSubject().elementAt(0)  ); 
                    }
                }
            }
        }
    }
    
    public boolean askQuestion(Element s) {
        //sanity check
        if(!s.isValidQuestion()) { throw new KBException("Invlaid Question"); }
        
        for(int x=0; x<facts.size(); x++) {
            if( facts.elementAt(x).equals(s)   ) {return true;}
        }
        return false;
    }
    
    public String dumpKB() {
        return dumpRules() + dumpFacts();
    }
    public String dumpRules() {
        String retval = new String();
        for(int x=0; x< rules.size(); x++) {
            retval = retval + rules.elementAt(x) + "\n";
        }
        return retval;
    }
    
    public String dumpFacts() {
        String retval = new String();
        for(int x=0; x< facts.size(); x++) {
            retval = retval + facts.elementAt(x) + "\n";
        }
        return retval;        
    }
}
