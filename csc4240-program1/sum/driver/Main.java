/*
 * Created on Sep 9, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.driver;

import java.io.BufferedReader;
import java.io.File;
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
	
	
	public static void usage()
	{
		System.out.println("\n\nCSC 4240 - Program 1 (Eight Square Puzzle Problem) \n\nUsage:\n\n");
		System.out.println("java -jar puzzle.jar [-g] <sourcefile>\n\n");
		System.out.println("-g           - Indicates if you want to start the graphical tree debugger\n");
		System.out.println("<sourcefile> - File to read in puzzle data from");
	}
	
	public static int start[][] = new int[3][3];
	public static int goal[][] = new int[3][3];

	public static void main(String[] args) 
	{
		
		if(args.length >= 1)
		{
			try
			{
				readFile(new File(args[args.length-1]));
			}
			catch (Exception e)
			{
				System.err.println("Error opening/parsing File");
				System.exit(2);
			}
		}
		else
		{
			usage();
			System.exit(1);
		}
		
		//-g option for debugging
		if(args.length >=1 && args[0].equals("-g"))
		{ StateViewer bob = new StateViewer(new State(start, null,0),new State(goal,null,-1)); }
		else
		{		
			System.out.println("A* Mahatten Distance");
			Search srch = new Search(start,goal);
			SearchResults results = srch.searchAStarMahatten();
			System.out.println("("+results.getNodes()+")"+" (depth="+results.getResultDepth()+")");
			results.printPath();
			
			System.out.println("A* Tiles Out of Place");
			results = srch.searchAStarTilesOutOfPlace();
			System.out.println("("+results.getNodes()+")"+" (depth="+results.getResultDepth()+")");
			results.printPath();
			
			
			System.out.println("IDS");
			results = srch.searchIDS(100000);
			System.out.println("("+results.getNodes()+")"+" (depth="+results.getResultDepth()+")");
			results.printPath();
		}
	}
	
	private static void readFile(File f) throws IOException
	{
		BufferedReader reader = new BufferedReader(new FileReader(f));
		reader.readLine(); //skip firt line

		for(int s=0; s<2; s++)
		{		
			String set = reader.readLine() + "," + reader.readLine() + "," + reader.readLine();
			StringTokenizer toke = new StringTokenizer(set,",\n");
			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
				{
					String t = toke.nextToken();
					if(s==0 && !t.equals("b")) 
					{ start[i][j] = Integer.parseInt(t); }
					else if(s==0) 
					{ start[i][j] = 0; }
					else if(s==1 && !t.equals("b"))
					{ goal[i][j] = Integer.parseInt(t); }
					else if(s==1)
					{ goal[i][j] = 0; }	
				}
			reader.readLine(); //skip blank and title lines
			reader.readLine();
		}
	}
}







