/*
 * Created on Sep 7, 2003
 */
package sum.gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


import sum.tree.State;
import sum.tree.Herestic;

//This is a Graphical UserInterface to view states and their expansion
//it was used for testing only and therefore is poorly written and badly 
//commented. If you want to try and read it, good luck!
public class StateViewer extends JFrame implements ListSelectionListener, ActionListener {

	private State root;

	private State current;
	
	private JPanel plate;
	
	private JSplitPane spane;
	
	private JList expansions;
	
	private boolean listlock;
	
	private State goal;
	
	private JPanel bottom;
	
	private JLabel mat_distance;
	
	private JLabel sqr_distance;
	
	private JLabel depth;
	
	private JButton up;
	
	private JLabel compareto;
	
	private JLabel atgoal;
	
	public StateViewer(State root, State goal)
	{
		listlock = false;
		
		this.goal = goal;

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
		
		bottom = new JPanel();
		bottom.setLayout(new GridLayout(0,2));
		bottom.add(new JLabel("Goal:"));
		bottom.add(new JLabel((new State(goal.getPlate(),null,-1).toString())));
		bottom.add(new JLabel("Depth:"));
		depth = new JLabel(new Integer(root.getDepth()).toString());
		bottom.add(depth);
		bottom.add(new JLabel("Mahatten Distance:"));
		mat_distance = new JLabel(new Integer(Herestic.getMahattenDistance(root.getPlate(),goal.getPlate())).toString());
		bottom.add(mat_distance);
		bottom.add(new JLabel("Squares out of Place:"));
		sqr_distance = new JLabel(new Integer(Herestic.getTilesOutOfPlace(root.getPlate(),goal.getPlate())).toString());
		bottom.add(sqr_distance);
		bottom.add(new JLabel("parent.compareTo(current) (Mahatten Distance): "));
		compareto = new JLabel("");
		bottom.add(compareto);
		bottom.add(new JLabel("At Goal: "));
		atgoal = new JLabel( (root.equals(goal)) ? "true" : "false");
		bottom.add(atgoal);
		
		JButton up = new JButton("Parent Node");
		up.addActionListener(this);
		
		this.getContentPane().setLayout(new BorderLayout());
		this.getContentPane().add(up,BorderLayout.NORTH);
		this.getContentPane().add(bottom,BorderLayout.SOUTH);
		this.getContentPane().add(spane, BorderLayout.CENTER);
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
		{ 
			 State temp = (State) ((JList) e.getSource()).getSelectedValue();
			 setState(temp);

		}
	}
	
	private void setState(State s)
	{
		
		//update weight
		s.setHerestic(Herestic.getMahattenDistance(s.getPlate(),goal.getPlate()));
		
		//update goal labels
		compareto.setText(new Integer(s.compareTo(goal)).toString());
		atgoal.setText((s.equals(goal))?"true":"false");
		
		//update distance labels
		mat_distance.setText(new Integer(Herestic.getMahattenDistance(s.getPlate(),goal.getPlate())).toString());
		depth.setText(new Integer(s.getDepth()).toString()); 
		sqr_distance.setText(new Integer(Herestic.getTilesOutOfPlace(s.getPlate(),goal.getPlate())).toString());
		
		//update JList of children
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

	/* (non-Javadoc)
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 */
	public void actionPerformed(ActionEvent e) {
		if(current.getParent() != null)
		{  setState(current.getParent()); } 
		else
		{  }
	}
}
