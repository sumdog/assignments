/*
 * Created on Oct 20, 2004
 */
package sum;
import java.rmi.RMISecurityManager;
import java.rmi.Naming;

import sum.net.RemoteObject;

/**
 * @author skhanna
 */
public class RMIServer { 

	
	public static String rmihost;
	
	public static void main(String[] args) {
		
		if(args.length != 1) {
			System.err.println("RMI Naming server not specified. Using localhost");
			rmihost = "localhost";
		}
		else {
			rmihost = args[0];
		}
		
		
		if(System.getSecurityManager() == null) {
			System.setSecurityManager(new RMISecurityManager());
		}
		
		try{
			RemoteObject robj = new RemoteObject();
			Naming.rebind("//"+rmihost+"/EchoServer", robj);
			System.out.println("RemoteObject registered with RMI registry");
		}
		catch(Exception e) {
			System.err.println("RMI Error: " + e.getMessage());
		}
	}
}
