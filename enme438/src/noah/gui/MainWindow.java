/*
 * Created on Feb 17, 2005
 */
package noah.gui;

import javax.swing.JFrame;
import javax.swing.JSplitPane;

import noah.can.Can;

/**
 * @author skhanna
 */
public class MainWindow extends JFrame {

    private JSplitPane splitpane;
    
    private CanCalculations calculations; 
    private CanControls cancontrols;
    
    public MainWindow(Can c) {
        super("Noah's Can");
        setSize(1000,600);
        setTitle("Noah's Can");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        splitpane = new JSplitPane();
        calculations = new CanCalculations(c);
        splitpane.setRightComponent(calculations);
        cancontrols = new CanControls(c,calculations);
        splitpane.setLeftComponent(cancontrols); 
        getContentPane().add(splitpane);
        
        show();
        
    }

}
