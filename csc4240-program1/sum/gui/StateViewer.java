/*
 * Created on Sep 7, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package sum.gui;

import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


import sum.tree.State;

/**
 * @author skhanna
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class StateViewer extends JFrame implements ListSelectionListener {

	private State root;

	private State current;
	
	private JPanel plate;
	
	private JSplitPane spane;
	
	private JList expansions;
	
	private boolean listlock;
	
	public StateViewer(State root)
	{
		listlock = false;
		
		plate = new JPanel();
		plate.setLayout(new GridLayout(root.getSize(),root.getSize()));
		this.root = root;
		this.current = root;
		
		int[][] tmp = root.getPlate();
		for(int x=0; x<root.getSize(); x++)
		  for(int y=0; y<root.getSize();y++) {
		  		plate.add(new JLabel(new Integer(tmp[x][y]).toString()));
		  }
		  
		spane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		spane.add(plate);

		expansions = new JList(root.expandState());
		expansions.addListSelectionListener(this);
		spane.add(expansions);
		
		this.getContentPane().add(spane);
		this.setSize(300,300);
		this.setVisible(true);
		spane.setDividerLocation(.5);
	}

	/* (non-Javadoc)
	 * @see javax.swing.event.ListSelectionListener#valueChanged(javax.swing.event.ListSelectionEvent)
	 */
	public void valueChanged(ListSelectionEvent e) 
	{	
		if(e.getValueIsAdjusting() == false && !listlock)
		{ setState( (State) ((JList) e.getSource()).getSelectedValue() ); }
	}
	
	private void setState(State s)
	{
		plate.removeAll();
		current = s;
		int[][]tmp = s.getPlate();
		for(int x=0; x<s.getSize(); x++)
			for(int y=0; y<s.getSize(); y++)
			{ plate.add(new JLabel(new Integer(tmp[x][y]).toString())); }
		listlock = true;
		expansions.setListData(s.expandState());
		listlock = false;
		spane.validate();
	}

}
