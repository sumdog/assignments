/*
 * Created on Nov 16, 2003
 */
package sum.main;

import sum.graph.PSet;
import sum.graph.Graph;

/**
 * @author skhanna
 */
public class Query {
    
    public Query(String query, PSet[] given, Graph g) {
        System.out.println(query);
        for(int x=0; x<given.length; x++) { System.out.println(given[x]); }
    }
}
