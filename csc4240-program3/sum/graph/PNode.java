/*
 * Created on Nov 9, 2003
 */
package sum.graph;

import java.util.Vector;

/**
 * @author skhanna
 */
public class PNode {
       

    /**
     * names for discrete variables
     */
    private String[] bools;
    
    /*
     * name of current node
     */
    private String name;
    
    /*
     * rows of probablity table
     */
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
    
    
    public String getName() { return name; }
    
    public String[] getVars() { return bools; }
    
    public String toString() {
        String retval = "<Name: \""+name+"\" Values: {";
        for(int x=0; x<bools.length; x++) {
            retval += bools[x];
            if(x != bools.length-1) { retval += ","; }
        }
        retval += "}>\n";
        /*
        for(int x=0; x<rows.size(); x++) {
            retval += "\n"+rows.elementAt(x);
        }*/
        return retval;
    }
}
