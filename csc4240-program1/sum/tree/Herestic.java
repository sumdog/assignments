/*
 * Created on Sep 8, 2003
 * Sumit Khanna
 */
package sum.tree;

//This Class contains Static Functions for
//determining Herestics
public class Herestic {

	//given the current and the goal arrays, this function 
	//determins the Mahatten Distace between the two
	public static int getMahattenDistance(int[][] current, int[][] goal)
	{
		int distance = 0;

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
	
	//given the current and the goal arrays, this function
	//determins the Tiles Out Of Place between the two
	public static int getTilesOutOfPlace(int[][] current, int[][] goal)
	{
		int distance = 0;
		
		for(int x=0;x<goal.length;x++)
			for(int y=0;y<goal.length;y++)
				if(current[x][y] != goal[x][y]) {distance++;}
		
		return distance;
	}
	
	//Private function used to pass location values
	private static Location getLocation(int a, int[][] current)
	{
		for(int x=0;x<current.length;x++)
			for(int y=0;y<current.length;y++)
				if(current[x][y] == a) { return new Location(x,y); }
				
		return null;
	}

}

//simple class used from the static getLocation funciton above
class Location {
	public int x;
	public int y;	
	public Location(int x,int y) { this.x = x; this.y = y; }
}