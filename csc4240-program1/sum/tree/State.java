package sum.tree;

import java.util.Stack;

/*
 * Created on Sep 7, 2003
 */

//This Class represents a given state of the problem
public class State implements Comparable{

	//the plate is a matrix representation of the grid puzzle problem
	private int[][] plate;
	
	//parent to this state (null if root)
	private State parent;
	
	//depth we're at (controled by state expansion logic in this class)
	private int depth;
	
	//size of plate
	private int size;
	
	//herestic weight (controlled externally by Search class using Herestic static functions)
	private int herestic;
	
	//Constructs a state given the following plate, parent node and current depth
	//  The inital state should have a parent of null and a depth of 0
	public State(int[][] plate, State parent, int depth) 
	{	
		//initalize class
		this.plate = plate;
		this.depth = depth;
		this.parent = parent;
		herestic = 0;
		
		if(plate[0].length != plate.length) {
			/*throw new Exception("Plate must be a square");*/
			System.err.println("you are really stupid.");
		}
		
		size = plate.length;
	}
	
	//set the heristic using external herestic function
	public void setHerestic(int w)
	{ this.herestic = w; }
	
	//reurns the herestic
	public int getHerestic()
	{ return herestic;	}
	
	//compares objects based on Herestic for entry into Priority queue
	public int compareTo(Object o) 
	{
		if(!(o instanceof State)) 
		{
			return -1;
		}
		else 
		{
			return herestic - ((State)o).getHerestic(); 
		}
	}
	
	public int getSize() 
	{ return size; }
	
	public int[][] getPlate()
	{ return plate; }
	
	public int getDepth() 
	{ return depth;	}
	
	public State getParent()
	{ return parent; }
	
	public State[] expandState()
	{
		Stack temp = new Stack();
		
		for(int x=0; x<size; x++)
		  for(int y=0; y<size; y++)
			{
				if(plate[x][y] == 0) //blank square
				{ 
					//Middle square (up to four choices)
					if(x != 0 && y != 0 && x != size-1 && y != size-1)
					{
						if(plate[x+1][y] != 0) { temp.push(new State(swap(x,y,x+1,y),this,depth+1)); }
						if(plate[x-1][y] != 0) { temp.push(new State(swap(x,y,x-1,y),this,depth+1)); }
						if(plate[x][y+1] != 0) { temp.push(new State(swap(x,y,x,y+1),this,depth+1)); }
						if(plate[x][y-1] != 0) { temp.push(new State(swap(x,y,x,y-1),this,depth+1)); }
					}
					//corner square (up to two choices)
					else if(x==0 && y==0) //top left
					{	
						if(plate[x][y+1] != 0) { temp.push(new State(swap(x,y,x,y+1),this,depth+1)); }
						if(plate[x+1][y] != 0) { temp.push(new State(swap(x,y,x+1,y),this,depth+1)); } 
					}
					else if(x==0 && y==size-1) //top right
					{	
						if(plate[x][y-1] != 0) { temp.push(new State(swap(x,y,x,y-1),this,depth+1)); }
						if(plate[x+1][y] != 0) { temp.push(new State(swap(x,y,x+1,y),this,depth+1)); } 
					}
					else if(x==size-1 && y==size-1) //bottom right
					{
						if(plate[x][y-1] != 0) { temp.push(new State(swap(x,y,x,y-1),this,depth+1)); }
						if(plate[x-1][y] != 0) { temp.push(new State(swap(x,y,x-1,y),this,depth+1)); } 						
					}
					else if(y==0 && x==size-1)//bottom left
					{
						if(plate[x][y+1] != 0) { temp.push(new State(swap(x,y,x,y+1),this,depth+1)); }
						if(plate[x-1][y] != 0) { temp.push(new State(swap(x,y,x-1,y),this,depth+1)); } 		
					}
					//edge squares (up to three choices)
					else if(x==0) //top edge
					{
						if(plate[x+1][y] != 0) { temp.push(new State(swap(x,y,x+1,y),this,depth+1)); }
						if(plate[x][y+1] != 0) { temp.push(new State(swap(x,y,x,y+1),this,depth+1)); }
						if(plate[x][y-1] != 0) { temp.push(new State(swap(x,y,x,y-1),this,depth+1)); }					
					}
					else if(x==size-1) //bottom edge
					{
						if(plate[x-1][y] != 0) { temp.push(new State(swap(x,y,x-1,y),this,depth+1)); }
						if(plate[x][y+1] != 0) { temp.push(new State(swap(x,y,x,y+1),this,depth+1)); }
						if(plate[x][y-1] != 0) { temp.push(new State(swap(x,y,x,y-1),this,depth+1)); }											
					}
					else if(y==0) //left edge
					{
						if(plate[x-1][y] != 0) { temp.push(new State(swap(x,y,x-1,y),this,depth+1)); }
						if(plate[x][y+1] != 0) { temp.push(new State(swap(x,y,x,y+1),this,depth+1)); }
						if(plate[x+1][y] != 0) { temp.push(new State(swap(x+1,y,x,y),this,depth+1)); }
					}
					else if(y==size-1) //right edge
					{
						if(plate[x-1][y] != 0) { temp.push(new State(swap(x,y,x-1,y),this,depth+1)); }
						if(plate[x][y-1] != 0) { temp.push(new State(swap(x,y,x,y-1),this,depth+1)); }
						if(plate[x+1][y] != 0) { temp.push(new State(swap(x+1,y,x,y),this,depth+1)); }						
					}
				}
			}//end for loop
		
		State[] retval = new State[temp.size()];
		for(int x=0; x<temp.size(); x++) 
		{ retval[x] = (State) temp.elementAt(x); }
		return retval;
	}
	
	public String toString() 
	{
		String retval = new String("[");
		
		for(int x=0; x<size; x++)
		{
			retval += " [";
			for(int y=0; y<size; y++)
			{
				retval = retval + plate[x][y] + ",";
			}
			retval += "] ";
		}

        retval += "]";
		
		return retval;
	}
	

	//creates a new plate with the two numbers indicated by
	//the parameters swapped
	private int[][] swap(int x1, int y1, int x2, int y2)
	{
		int[][] retval = new int[size][size];
		
		for(int x=0; x<size; x++)
		  for(int y=0; y<size; y++)
		  {
		  	retval[x][y] = plate[x][y];
		  }
		
		int tmp1;
		tmp1 = retval[x1][y1];
		retval[x1][y1] = retval[x2][y2];
		retval[x2][y2] = tmp1; 
		
		return retval;
	}

	public boolean equals(Object o)
	{
			for(int x=0; x<size; x++)
			  for(int y=0; y<size; y++)
				if(((State)o).getPlate()[x][y] != plate[x][y]) { return false; }
			return true;
	}
}
