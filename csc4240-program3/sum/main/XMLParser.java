/*
 * Created on Nov 8, 2003
 *
 */
package sum.main;
import java.io.File;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
 
import sum.graph.PNode;
import sum.graph.Graph;

/**
 * @author skhanna
 *
*/
public class XMLParser {

    private Document doc;
    
    private Graph graph;

    XMLParser(File file) {
        
        graph = new Graph();
        
        try {
		    doc = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(file);
		} catch (Exception e) {
            System.err.println("Error Parsing Document");
            System.exit(5);
		}
        
        Element root = doc.getDocumentElement();
        if(!root.getTagName().equals("bn")) {
            System.err.println("Invalid XML. Root must be of type \"bn\"");
            System.exit(6);
        }
        
        for(int x=0; x < root.getChildNodes().getLength(); x++) {
            Node child = root.getChildNodes().item(x);
            if(child.getNodeName().equals("vars")) {
                NodeList nl = child.getChildNodes();
                for(int y=0; y < nl.getLength(); y++){
                    if(nl.item(y).getNodeName().equals("var")) {
                        String name = null ;
                        String[] values = null;
                        NodeList sub_nl = nl.item(y).getChildNodes();
                        for(int z=0; z< sub_nl.getLength(); z++) {
                            if(sub_nl.item(z).getNodeName().equals("name")) {
                                name = sub_nl.item(z).getChildNodes().item(0).getNodeValue();
                            } else if (sub_nl.item(z).getNodeName().equals("vals")) {
                                NodeList vals_nl = sub_nl.item(z).getChildNodes();
                                values = new String[vals_nl.getLength()];
                                for(int i=0; i< vals_nl.getLength(); i++) {
                                    values[i] = vals_nl.item(i).getChildNodes().item(0).getNodeValue();
                                }
                            }
                            //finall, create the node
                        }
                        graph.addNode(new PNode(name, values));
                    }
                }// end <vars> section
            } else if (child.getNodeName().equals("topology")) {
                NodeList nl = child.getChildNodes();
                for(int i=0; i < nl.getLength(); i++) {
                    if(nl.item(i).getNodeName().equals("node")) {
                        String name = null;
                        NodeList sub_nl = nl.item(i).getChildNodes();
                        for(int j=0; j < sub_nl.getLength(); j++) {
                            if(sub_nl.item(j).getNodeName().equals("name")) {
                                name = sub_nl.item(j).getChildNodes().item(0).getNodeValue();
                            } else if (sub_nl.item(j).getNodeName().equals("parents")) {
                                NodeList parents_nl = sub_nl.item(j).getChildNodes();
                                for(int k=0; k < parents_nl.getLength(); k++) {
                                    if(parents_nl.item(k).getNodeName().equals("parent")) {
                                        //add edge to graph
                                        graph.addEdge(name,parents_nl.item(k).getChildNodes().item(0).getNodeValue());
                                    }
                                }
                            }
                        }
                    }
                }
            }//end <topology> section
            else if (child.getNodeName().equals("probabilities")) {

            }// end <probabilities> section
            
            //System.out.println(graph);
        }//end for()
        System.out.println(graph);
    }//end XMLParser()  (constructor)

}//end class
