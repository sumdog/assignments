/*
 * Created on Nov 18, 2003
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
public class PVarValSet {

    public String name, val;
    public float prob;

    public PVarValSet(String name, String val, float f) {
        this.name = name;
        this.val = val;
        prob = f;
    }
    
    public String toString() {
        return "<"+name+","+val+"="+prob+">";
    }

}
