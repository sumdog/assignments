/*
 * Created on Nov 8, 2003
 */
package sum.main;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import sum.graph.Graph;
import sum.graph.PSet;

/**
 * @author skhanna
 */
public class Main {

	public static void main(String[] args) {
        Graph bnet = XMLParser.XMLParse(new File("bn.xml"));
	
       BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
       String input;
       try { input = reader.readLine(); } catch (IOException e) { input=null; System.err.println("Fatal Error"); System.exit(5); }
       while(input != null) {
            //process input
            String[] parts =   input.split("\\|");
            String[] givens = parts[1].split(",");
            PSet set[] = new PSet[givens.length];
            for(int x=0; x<givens.length; x++) {
                String splits[] = givens[x].split("\\=");
                if(x == givens.length -1) {
                    set[x] = new PSet(splits[0],splits[1].substring(0,splits[1].length()-1));
                }
                else {
                   set[x] = new PSet(splits[0],splits[1]);
                }
            }
            new Query(parts[0].substring(2,parts[0].length()),set,bnet);
            
            //read the next line
            try {
				input = reader.readLine();
			} catch (IOException e1) {
				System.err.println("Fatal Error");
                System.exit(5);
			}   
       }

    }
}
