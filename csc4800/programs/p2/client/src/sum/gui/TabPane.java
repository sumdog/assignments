/*
 * Created on Sep 28, 2004
 */
package sum.gui;
import sum.net.ConnectionAck;
import sum.net.ConnectionHandler;

import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;

/**
 * @author skhanna
 */
class TabPane extends JTabbedPane implements ActionListener {

	private JTextField insssn3, insssn2, insssn4, inslname, insfname, inshousenum, insstreet,
		inscity, insstate, inszip, qssn, listlname;
	private JButton listgo, qgo, insadd;
	
	private ConnectionHandler socket;
	
	public TabPane (ConnectionHandler c) {
		
		socket = c;
		
		insssn3 = new JTextField(3);
		insssn2 = new JTextField(2);
		insssn4 = new JTextField(4);
		inslname = new JTextField(10);
		insfname = new JTextField(10);
		inshousenum = new JTextField(5);
		insstreet = new JTextField(10);
		inscity = new JTextField(10);
		insstate = new JTextField(2);
		inszip = new JTextField(5);
		insadd = new JButton("Add Entry");
		insadd.addActionListener(this);
		addTab("Insert",new JPanel() {
			{
				setLayout(new GridLayout(0,1));
				add(new JPanel() {
					{
						setLayout(new FlowLayout());
						add(new JLabel("SSN"));
						add(insssn3);
						add(insssn2);
						add(insssn4);
					}
				});
				add(new JPanel(){
					{
						setLayout(new FlowLayout());
						add(new JLabel("Last Name"));
						add(inslname);
						add(new JLabel("First"));
						add(insfname);
					}
					
				});
				add(new JPanel(){
					{
						setLayout(new FlowLayout());
						add(new JLabel("House Number"));
						add(inshousenum);
						add(new JLabel("Street"));
						add(insstreet);
					}
				});
				add(new JPanel(){
					{
						setLayout(new FlowLayout());
						add(new JLabel("City"));
						add(inscity);
						add(new JLabel("State"));
						add(insstate);
						add(new JLabel("Zip"));
						add(inszip);
					}
				});
				add(new JPanel() {
					{
						setLayout(new FlowLayout());
						add(insadd);
					}
				});
			}
		});
		addTab("Query",new JPanel(){
			{
				
			}
		});
		addTab("List", new JPanel(){
			{
				
			}
		});
	}

	/* (non-Javadoc)
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 */
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == insadd) {
			String[] query = { inslname.getText(), insfname.getText(), insssn3.getText()+insssn2.getText()+insssn4.getText(), insstreet.getText(), inshousenum.getText(), inscity.getText(), insstate.getText(), inszip.getText() };
			ConnectionAck a = socket.sendQuery(ConnectionHandler.ADD_PERSON,query);
			if(a.acktype == ConnectionAck.ACK) {
				/* TODO clear all fields */
			}
			a.displayMessageDialog();
		}	
	}
	

	
}
