/*
 * Created on Sep 29, 2004
 *
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * Program Entry Point
 */
package sum;
import sum.gui.ConnectDialog;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.Window;

/**
 * @author skhanna
 *
 */
public class Client {

	public static void main(String[] args) {
		new ConnectDialog();
	}
    
    public static void centerWindow(Window w){
        //Center the window (taken from Sun website)
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        Dimension frameSize = w.getSize();
        if (frameSize.height > screenSize.height) {
        frameSize.height = screenSize.height;
        }
        if (frameSize.width > screenSize.width) {
        frameSize.width = screenSize.width;
        }
        w.setLocation((screenSize.width - frameSize.width) / 2,
        (screenSize.height - frameSize.height) / 2);
        //end centering window code

    }
}
