package examples.hello;

import java.applet.Applet;
import java.awt.Graphics;
import java.rmi.Naming;
import java.rmi.RemoteException;

public class MyApplet extends Applet {

  MyObj obj = null;
  String returnVal;
  public void init() {
    try {
       obj = (MyObj)Naming.lookup("//" + getCodeBase().getHost() + "/MyServer");
       returnVal = obj.method();
    }
    catch (Exception e) {
       System.out.println(" Exception: " + e.getMessage());
       e.printStackTrace();
    }
  }
  public void paint(Graphics g) {
    g.drawString(returnVal, 25, 50);
  }
}
