/*
 * Created on Sep 28, 2004
 * 
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * GUI component containing the actual tabpane
 * components of the query window
 */
package sum.gui;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;

import sum.net.ConnectionHandler;
import sum.net.DisconnectListener;
import sum.Client;

/**
 * @author skhanna
 */
public class MainWindow extends JFrame implements DisconnectListener, ActionListener {

    private final ConnectionHandler socket;
    
    public MainWindow(ConnectionHandler c) {
    	super();
        this.setSize(500,250);
        this.setTitle("csc4800client");
        this.setResizable(false);
        this.getContentPane().setLayout(new BorderLayout());
        this.getContentPane().add(new TabPane(c),BorderLayout.CENTER);
        this.getContentPane().add(new Menu(this),BorderLayout.NORTH);
        
        c.addDisconnectListener(this);
        
        socket = c;
        addWindowListener(new WindowAdapter(){
            
            public void windowClosing(WindowEvent e) {
                super.windowClosed(e);
                socket.disconnect();
                System.exit(0);
            }
        });
        
        Client.centerWindow(this);
        this.show();
    }


    public void serverDisconnect(IOException e) {
        JOptionPane.showMessageDialog(new JFrame(),"Disconnected From Server","Error",JOptionPane.ERROR_MESSAGE);
        this.hide();
        new ConnectDialog();
    }
    
    public void actionPerformed(ActionEvent e)  {
        if(e.getSource() == miDisconnect) {
            socket.disconnect();
            this.hide();
            new ConnectDialog();
        }
        else if(e.getSource() == miExit) {
            socket.disconnect();
            System.exit(0);
        }
        else if(e.getSource() == miAbout) {
            String s = "CSC4800 Program 2 Client\n" +
                        "Written by Sumit Khanna\n" +
                        "For Dr. Rogers CSC3400/4800 class\n" +
                        "GNU GPL 2004";
            JOptionPane.showMessageDialog(new JFrame(),s,"About",JOptionPane.PLAIN_MESSAGE);
        }
    }
		
    JMenu mFile, mHelp;
    JMenuItem miDisconnect, miExit, miAbout;
    
    class Menu extends JMenuBar {
        
        Menu(ActionListener a) {
            mFile = new JMenu("File");
            mFile.setMnemonic('F');
            miDisconnect = new JMenuItem("Disconnect");
            miDisconnect.setMnemonic('D');
            miDisconnect.addActionListener(a);
            miExit = new JMenuItem("Exit");
            miExit.setMnemonic('E');
            miExit.addActionListener(a);
            mFile.add(miDisconnect);
            mFile.add(miExit);
            
            mHelp = new JMenu("Help");
            mHelp.setMnemonic('H');
            miAbout = new JMenuItem("About");
            miAbout.setMnemonic('A');
            miAbout.addActionListener(a);
            mHelp.add(miAbout);
            
            add(mFile);
            add(mHelp);
        }
        
    }
}


