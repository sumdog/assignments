/*
 * Created on Nov 9, 2003
 */
package sum.graph;

import java.util.Hashtable;
import java.util.Vector;

import sum.exception.GraphException;


/**
 * @author skhanna
 */
public class PNode {
       

    
    /**
     * probablity table which maps discrete boolean values to probablities
     */
    private Hashtable probs;

    /**
     * names for discrete variables
     */
    private String[] bools;
    
    /*
     * name of current node
     */
    private String name;
    
    private Vector rows;
     
     /**
      * Constructs a new node
      * @param name name of node
      * @param bools discrete variables for node
      */
    public PNode(String name, String[] bools) {
        this.name = name;
        this.bools = bools;
        rows = new Vector();    
    }
    
    public void addRow(PRow r) {
        rows.add(r);
    }
    
    public float getProbablity(String id) {
        Float retval = ((Float) probs.get(id));
        if(retval == null){ throw new GraphException("invalid probablity id: " +id ); }
        return retval.floatValue();
    }
    
    public void setProbablity(String parent, String var, float f) {
        
    }
    public void setProbablity(String var, float f) {
        
    }
    
    public String getName() { return name; }
    
    public String toString() {
        String retval = "<Name: \""+name+"\" Values: {";
        for(int x=0; x<bools.length; x++) {
            retval += bools[x];
            if(x != bools.length-1) { retval += ","; }
        }
        retval += "}>\n";
        for(int x=0; x<rows.size(); x++) {
            retval += "\n"+rows.elementAt(x);
        }
        return retval;
    }
}
