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
        //PNode[] roots = g.findRoots();
        //get rest
        //Vector rest = g.findNonRoots();
        
        //get all discrete variables for query variable
        String[] qvars = g.getNode(query).getVars();
        
        double[] sums = new double[qvars.length];
        
        Vector marked = new Vector();
        Vector pvarvalset = new Vector(); //a vector of vectors of pvarvalsets
        pvarvalset.add(new Vector());
        
        for(int q=0; q<qvars.length; q++){
            for( PNode p = g.getNextFesiable(marked); p != null; marked.add(p), p = g.getNextFesiable(marked)) {
               Vector newpar = new Vector();
               for(int w=0; w < pvarvalset.size() ; w++) {
                   //if(pvarvalset.size() > 0) { newpar.add(copyVector(pvarvalset)); }
                   //else { pvarvalset.add(new Vector()); }
                  // newpar.add(new PVarValSet(p.getName(), given [inSet(given,p.getName())].val,p.getProbablity()
                  if(p.getName().equals(query)) {
                      //this will change with q
                      newpar.add(copyVector((Vector)pvarvalset.elementAt(w),  new PVarValSet(p.getName(), qvars[q],p.getProbablity(  (Vector)pvarvalset.elementAt(w)  ,qvars[q]))  ));
                  }
                  else {
                      for(int e=0; e < p.getVars().length; e++) {
                          if(contains(p.getName(),given) != -1) {
                              newpar.add(copyVector((Vector)pvarvalset.elementAt(w),  new PVarValSet(p.getName(),  given[contains(p.getName(),given)].val   ,p.getProbablity(  (Vector)pvarvalset.elementAt(w)  ,  given[contains(p.getName(),given)].val   ))  ));                             
                          }
                          else {
                            newpar.add(copyVector((Vector)pvarvalset.elementAt(w),  new PVarValSet(p.getName(), p.getVars()[e],p.getProbablity(  (Vector)pvarvalset.elementAt(w)  ,p.getVars()[e]))  ));
                          }
                      }
                  }
               }
               //System.out.println(newpar);
               pvarvalset = newpar;
               pvarvalset.add(new Vector());
            }
            
            //do all our sumations/productions
            sums[q] = 0;
            double product = 1;
            for(int r=0; r < pvarvalset.size(); r++) {
                Vector v = (Vector) pvarvalset.elementAt(r);
                for(int t=0; t < v.size(); t++) {
                    product *= (((PVarValSet)v.elementAt(t)).prob);
                    //System.out.println(product);
                    if(product == 0) { product = 1;}
                }
                sums[q] += product;
                //System.out.println(sums[q]);
            }
            //reset marked nodes
            marked = new Vector();
        }//out of all our nested loops
        
        //...almost
        double total = 0;
        for(int t=0; t < sums.length; t++) {
            total += sums[t];
        }
        double alpha = 1 / total;

        
        //output
        System.out.print("<");
        for(int y=0; y < sums.length; y++) {
            double d = alpha * sums[y];
            if( y == sums.length-1 ) { System.out.print(",");}
        }
        System.out.print(">\n");
        
                /*
        //loop through each possible query variable
        for(int x=0; x<qvars.length; x++) {
            int i = 0;
            for( PNode p = g.getNextFesiable(marked); p != null; marked.add(p), p = g.getNextFesiable(marked), i++) {
                //if it's one of the evidence vars
                if(inSet(given, p.getName()) != -1) {
                    pvarvalset.add(i,new Vector());
                    //sums.add(new PVarValSet(p.getName(), p.getVars()[x], ))
                    ((Vector)pvarvalset.elementAt(i)).add(new PVarValSet(p.getName(), given[inSet(given,p.getName())].val,p.getProbablity((Vector)pvarvalset.elementAt(i),given[inSet(given,p.getName())].val)));
                }
                else {
                    int size = ((Vector)pvarvalset.elementAt(i)).size();
                    for(int z=0; z<= size; z++) {
                        pvarvalset.add(i,copyVector((Vector)pvarvalset.elementAt(i)));
                        //i++;
                        for(int a=0; a<qvars.length; a++) {
                            ((Vector)pvarvalset.elementAt(i)).add(new PVarValSet(p.getName(), p.getVars()[a], p.getProbablity((Vector)pvarvalset.elementAt(i),qvars[a])));
                        }
                    }
                }
                System.out.println(pvarvalset); 
            }
            //do all our sumations/productions
            sums[x] = 0;
            double product = 1;
            for(int r=0; r < pvarvalset.size(); r++) {
                Vector v = (Vector) pvarvalset.elementAt(r);
                for(int t=0; t < v.size(); t++) {
                    product *= (((PVarValSet)v.elementAt(t)).prob);
                    System.out.println(product);
                    if(product == 0) { product = 1;}
                }
                sums[x] += product;
                //System.out.println(sums[q]);
            }
            //marked = new Vector();
        }
        double total = 0;
         for(int t=0; t < sums.length; t++) {
             total += sums[t];
         }
         double alpha = 1 / total;

        
         //output
         System.out.print("<");
         for(int y=0; y < sums.length; y++) {
             double d = alpha * sums[y];
             if( y == sums.length-1 ) { System.out.println(",");}
         }
         System.out.println(">");      
        */
        
    }//end Query()
    
    public int contains(String s, PSet[] p) {
        for(int r=0 ; r < p.length; r++) {
            if(p[r].name.equals(s)) { return r; }
        }
        return -1;
    }
    
    private Vector copyVector(Vector src, Object o) {
        Vector retval = new Vector();
        for(int x=0; x<src.size(); x++) {
            retval.add(x,src.elementAt(x));
        }
        retval.add(o);
        return retval;
    }
    
    private int inSet (PSet[] p, String name) {
        for(int y=0; y<p.length; y++) {
            if(p[y].name.equals(name)) { return y; }
        }
        return -1;
    }
    
}//end class Query
