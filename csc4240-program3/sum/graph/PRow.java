/*
 * Created on Nov 16, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.graph;

import java.util.Vector;

/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class PRow {
    
    private Vector pset, pvalue;
    
    public PRow() {
        pset = new Vector();
        pvalue = new Vector();
    }

    public void addSet(PSet p) {
        pset.add(p);
    }
    
    public void addVal(PValue v) {
        pvalue.add(v);
    }
    
    public String toString() {
        String retval = "Given:\n";
        for(int i=0; i<pset.size();i++) {
            retval += pset.elementAt(i).toString() + "\n";
        }
        retval += "Assume:\n";
        for(int j=0; j<pvalue.size(); j++) {
            retval += pvalue.elementAt(j).toString() + "\n";
        }
        return retval;
    }
}
