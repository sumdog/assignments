/*
 * Created on Nov 8, 2003
 */
package sum.main;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * @author skhanna
 */
public class Main {

	public static void main(String[] args) {
        XMLParser bnet = new XMLParser(new File("bn.xml"));
	
       BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
       String input;
       try { input = reader.readLine(); } catch (IOException e) { input=null; System.err.println("Fatal Error"); System.exit(5); }
       while(input != null) {
            //process input
        
        
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
