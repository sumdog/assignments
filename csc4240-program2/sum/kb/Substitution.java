/*
 * Created on Oct 26, 2003
 */
package sum.kb;

/**
 * @author skhanna
 */
public class Substitution {
    
    private Variable v;
    
    private Constant c;
    
    private String identifer;
    
    public Substitution(Variable v, Constant c, String identifier) {
        this.v = v;
        this.c = c;
        this.identifer = identifier;
    }
    
    public String getIdentifier() {return identifer; }
    public Variable getVariable() { return v;}
    public Constant getConstant() {return c;}
    public String toString() {
        return "["+identifer+"]{"+v.getArg()+"/"+c.getArg()+"}";
    }

}
