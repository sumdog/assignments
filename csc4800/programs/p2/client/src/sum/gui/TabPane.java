/*
 * Created on Sep 28, 2004
 * 
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * Class containing tabs, individual components and
 * their event handlers
 */
package sum.gui;
import sum.net.ConnectionAck;
import sum.net.ConnectionHandler;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextArea;
import javax.swing.JList;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * @author skhanna
 */
class TabPane extends JTabbedPane implements ActionListener, ListSelectionListener {

	private JTextField insssn3, insssn2, insssn4, inslname, insfname, inshousenum, insstreet,
		inscity, insstate, inszip, qssn, listlname;
	private JButton listgo, qgo, insadd;
	private JComboBox qfield;
    private JTextArea qresult;
    private JList listssn;
	
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
		qfield = new JComboBox(new Object[] {
                new ComboOption("Name",ConnectionHandler.GET_NAME),
                new ComboOption("House Number",ConnectionHandler.GET_HOUSE_NUM),
                new ComboOption("Street",ConnectionHandler.GET_STREET),
                new ComboOption("City",ConnectionHandler.GET_CITY),
                new ComboOption("State",ConnectionHandler.GET_STATE),
                new ComboOption("Zip",ConnectionHandler.GET_ZIP)
        });
        qssn = new JTextField(10);
        qgo = new JButton("Submit");
        qresult = new JTextArea(10,40);
        qresult.setEditable(false);
        qgo.addActionListener(this);
		addTab("Query",new JPanel(){
			{
				setLayout(new BorderLayout());
				add(new JPanel(){
					{
                        setLayout(new FlowLayout());
						add(new JLabel("SSN"));
                        add(qssn);
                        add(new JLabel("Query"));
                        add(qfield);
                        add(qgo);
					}
				},BorderLayout.NORTH);
                add(qresult,BorderLayout.CENTER);
			}
		});
        listlname = new JTextField(10);
        listgo = new JButton("List");
        listgo.addActionListener(this);
        listssn = new JList();
        listssn.addListSelectionListener(this);
        listssn.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		addTab("List", new JPanel(){
			{
				setLayout(new BorderLayout());
                add(new JPanel() {
                    {
                      setLayout(new FlowLayout());
                      add(new JLabel("Last Name"));
                      add(listlname);
                      add(listgo);
                    }
                },BorderLayout.NORTH);
                add(new JScrollPane(listssn),BorderLayout.CENTER);
			}
		});
	}

    public void valueChanged(ListSelectionEvent e) {
        qssn.setText( listssn.getSelectedValue().toString() );
        qresult.setText("");
        setSelectedIndex(1);
    }
	/* (non-Javadoc)
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 */
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == insadd) {
			String[] query = { inslname.getText(), insfname.getText(), insssn3.getText()+insssn2.getText()+insssn4.getText(), insstreet.getText(), inshousenum.getText(), inscity.getText(), insstate.getText(), inszip.getText() };
			ConnectionAck a = socket.sendQuery(ConnectionHandler.ADD_PERSON,query);
			if(a.acktype == ConnectionAck.ACK) {
				//clear our fields
				insssn3.setText("");
				insssn2.setText("");
				insssn4.setText("");
				inslname.setText("");
				insfname.setText("");
				inshousenum.setText("");
				insstreet.setText("");
				inscity.setText("");
				insstate.setText("");
				inszip.setText("");
			}
			a.displayMessageDialog();
		}
        else if(e.getSource() == qgo) {
            ConnectionAck a = socket.sendQuery( ((ComboOption)qfield.getSelectedItem()).REQ_TYPE,new String[] {qssn.getText() });
            if(a.acktype == ConnectionAck.ACK) {
                qresult.setText(a.messages[0]);
            }
            else {
                qresult.setText("");
                a.displayMessageDialog();
            }
        }
        else if(e.getSource() == listgo) {
            ConnectionAck a = socket.sendQuery(ConnectionHandler.GET_SOC_SEC_NO,new String[] { listlname.getText() });
            if(a.acktype == ConnectionAck.ACK) {
                listssn.setListData(a.messages);
            }
            else {
                listssn.setListData(new String[] {});
                a.displayMessageDialog();
            }
        }
	}	
}


class ComboOption {
	
	public final String COMMON_NAME;
	
	public final char REQ_TYPE;
	
	public ComboOption(String c, char r) {
		COMMON_NAME = c;
		REQ_TYPE = r;
	}
	
	public String toString() {
		return COMMON_NAME;
	}
	
}











