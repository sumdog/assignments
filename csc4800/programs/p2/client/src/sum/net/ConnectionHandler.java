/*
 * Created on Sep 28, 2004
 * 
 * CSC4800/3400 - Sumit Khanna - Project 2
 * 
 * Layer of network and protocol abstraction
 */
package sum.net;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.InetSocketAddress;
import java.net.Socket;

/**
 * @author 
 */
public class ConnectionHandler {

    /*
     * client socket
     */
    private Socket socket;
    
    /*
     * hostname of server
     */
    private String host;
    
    /*
     * port of server
     */
    private int port;
    
    /*
     * used to write to socket
     */
    private BufferedWriter writer;
    
    /*
     * used to read from socket
     */
    private BufferedReader reader;
    
    /*
     * event listener for disconnects
     */
    private DisconnectListener disconnect;
       
    //Address Book Protocol Constants
    public static final char GET_NAME       = 'B';
    public static final char GET_SOC_SEC_NO = 'C';
    public static final char GET_STREET     = 'D';
    public static final char GET_HOUSE_NUM  = 'E';
    public static final char GET_ZIP        = 'F';
    public static final char GET_CITY       = 'G';
    public static final char GET_STATE      = 'H';
    public static final char ADD_PERSON     = 'I';
    public static final char QUIT           = 'Q';
    
    public ConnectionHandler(String host, int port) {
        
        socket = new Socket();
        this.host = host;
        this.port = port;
        
    }
    
    public void addDisconnectListener(DisconnectListener d) {
        disconnect = d;
    }
    
    public boolean connect() {
        try {
            socket.connect( new InetSocketAddress(host,port) );
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            return true;
        } catch (IOException e) {
            return false;
        }
    }
    
    public ConnectionAck sendQuery(char type,String[] args) {
        
        //format request
        String send = type + ":";
        for(int i=0; i<args.length; i++) {
            send += args[i] + ":";
        }
        send += "\n";
        
        //temp variables within this scpe
        String[] retval;
        String ack = "";
        try {
            //send request
            writer.write(send);
            writer.flush();
            
            //recieve acknowlegement (block until we get one line)
            ack = reader.readLine();
            if(ack == null) {disconnect.serverDisconnect(null);}

        } catch (IOException e) {
             if(disconnect != null) {
                 disconnect.serverDisconnect(e);
             }
        }
        
        //process ACK
        String[] ackparts = ack.split(":");
        char acktype = ackparts[0].charAt(0);
        retval = new String[ackparts.length-1];
        for(int i=1; i<ackparts.length; i++) {        
            retval[i-1] = ackparts[i];
        }
        return new ConnectionAck(acktype,retval);
    }
    
    public void disconnect() {
        try {
            writer.write(QUIT + ":");
            writer.flush();
            writer.close();
            reader.close();
            socket.close();
        }
        catch(Exception e) { /* do nothing */ }
    }
    
}
