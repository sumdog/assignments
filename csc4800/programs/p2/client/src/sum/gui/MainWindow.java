/*
 * Created on Sep 28, 2004
 *
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * 
 */
package sum.gui;

import java.awt.BorderLayout;
import javax.swing.JFrame;

import sum.net.ConnectionHandler;

/**
 * @author skhanna
 */
public class MainWindow extends JFrame {

    public MainWindow(ConnectionHandler c) {
    	super();
        this.setSize(380,250);
        this.setName("csc4800client");
        this.getContentPane().setLayout(new BorderLayout());
        this.getContentPane().add(new TabPane(c),BorderLayout.CENTER);
        
        this.show();
    }
		
}


