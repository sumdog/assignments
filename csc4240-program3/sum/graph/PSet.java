/*
 * Created on Nov 16, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.graph;

/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class PSet {
    
    private String name, val;
    
    public PSet(String name, String val) {
        this.name = name;
        this.val = val;
    } 
    
    public String toString() {
        return "<"+name+"="+val+">"; 
    }

}
