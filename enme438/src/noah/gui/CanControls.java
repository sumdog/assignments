/*
 * Created on Feb 17, 2005
 */
package noah.gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import noah.can.Can;

/**
 * @author skhanna
 *    protected int x,y,z;
    protected double xspacing, yspacing, zspacing, fourier, totaltime, timeinterval, aspacing;
 */
public class CanControls extends JPanel implements ActionListener,ChangeListener {

    private JSpinner zspin;
    private Can can;
    private CanInterface cinterface;
    private JButton step,solve, chords, reset, dump;
    private JLabel curiter;
    
    private void addField(String title, double num, String suffix, boolean i) {
        add(new JLabel(title));
        if(i) {
            add(new JLabel( ((int)num)+suffix ));
        } else {
            add(new JLabel(num + suffix));
        }
    }
    
    public CanControls(Can c, CanInterface i) {
        
        can = c;
        cinterface = i;
        int height = (int) (c.height*1000);
        double dheight = ((double)height)/1000; 
        setLayout(new GridLayout(0,2));
        addField("X: ",c.x," units",true);
        addField("Y: ",c.y," units",true);
        addField("Z: ",c.z," units",true);
        addField("X spacing: ",c.xspacing," meters",false);
        addField("Y spacing: ",c.yspacing," meters",false);
        addField("Z spacing: ",c.zspacing," meters",false);
        addField("Fluid: ",c.fluid," oz",false);
        addField("Fluid Height:",dheight," meters", false);
        addField("Angle spacing: ",c.aspacing," degrees",false);
        addField("Fourier: ",c.fourier," units",false);
        addField("Time Interval: ",c.timeinterval," seconds",true);
        addField("Total Time: ",c.totaltime," minutes",false);
        addField("Max Iterations",c.MAX_INT,"",true);
        
        add(new JLabel("Current Iteration"));
        curiter = new JLabel("0");
        add(curiter);
        
        add(new JLabel("Z: "));
        
        SpinnerModel model = new SpinnerNumberModel(0, 0, c.z-1, 1);
        
        zspin = new JSpinner(model);
        zspin.addChangeListener(this);
        add(zspin);
        
        step = new JButton("Step");
        step.addActionListener(this);
        add(step);
        
        solve = new JButton("Solve");
        solve.addActionListener(this);
        add(solve);
        
        chords = new JButton("Coordinates");
        chords.addActionListener(this);
        add(chords);
        
        reset = new JButton("Reset");
        reset.addActionListener(this);
        add(reset);
        reset.setEnabled(false);
        
        dump = new JButton("Dump");
        dump.addActionListener(this);
        add(dump);
        
    }

    

    
    public void actionPerformed(ActionEvent e) {
       
       
        
       if(e.getSource() == step) {
          
          can.stepCalculation();
          cinterface.updateTab();
          cinterface.setTab(can.calcindex % 3);
          if(can.calcindex >= can.MAX_INT) {
              step.setEnabled(false);
              solve.setEnabled(false);
          }
       } 
       else if(e.getSource() == solve) {
           

           while(can.calcindex < can.MAX_INT) {
               can.stepCalculation();
           }
           cinterface.updateTab();
           step.setEnabled(false);
           solve.setEnabled(false);
           cinterface.setTab(can.calcindex % 3);
       }
       else if(e.getSource() == chords) {
           cinterface.showChords();
           zspin.setEnabled(false);
           step.setEnabled(false);
           solve.setEnabled(false);
           reset.setEnabled(true);
           chords.setEnabled(false);
           dump.setEnabled(false);
       }
       else if(e.getSource() == reset ) {
           zspin.setEnabled(true);
           step.setEnabled(true);
           solve.setEnabled(true);
           cinterface.updateTab();
           chords.setEnabled(true);
           reset.setEnabled(false);
           dump.setEnabled(true);
       }
       else if(e.getSource() == dump) {
           cinterface.dumpTable();
       }
       
       curiter.setText(new Integer(can.calcindex).toString());
    }
    
  
    public void stateChanged(ChangeEvent e) {
                
        if(e.getSource() == zspin) {
               cinterface.zChange( Integer.parseInt(zspin.getValue().toString()) );
        }
    }

}
