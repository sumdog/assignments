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
    
    public float correctRow(Vector pvarvalset,  String val) {
        int count = 0;
        for(int y=0; y< pset.size(); y++) {
            for( int w=0; w < pvarvalset.size(); w++) {
                PVarValSet v = ((PVarValSet)pvarvalset.elementAt(w));
                PSet p = (PSet)pset.elementAt(y);
                if(  v.name.equals(p.name) && v.val.equals(p.val)) {
                    count++;
                }
            }
        }
        if(count != pset.size()) { return -1; }
        
        for(int x=0; x < pvalue.size(); x++) {
            PValue v = (PValue)pvalue.elementAt(x);
            if(v.val.equals(val)) { return v.f; }
        }
        
        //should NOT get here
        return -1;
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
