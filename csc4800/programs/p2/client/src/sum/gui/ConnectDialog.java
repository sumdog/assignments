/*
 * Created on Sep 28, 2004
 * 
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * Dialog that is displayed when program first starts 
 * or the user decides to reconnect
 */
package sum.gui;

import sum.net.ConnectionHandler;
import sum.Client;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JOptionPane;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JLabel;

/**
 * @author skhanna
 */
public class ConnectDialog extends JDialog implements ActionListener {
	
	private JTextField tf_hostname, tf_port;
	private JButton b_connect, b_quit;
	
    public ConnectDialog() {
        super(new JFrame(),"Connect to Server",true);
        
        //set layout for dialog
        this.getContentPane().setLayout(new BorderLayout(10,0));
        this.setSize(200,110);
        this.setResizable(false);
        
        //Left Panel with Host/Port lables
        this.getContentPane().add(new JPanel() {
        	//psuedo constructor
        	{
        		setLayout(new GridLayout(2,1));
        		add(new JLabel("  Host"));
        		add(new JLabel("  Port"));
        	}	
        },BorderLayout.WEST);
        
        //center panel with host/port text entry fields
        tf_hostname = new JTextField("localhost",30);
        tf_port     = new JTextField("9001",5);
        this.getContentPane().add(new JPanel() {
        	{
        		setLayout(new GridLayout(2,1));
        		add(tf_hostname);
        		add(tf_port);
        	}
        },BorderLayout.CENTER);
        
        //bottom panel with connect and quit button
        b_connect = new JButton("Connect");
        b_quit    = new JButton("Quit");
        this.getContentPane().add(new JPanel() {
        	{
        		setLayout(new FlowLayout(FlowLayout.CENTER));
        		add(b_connect);
        		add(b_quit);
        	}
        }, BorderLayout.SOUTH);
        
        b_connect.addActionListener(this);
        b_quit.addActionListener(this);
        
        addWindowListener(new WindowAdapter() {
        	  public void windowClosing(WindowEvent e) {
        		System.exit(0);
        	}
        });
        
        Client.centerWindow(this);
        this.show();
    }
    
	/* (non-Javadoc)
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 */
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == b_quit) {
			System.exit(0);
		}
		else if(e.getSource() == b_connect) {
			int prt = 0;
			try { prt = Integer.parseInt(tf_port.getText()); }
			catch(NumberFormatException f) {
				JOptionPane.showMessageDialog(new JFrame(),"Invalid Port","Error",JOptionPane.ERROR_MESSAGE);
			}
			if(prt < 1 || prt > 65535) {
				JOptionPane.showMessageDialog(new JFrame(),"Port must be within the range 1 to 65535","Error",JOptionPane.ERROR_MESSAGE);
			}
			ConnectionHandler socket = new ConnectionHandler(tf_hostname.getText(),prt);
			if(socket.connect()) {
				new MainWindow(socket);
				this.hide();
			}
			else {
				JOptionPane.showMessageDialog(new JFrame(),"Cannot Connect to Host","Connection Error",JOptionPane.ERROR_MESSAGE);
			}
		}		
	}
}