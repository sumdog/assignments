/*
 * Created on Oct 20, 2004
 */
package sum.net;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * @author skhanna
 */
public interface RemoteEcho extends Remote {
	
	String echoString(String s) throws RemoteException;

}
