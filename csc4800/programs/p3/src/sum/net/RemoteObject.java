/*
 * Created on Oct 20, 2004
 */
package sum.net;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 * @author skhanna
 */
public class RemoteObject extends UnicastRemoteObject implements RemoteEcho {

	public RemoteObject() throws RemoteException {
		super();
	}
	
	public String echoString(String s) {
		return s;
	}
	
}
