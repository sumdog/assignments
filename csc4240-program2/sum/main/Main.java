/*
 * Created on Oct 13, 2003
 */
package sum.main;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

import sum.kb.*;


/**
 * Entry Point for program
 * @author skhanna
 */
public class Main {

    private static BufferedReader reader;
    private static KnowledgeBase kb;
    private static BufferedWriter writer;
    

    public static void main(String[] args) {
        
        kb = new KnowledgeBase();
        
        //read in knowledge base file (kb.txt)
        try {
			reader = new BufferedReader(new FileReader("kb.txt"));
            System.err.println("Reading kb.txt into Knowledge Base...");
            for(String line = reader.readLine(); line != null; line = reader.readLine()) {
                kb.addRule(new Sentence(line));
            }
		} catch (FileNotFoundException e) {
            System.err.println("Can not find file kb.txt");
            System.exit(2);
		} catch (IOException e) {
            System.err.println("Error Reading File");
            System.exit(3);
        }
        System.err.println("kb.txt successfully read into Knowledge Base...");
        
        //start interactive input loop
        reader = new BufferedReader(new InputStreamReader(System.in));
        System.err.print("$");
        String input;
        try { input = reader.readLine(); } catch (IOException e) { input=null; System.err.println("Fatal Error"); System.exit(5); }
        while(!input.trim().equals("quit")) {
          try {
                if(input.charAt(input.length()-1) == '?') {
                    //ask knowledge base something
                    kb.askQuestion(new Element(input.substring(0,input.length()-1)));
                }
                else {
                    try { kb.addFact(new Element(input));   }
                    catch(KBException e) { System.err.println("Invalid Rule"); }
                }
                System.err.print("$");
                input = reader.readLine();
            }
            catch(IOException e) {
                System.err.println("Error reading input! Bailing out.");
                System.exit(4);
            }
        }
        //dump knowledgebase (finalkb.txt) and exit program
        try{
            writer = new BufferedWriter(new FileWriter("finalkb.txt"));
            writer.write(kb.dumpKB());
            writer.close();
        }
        catch (IOException e){
            System.err.println("Error writing finalkb.txt! Bailing out.");
            System.exit(5);
        }
        
    }//end main()
}//end class Main








