/*
 * Created on Sep 8, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.tree;

/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class Search {

	public final int BFS   = 0;
	public final int ASTAR = 1;
	
	private int type;
	private int goal[][];
	private State root;
	private State current;
	
	public Search(int start[][], int goal[][], int type)
	{
		this.type = type;
		this.goal = goal;
		root = new State(start,null,0);
		current = root;
	}

}
