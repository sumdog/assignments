package sum.tree;

import java.util.Stack;

/*
 * Created on Sep 7, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */

/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class State {

	private int[][] plate;
	
	private State parent;
	
	private int depth;
	
	private int size;
	
	public State(int[][] plate, State parent, int depth) 
	{	
		//initalize class
		this.plate = plate;
		this.depth = depth;
		this.parent = parent;
		
		if(plate[0].length != plate.length) {
			/*throw new Exception("Plate must be a square");*/
			System.err.println("you are really stupid.");
		}
		
		size = plate.length;
	}
	
	public int getSize() 
	{ return size; }
	
	public int[][] getPlate()
	{ return plate; }
	
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

}
