/*
 * Created on Sep 8, 2003
 */
package sum.tree;

import java.util.Hashtable;
import org.mcgraw.PriorityQueue;
import org.mcgraw.PriorityVector;

//This class handels the details of the search
public class Search {

	//varables needed for each search function
	private State goal;
	private State root;
	private State current;
	private int counter;
	
	//setup a search given a starting position and a goal
	public Search(int start[][], int goal[][])
	{
		this.goal = new State(goal,null,-1);
		root = new State(start,null,0);
		current = root;
	}
	
	//perform an Iterative Deepening Search that will stop after 
	// abandon depth
	public SearchResults searchIDS(int abandon)
	{
		PriorityQueue pq = new PriorityVector();
		Hashtable check = new Hashtable();
		pq.add(root);
		check.put(root.toString(),root);
		counter = 0;
		int d;
		for(d=0; d<abandon; d++)
		{
			while(!pq.isEmpty())
			{
				//infinate loop check
				current = (State) pq.remove();
				if(current.getDepth()-1 == d) { break; }
				while(check.containsKey(current.toString()))
				{ 	
					if(pq.isEmpty()) { break; }
					current = (State) pq.remove(); 
				}
				
				if(current.equals(goal)) { return new SearchResults(counter,current.getDepth(),current); }
				else
				{
					State[] expand = current.expandState();
					for(int x=0; x<expand.length; x++)
					{
						expand[x].setHerestic(1); 
						pq.add(expand[x]); 
					}
				}
				counter++;	
			}
		}
		return new SearchResults(counter,d,null);
		
	}
	
	
	//perform an A* tree search based on Mahatten Distance
	public SearchResults searchAStarMahatten()
	{
		PriorityQueue pq = new PriorityVector();
		Hashtable check = new Hashtable();
		pq.add(root);
		check.put(root.toString(),root);
		counter = 0;
		while(!pq.isEmpty())
		{
			//infinate loop check
			current = (State) pq.remove();
			while(check.containsKey(current.toString()))
			{ 
				if(pq.isEmpty()) { break; }
				current = (State) pq.remove(); 
			}
			
			if(current.equals(goal)) { return new SearchResults(counter,current.getDepth(),current); }
			else
			{
				State[] expand = current.expandState();
				for(int x=0; x<expand.length; x++)
				{
					expand[x].setHerestic(Herestic.getMahattenDistance(expand[x].getPlate(),goal.getPlate())); 
					pq.add(expand[x]); 
				}
			}
			counter++;		
		}
		return null;
	}
	
	//performs an A* search based on Tiles Out of Place
	public SearchResults searchAStarTilesOutOfPlace()
	{
		PriorityQueue pq = new PriorityVector();
		Hashtable check = new Hashtable();
		pq.add(root);
		check.put(root.toString(),root);
		counter = 0;
		while(!pq.isEmpty())
		{
			//infinate loop check
			current = (State) pq.remove();
			while(check.containsKey(current.toString()))
			{ 
				if(pq.isEmpty()) { break; }
				current = (State) pq.remove(); 
			}
			
			if(current.equals(goal)) { return new SearchResults(counter,current.getDepth(),current); }
			else
			{
				State[] expand = current.expandState();
				for(int x=0; x<expand.length; x++)
				{
					expand[x].setHerestic(Herestic.getTilesOutOfPlace(expand[x].getPlate(),goal.getPlate())); 
					pq.add(expand[x]); 
				}
			}
			counter++;		
		}
		return null;
	}
	

}

