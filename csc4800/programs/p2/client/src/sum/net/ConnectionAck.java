/*
 * Created on Sep 28, 2004
 *
 */
package sum.net;

import javax.swing.JOptionPane;
import javax.swing.JFrame;

/**
 * @author skhanna
 */
public class ConnectionAck {
    
    //Standard Protocol Constants
    public static final char ACK            = 'A';
    public static final char ERROR          = 'E';
    
    /*
     * type of acknowledgement
     */
    public final char acktype;
    
    /*
     * acknowledgement message
     */
    public final String[] messages;
    
    /*
     * Constructor (to be called from ConnectionHandler)
     */
    public ConnectionAck(char type, String[] messages) {
        acktype = type;
        this.messages = messages;
    }
    
    /*
     * displays a message dialog containing ack information for user
     */
    public void displayMessageDialog() {
    	String msg = "";
    	for(int x=0; x<messages.length; x++) {
    		msg += messages[x] + "\n";
    	}
        switch(acktype) {
            case ACK:
                JOptionPane.showMessageDialog(new JFrame(),msg,
                        "Server Message",JOptionPane.INFORMATION_MESSAGE);
                break;
            case ERROR:
                JOptionPane.showMessageDialog(new JFrame(),msg,
                        "Error",JOptionPane.ERROR_MESSAGE);
                break;
            default:
                JOptionPane.showMessageDialog(new JFrame(),"Malformed Ack From Server",
                        "Error",JOptionPane.ERROR_MESSAGE);
                break;
        }
    }   
}
