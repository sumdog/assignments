/*
 * Created on Sep 29, 2004
 * 
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * Used to indicate to a window when a network
 * connection is lost
 */
package sum.net;

import java.io.IOException;

/**
 * @author skhanna
 */
public interface DisconnectListener {

    public void serverDisconnect(IOException e);
    
}
