package examples.hello;
import java.rmi.Naming;
import java.rmi.RemoteExcpetion;
import java.rmi.RMISecurityManager;
import java.rum.server.UnicaseRemoteObject;
public class HelloImp1 extends UnicaseRemoteObject implements Hello {

    public HelloImp1() throws RemoteException { super(); }
    public String sayHello(String message) { return message; }
    public static void main (String args) {
      if(System.getSecurityManager() == null) {
        System.setSecurityManager(new RMISecurityManager());
      }
      try {
         HellowImp1 obj = new HelloImp1();
	 Naming.rebind("//myhost/HelloServer", obj);
	 System.out.println("HelloServer boud in registry");
      }
      catch(Exception e) {
         System.out.println("HellowImp1 err: " + e.getMessage());
	 e.printStackTrace();
      }
    }
}
