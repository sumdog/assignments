/*
 * Created on Feb 17, 2005
 */
package noah.gui;

import noah.can.Can;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
/**
 * @author skhanna
 */
public class SetupDialog extends JDialog implements ActionListener {

    
    private JTextField x, y, z, aspace, xspace, yspace, zspace, forure, totaltime, intemp, outtemp, fluid;
    private JButton ok, cancel, clear;
    private JComboBox set;
    
    private JTextField addInputField(String title, String units) {
        getContentPane().add(new JLabel(title));
        JTextField t = new JTextField();
        getContentPane().add(t);
        getContentPane().add(new JLabel(units));
        return t;
    }
    
    private JButton addButton(String title) {
        JButton b = new JButton(title);
        getContentPane().add(b);
        b.addActionListener(this);
        return b;
    }
    
    public SetupDialog() {
        setTitle("Input Specification");
        setSize(300,300);
        getContentPane().setLayout(new GridLayout(0,3));
        
        getContentPane().add(new JLabel("Test Set"));
        Object[] t = new String[] { "Custom" , "Set1" };
        set = new JComboBox(  t );
        set.addActionListener(this);
        getContentPane().add(set);
        getContentPane().add(new JLabel(""));        
        
        x = addInputField("Size of x","nodes");
        y = addInputField("Size of y","nodes");
        z = addInputField("Size of z","nodes");
        fluid = addInputField("Fluid","oz");
        aspace = addInputField("Angle Spacing","degrees");
        xspace = addInputField("X spacing","inches");
        //yspace = addInputField("Y spacing","inches");
        zspace = addInputField("Z spacing","inches");
        forure = addInputField("Forure","units");
        totaltime = addInputField("totaltime","minutes");
        intemp = addInputField("Inside Temp","F");
        outtemp = addInputField("Outside Temp","F");
        
        ok = addButton("OK");
        cancel = addButton("Cancel");
        clear = addButton("Clear");
        
        
        show();

    }
    
    private int getInt(JTextField t) {
        return Integer.parseInt(t.getText());        
    }
    private double getDouble(JTextField t) {
        return Double.parseDouble(t.getText());
    }
    
    public void actionPerformed(ActionEvent e) {
        
        if(e.getSource() == ok) {                      
            Can mycan = new Can(getInt(x),
                    getInt(y),
                    getInt(z),
                    getDouble(xspace),
                    getDouble(zspace),
                    getDouble(forure),
                    getDouble(totaltime),
                    getDouble(aspace),
                    getDouble(intemp),
                    getDouble(outtemp),
                    getDouble(fluid)
            );
            hide();
            MainWindow w = new MainWindow(mycan);
        }
        else if(e.getSource() == cancel) {
            System.exit(0);
        }
        else if(e.getSource() == clear) {
            x.setText("");
            y.setText("");
            z.setText("");
            aspace.setText("");
            xspace.setText("");
            yspace.setText("");
            zspace.setText("");
            forure.setText("");
            totaltime.setText("");
            intemp.setText("");
            outtemp.setText("");
        }
        else if( e.getSource() == set ) {
            if (set.getSelectedItem().equals("Set1")) {
                x.setText("261");
                y.setText("3");
                z.setText("921");
                aspace.setText("1");
                xspace.setText(".005");
                zspace.setText(".005");
                forure.setText("0.5");
                totaltime.setText("1");
                intemp.setText("75");
                outtemp.setText("0");
                fluid.setText("12");
                
                x.setEnabled(false);
                y.setEnabled(false);
                z.setEnabled(false);
                aspace.setEnabled(false);
                xspace.setEnabled(false);
                zspace.setEnabled(false);
                forure.setEnabled(false);
                totaltime.setEnabled(false);
                intemp.setEnabled(false);
                outtemp.setEnabled(false);
                fluid.setEnabled(false);
                
            }
            else {
                x.setEnabled(true);
                y.setEnabled(true);
                z.setEnabled(true);
                aspace.setEnabled(true);
                xspace.setEnabled(true);
                zspace.setEnabled(true);
                forure.setEnabled(true);
                totaltime.setEnabled(true);
                intemp.setEnabled(true);
                outtemp.setEnabled(true);
                fluid.setEnabled(true);                
            }

        }
    }
}


class DataSet {
    
    String s;
    
    public DataSet(String s) {
        this.s = s;
    }
    public String toString() {
        return s;
    }
}