/*
 * Created on Feb 17, 2005
 */
package noah.gui;

import noah.can.Can;

import javax.swing.JButton;
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
    }
}
