/*
 * Created on Sep 9, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.driver;

import java.io.BufferedReader;
import java.io.File;
//import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

import sum.tree.*;
import sum.gui.StateViewer;
;
/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class Main {

	public static void main(String[] args) 
	{
		//int start[][] = { {6,5,4},{0,0,0},{3,2,1} };
		//int goal[][] = { {1,2,3},{0,0,0},{4,5,6} };
		int start[][] = { {1,2,3},{4,8,6},{7,0,9} };
		int goal[][] = { {1,2,3},{4,0,6},{7,8,9} };
		
		StateViewer bob = new StateViewer(new State(start, null,0),new State(goal,null,-1));
		
		Search srch = new Search(start,goal);
		//SearchResults results = srch.searchAStarMahatten();
		//System.out.println("("+results.getNodes()+")"+" (depth="+results.getResultDepth()+")");
		//results.printPath();
		
		//SearchResults results = srch.searchAStarTilesOutOfPlace();
		//System.out.println("("+results.getNodes()+")"+" (depth="+results.getResultDepth()+")");
		//results.printPath();
		
		/*
		Search s = new Search(start,goal);
		SearchResults result = s.searchIDS(100000);
		
		System.out.println("("+result.getNodes()+")"+" (depth="+result.getResultDepth()+")");
		result.printPath();*/
	}
	
	private void readFile(File f) throws IOException
	{
		BufferedReader reader = new BufferedReader(new FileReader(f));
		reader.readLine(); //skip firt line
		String set = reader.readLine() + "," + reader.readLine() + "," + reader.readLine();
		StringTokenizer toke = new StringTokenizer(set);
	}
}
