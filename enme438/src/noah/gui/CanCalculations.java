/*
 * Created on Feb 17, 2005
 */
package noah.gui;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import java.awt.GridLayout;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;

import javax.swing.JOptionPane;

import noah.can.Can;
import noah.can.Node;

/**
 * @author skhanna
 */
public class CanCalculations extends JTabbedPane implements CanInterface {

    private CanTab[] layers;
    
    private Can can;
    
    public CanCalculations(Can c) {
        can = c;
        layers = new CanTab[3];
        for(int i=0; i<3; i++) {
            layers[i] = new CanTab(can.getNodes(),i);
            addTab("Layer "+i,new JScrollPane(layers[i]));
        }
    }
    
    public void zChange(int z) {
        for(int x=0; x<layers.length; x++) {
            layers[x].changeZ(z);
        }
    }
    public void updateTab() {
        for(int i=0; i<3; i++) {
            layers[i].updateTab();
        }
    }
    public void setTab(int i) {
        setSelectedIndex(i);
    }
    
    public void showChords() {
        layers[getSelectedIndex()].showCord();
    }
    
    public void dumpTable() {
        JFileChooser f = new JFileChooser();
        int returnVal = f.showOpenDialog(this);
        if(returnVal == JFileChooser.APPROVE_OPTION) {
            dumpFile(f.getSelectedFile());
        }
    }
    
    private void dumpFile(File f) {
        Node[][][] n = layers[getSelectedIndex()].nodes;
        int layer = layers[getSelectedIndex()].layer;
        
        try {
            
            FileOutputStream o = new FileOutputStream(f);
            PrintStream p = new PrintStream( o );
            
            int curz = -1;
            for(int z=0; z<n[0][0].length; z++) {
                p.println("\n\nz:"+z);
                for(int y=0; y < n[0].length; y++) {
                    for(int x=0; x < n.length; x++) {
                        p.print(n[x][y][z].getTemp(layer)+"\t");
                    }
                    p.print("\n");
                }
            }
            
            p.close();
            o.close();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(new JFrame(),"Error writing to File","Error",JOptionPane.ERROR_MESSAGE);
        }
        
    }
}


class CanTab extends JPanel {
    
    Node[][][] nodes;
    JLabel[][] labels;
    int layer,z;
    
    CanTab(Node c[][][], int layer) {
        nodes = c;
        this.layer = layer;
        z = 0;
        
        setLayout(new GridLayout(c[0].length,c.length,10,10));
        labels = new JLabel[c.length][c[0].length];
              
        for(int y=0; y<labels[0].length; y++) {
            for(int x=0; x<labels.length; x++) {
                
                nodes[x][y][0].getTemp(layer);
                labels[x][y] = new JLabel(new Double(nodes[x][y][z].getTemp(layer)).toString());
                //labels[x][y] = new JLabel("X:"+x+" Y:"+y+" Z:"+z);
                add(labels[x][y],0);
            }
        }
    }
    
    void changeZ(int c) {
        z = c;
        updateTab();
    }
    
    void updateTab() {
        for(int x=0; x<labels.length; x++) {
            for(int y=0; y<labels[x].length; y++) {
                //labels[x][y].setText("X:"+x+" Y:"+y+" Z:"+z);
                labels[x][y].setText(new Double(nodes[x][y][z].getTemp(layer)).toString());
            }
        }
    }
    
    void showCord() {
        for(int x=0; x<labels.length; x++) {
            for(int y=0; y<labels[x].length; y++) {
                labels[x][y].setText("X:"+x+" Y:"+y+" Z:"+z);
                //labels[x][y].setText(new Double(nodes[x][y][z].getTemp(layer)).toString());
            }
        }
    }
}