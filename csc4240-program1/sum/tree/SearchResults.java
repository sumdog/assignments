/*
 * Created on Sep 9, 2003
 */
package sum.tree;

//This class is passed back from the Search class's static 
//functions and indicates search results/failures
public class SearchResults 
{
	private State[] path;
	private int nodes;
	private int depthfound;

	//Search will use this constructor to constructs its results
	//  nodes = number of nodes searched
	//  depthfound = the depth at which result was found
	//  path = the goal node which can be used to trace the path using getParent()	
	public SearchResults(int nodes, int depthfound, State path)
	{
		this.nodes = nodes;
		this.depthfound = depthfound;
		if(path != null)
		{
			this.path = new State[depthfound];
			for(int x=0; x<depthfound; x++, path = path.getParent()) 
			{ this.path[x] = path; }
		}
		else
		{ this.path = null; }
	}
	
	//prints the path from goal to start to standard out
	public void printPath()
	{
		if(path == null) 
		{System.out.println("Search Abandoned After Examining "+nodes+" nodes");}
		else
		{
			for(int x=0; x<path.length;x++)
				System.out.println(path[x].toString()+"\n");
		}
	}
	
	public int getNodes() { return nodes; }
	public int getResultDepth() { return depthfound; }

}
