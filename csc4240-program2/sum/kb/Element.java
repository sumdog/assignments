/*
 * Created on Oct 16, 2003
 */
package sum.kb;

/**
 * @author skhanna
 */
public abstract class Element {
    
    protected String identifer;
    protected String var;
    
    public Element(String s, String v) {
        identifer = s;
        var = v;
    }
    
    public String getIdentifer() { return identifer;  }
    public String getValue() { return var; }
    public String toString() { return identifer+"("+var+")"; }
    
}
