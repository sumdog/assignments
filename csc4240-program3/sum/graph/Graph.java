/*
 * Created on Nov 13, 2003
 */
package sum.graph;

import java.util.Vector;


/**
 * @author skhanna
 */
public class Graph {

    private boolean[][] edges;

    private PNode[] nodes;
    
    private int size,capacity;

	/**
	 * 
	 */
	public Graph() {
        edges = new boolean[10][10];
        for(int i=0; i<edges.length; i++) {
            for(int j=0; j<edges[0].length; j++) {
                edges[i][j] = false;
            }
        }
        nodes = new PNode[10];
        size = 0;
        capacity = 10;
	}

    public void addEdge(String parent, String child) {
        edges[indexOfNode(parent)][indexOfNode(child)] = true;
    }
    
    public PNode[] findRoots() {
        PNode[] retval = new PNode[size];
        int ret_loc = 0;
        for(int i=0; i<size; i++) {
            boolean check = true;
            for(int j=0; j<size; j++) {
                if(edges[i][j] ) {check=false;}
            }
            if(check) { retval[ret_loc++] = nodes[i]; }
        }
        
        PNode[] r = new PNode[ret_loc];
        for(int i=0; i < r.length; i++) {
            r[i] = retval[i];   
        }
        return r;
    }
    
    public Vector findNonRoots() {
        Vector retval = new Vector();
        for(int i=0; i<size; i++) {
            boolean check = true;
            for(int j=0; j<size; j++) {
                if(edges[i][j] ) {check=false;}
            }
            if(!check) { retval.add(nodes[i]); }
        }
        return retval;            
    }
    
    public Vector getParents(PNode p) {
        Vector retval = new Vector(size);
        int i = indexOfNode(p.getName());
        for(int j=0; j<size; j++) {
            if( edges[i][j] ) { retval.add(nodes[j]); }
        }
        return retval;
    }
    
    public int getSize(){return size;}
    
    private boolean isFesiable(Vector marked, PNode n) {
        if( marked.contains(n) ) { return false; }
        
        Vector parents = getParents(n);
            boolean fes = true;
            for(int j=0; j < parents.size(); j++) {
                if( !marked.contains(parents.elementAt(j)) ) { fes = false; }              
            }
            return fes;
    }
    
    public PNode getNextFesiable(Vector marked) {
        for(int x=0; x < size; x++) {
            if(isFesiable(marked,nodes[x])) {return nodes[x];}
        }
        return null;
    }
  
    //returns the first node that's not in the vector  
    public PNode getNextNode(Vector marked) {
        for( int x=0; x<size; x++) {
            if(!marked.contains(nodes[x])) {
                return nodes[x];
            }
        }
        return null;
    }
    
    public void addNode(PNode n) {
        if( size == capacity ) {
            resizeGraph(capacity + 10);
        }
        nodes[size++] = n;
    }
    
    private int indexOfNode(String s) {
        for(int x=0; x<size; x++) {
            if( nodes[x].getName().equals(s)) {
                return x;
            }
        }
        return -1;
    }
    
    public void addRow(String node, PRow p) {
        if(p != null) {
            getNode(node).addRow(p);
        }
    }
    
    public PNode getNode(String s) {
        for(int x=0; x < size; x++) {
            if(nodes[x].getName().equals(s)) { return nodes[x]; }
        }
        return null;
    }
    
    private void resizeGraph(int newsize) {
        //create new stuff
        boolean[][] new_edges = new boolean[newsize][newsize];
        PNode[] new_nodes = new PNode[newsize];
        
        //copy stuff
        for(int i=0; i<size; i++) {
            new_nodes[i] = nodes[i];
            for(int j=0; j<size; j++) {
                new_edges[i][j] = edges[i][j];
            }
        }
        
        //set stuff
        edges = new_edges;
        nodes = new_nodes;
        capacity = newsize;
    }
    
    public String toString() {
        String retval = "";
        //print nodes
        for(int x=0; x<size; x++){
            retval += nodes[x].toString() + "\n";
        }
        //print adj matrix
        for(int i=0; i<size; i++) {
            for(int j=0; j<size; j++) {
                retval += (edges[i][j]) ? "1" : "-";
            }
            retval += "\n";
        }
        return retval;
    }
}
