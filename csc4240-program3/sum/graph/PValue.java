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
public class PValue {
    
    String val;
    float f;
    
    public PValue(String val, float f) {
        this.f = f;
        this.val = val;
    }
    
    public String toString() {
        return "<"+val+"="+f+">";
    }

}
