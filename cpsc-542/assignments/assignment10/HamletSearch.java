/*
 * Assignment #9 for cpsc-542
 * 
 * Utility to search though Hamlet in XML using DOM parser
 * 
 * @author Sumit Khanna
 */


import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Iterator;

import org.jdom.*;
import org.jdom.input.*;
import org.jdom.output.*;
import org.jdom.xpath.*;



public class HamletSearch {
	

	/*
	 * program entry point.
	 */
	public static void main(String[] args) {
		if(args.length != 1) {
			printUsage();
		}
		else {
			HamletSearch h = new HamletSearch(new File("hamlet.xml"),args[0]);
		}
	}
	
	
	public HamletSearch(File f, String q) {
		try{
			
		   String act, scene, speaker, sline;
			
		   Document doc = new SAXBuilder().build(f);
		   XPath linePath = XPath.newInstance("//ACT");
		   List lines = linePath.selectNodes(doc);
		   Iterator i = lines.iterator();
		   while(i.hasNext()) {
			   Element line = (Element) i.next();
			   
			   //Get Current Act
			   act = line.getChild("TITLE").getContent().toString();
			   act = act.substring(8,act.length()-2);
			   
			   //get current Scene
			   Object[] scenes = line.getChildren("SCENE").toArray();
			   for(int j=0; j<scenes.length; j++) {
				   scene = ((Element) scenes[j]).getChild("TITLE").getContent().toString();
				   scene = scene.substring(8,scene.length()-2);
				   
				   //get speeches
				   Object[] speaches = ((Element) scenes[j]).getChildren("SPEECH").toArray();
				   for(int k=0; k<speaches.length; k++) {
					   speaker = ((Element) speaches[k]).getChild("SPEAKER").getContent().toString();
					   speaker = speaker.substring(8,speaker.length()-2);
					   
					   //search line
					   sline = ((Element) speaches[k]).getChild("LINE").getContent().toString();
					   sline = sline.substring(8,sline.length()-2);
					   
					   if(sline.toLowerCase().contains(q.toLowerCase())) {
						   System.out.println("Act:" + act);
						   System.out.println("Scene: " + scene);
						   System.out.println("Speaker: " + speaker);
						   System.out.println("Line: " + sline+"\n");
					   }
				   }
			   }
		   }
		   
		}
		catch(JDOMException e) {
			System.out.println("JDOM Error:" + e.getMessage());
		}
		catch(IOException e){
			System.out.println("IO Error:" + e.getMessage());
		}
	}
	
	/*
	 * prints program usage and exits with a return code of 1.
	 */
	public static void printUsage() {
		System.out.println("\nUsage: java HamletSearch <phrase>");
		System.out.println("\t<phrase> - phrase to search for in Hamlet\n");
		System.exit(1);
	}
	

}


