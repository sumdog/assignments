/*
 * Created on Nov 13, 2003
 */
package sum.graph;

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
    
    private PNode getNode(String s) {
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
