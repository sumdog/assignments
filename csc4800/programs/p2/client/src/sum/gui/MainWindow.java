/*
 * Created on Sep 28, 2004
 *
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * 
 */
package sum.gui;

import java.awt.BorderLayout;
import javax.swing.JWindow;

import sum.net.ConnectionHandler;


/**
 * @author skhanna
 */
public class MainWindow extends JWindow {

    public MainWindow(ConnectionHandler c) {
        this.setSize(1000,500);
        this.getContentPane().setLayout(new BorderLayout());
        this.add(new TabPane(c),BorderLayout.CENTER);
        
        this.show();
    }
		
}


