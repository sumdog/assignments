/*
 * Created on Oct 20, 2004
 */
package sum.gui;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import sum.net.RemoteEcho;
/**
 * @author skhanna

 */
public class ClientPanel extends JPanel implements ActionListener {

	JButton send;
	JTextField input;
	JTextArea reply;
	
	RemoteEcho robj;
	
	public ClientPanel(RemoteEcho o) {
		super();
		setLayout(new BorderLayout());
		
		robj = o;
		
		input = new JTextField();
		send = new JButton("Send");
		reply = new JTextArea(10,50);
		reply.setEditable(false);
		
		add(input,BorderLayout.NORTH);
		add(send,BorderLayout.CENTER);
		add(reply,BorderLayout.SOUTH);
		
		send.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == send) {
			try {
				reply.setText(robj.echoString(input.getText()));
			}
			catch(Exception ex){
				//TODO: Error communicating with server message
			}
		}
	}
	
}
