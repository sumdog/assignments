/*
 * Created on Sep 28, 2004
 */
package sum.gui;
import sum.net.ConnectionHandler;

import java.awt.FlowLayout;
import java.awt.GridLayout;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;

/**
 * @author skhanna
 */
class TabPane extends JTabbedPane {

	private JTextField insssn3, insssn2, insssn4, inslname, insfname, inshousenum, insstreet,
		inscity, insstate, inszip, qssn, listlname;
	private JButton listgo, qgo, insadd;
	
	private ConnectionHandler socket;
	
	public TabPane (ConnectionHandler c) {
		
		socket = c;
		
		insssn3 = new JTextField(3);
		insssn2 = new JTextField(2);
		insssn4 = new JTextField(4);
		inslname = new JTextField(20);
		insfname = new JTextField(20);
		inshousenum = new JTextField(5);
		insstreet = new JTextField(20);
		inscity = new JTextField(20);
		insstate = new JTextField(2);
		inszip = new JTextField(5);
		addTab("Insert",new JPanel() {
			{
				setLayout(new GridLayout(1,0));
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
	
}
