/*
 * Created on Oct 27, 2003
 */
package sum.kb;

/**
 * @author skhanna
 */
public abstract class Argument {

    private String arg;
    
    public Argument(String s) {
        arg = s;
    }
    
    public String getArg() { return arg; }
    public void setArg(String s) { arg = s;  }
    public String toString() { return arg;  }
}
