/*
 * Created on Oct 16, 2003
 */
package sum.kb;

/**
 * @author skhanna
 */
public class Element {
    
    protected String identifer;
    protected Argument[] args;
    
    public Element(String s) {
        String tmp[] = s.trim().split("[()]");
        if(tmp.length != 2) { throw new KBException("Invalid Element " + s); }
        identifer = tmp[0];
        
        tmp = tmp[1].split(",");
        args = new Argument[tmp.length];
        for(int x=0; x<tmp.length; x++){
            if( Character.isLowerCase(tmp[x].charAt(0))  ) {
                args[x] = new Constant(tmp[x]);
            }
            else{
                args[x] = new Variable(tmp[x]);
            }
        }
    }
    
    public boolean equals(Object o) {
        return o.toString().equals(this.toString());
    }
    
    //this program restricts questions to only containing Constants (no variables)
    public boolean isValidQuestion() {
        for(int x=0; x<args.length; x++) {
            if(! (args[x] instanceof Constant)) { return false; }  
        }
        return true;
    }
    
    public String getIdentifer() { return identifer;  }
    public Argument[] getArguments() { return args; }
    public String toString() { 
        String retval = identifer + "(";
        for(int x=0; x<args.length; x++) {
            retval = retval + args[x];
            if(x != args.length-1) {
                retval = retval + ",";
            }
        }
        retval = retval + ")";
       return retval;
    }
    
}
