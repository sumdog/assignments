/*
 * Created on Nov 16, 2003
 */
package sum.main;
import java.util.Vector;
import sum.graph.PNode;
import sum.graph.PSet;
import sum.graph.Graph;
import sum.graph.PVarValSet;

/**
 * @author skhanna
 */
public class Query {
    
    public Query(String query, PSet[] given, Graph g) {
        //get all nodes without parents
        PNode[] roots = g.findRoots();
        //get rest
        Vector rest = g.findNonRoots();
        
        //get all discrete variables for query variable
        String[] qvars = g.getNode(query).getVars();
        
        Vector marked = new Vector();
        Vector sums = new Vector();
                
        //loop through each possible query variable
        for(int x=0; x<qvars.length; x++) {
            for( PNode p = g.getNextFesiable(marked); p != null; p = g.getNextFesiable(marked)) {
                System.out.println(p);
                marked.add(p);
            }
        }
        
    }//end Query()
    

    
}//end class Query
