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
public class Herestic {

	int[][] goal;

	public Herestic(int[][] goal)
	{
		this.goal = new int[goal.length][goal.length];
		for(int x=0;x<goal.length;x++)
			for(int y=0;y<goal.length;y++)
				this.goal[x][y] = goal[x][y]; 
	}
	
	public double getDirectDistance(int[][] current)
	{
		double distance = 0;
		
		for(int x=0;x<goal.length;x++)
			for(int y=0;y<goal.length;y++)
			{
				int gl = goal[x][y];
				Location t = getLocation(gl, current);
				if(t == null) { /* thorow some type of exception */ }
				distance += Math.sqrt(Math.pow(x-t.x,2) + Math.pow(y-t.y,2));
			}
		
		return distance;
	}
	
	public double getMahattenDistance(int[][] current)
	{
		double distance = 0;

		for(int x=0;x<goal.length;x++)
			for(int y=0;y<goal.length;y++)
			{
				int gl = goal[x][y];
				Location t = getLocation(gl, current);
				if(t == null) { /* thorow some type of exception */ }
				distance += Math.abs(x-t.x) + Math.abs(y-t.y);
			}		
		
		return distance;
	}
	
	private Location getLocation(int a, int[][] current)
	{
		for(int x=0;x<current.length;x++)
			for(int y=0;y<current.length;y++)
				if(current[x][y] == a) { return new Location(x,y); }
				
		return null;
	}

}

class Location {
	public int x;
	public int y;	
	public Location(int x,int y) { this.x = x; this.y = y; }
}