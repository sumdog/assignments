/*
 * Created on Oct 20, 2004
 */
package sum;

import sum.net.RemoteEcho;
import sum.gui.ClientPanel;

import java.applet.Applet;

import java.rmi.Naming;

/**
 * @author skhanna
 */
public class RMIApplet extends Applet { 
	
	RemoteEcho robj;
	
	public void init() {

			System.err.println(getCodeBase().getHost());
		try {
			robj = (RemoteEcho)Naming.lookup("//" + getCodeBase().getHost() + "/EchoServer");
			this.add(new ClientPanel(robj));
		}
		catch(Exception e){
			System.err.println("Error connecting to Remote Object");
			System.exit(4);
		}
	}
	
}
