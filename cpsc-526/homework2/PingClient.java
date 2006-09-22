import java.io.*;
import java.net.*;
import java.util.Calendar;

public class PingClient implements Runnable {

    public static void main(String []args) {
        if(args.length != 2){
          System.err.println("Usage: PingClient hostname port");
          System.exit(2);
        }
        
        PingClient p = new PingClient(args[0],Integer.parseInt(args[1]));
    }

    /**
     * application socket 
     */
	private DatagramSocket sock;
	
	private int port;
	
	private InetAddress addr;
	
	private Calendar[] pingtimes;
	
	public PingClient(String hostname, int port) {

       //initalize the class
	   this.port = port;
	   pingtimes = new Calendar[10];
	   
	   try{
	     addr = InetAddress.getByName(hostname);
	   }
	   catch (UnknownHostException uhe) {
	     System.err.println("Unknown Host "+hostname);
	     System.exit(4);
	   }  
	
	    try{
           sock = new DatagramSocket();
	       //sock.connect( new InetSocketAddress(hostname,port) ); 
        }
        catch(SocketException se) {
          //TODO: error reporting
          System.err.println("Error Connecting to host");
          System.exit(3);
        }
        
        Thread t = new Thread(this);
        t.start();
        
        while(true) {
           DatagramPacket p = new DatagramPacket(new byte[1024],1024);
           String line = "";
           try{
              sock.receive(p);
              line = (new BufferedReader(new InputStreamReader(new ByteArrayInputStream(p.getData())))).readLine();
           }
           catch(IOException e) {
             System.err.println("Error Reading from Socket");
             System.exit(6);
           }
           
           System.out.println(line);
        }
	}
	
	public void run() {
	
	  for(int i=0; i<10; i++) {
	   //get time
	   Calendar now = Calendar.getInstance();
	   pingtimes[i] = now;
	   
	   String sndstring = "PING " + i + " " + 
	     now.HOUR_OF_DAY +":"+now.MINUTE+":"+now.SECOND+"\r\n";
	
	   try{
	     byte[] buf = sndstring.getBytes();
	     DatagramPacket p = new DatagramPacket(buf, buf.length,addr,port);
	     sock.send(p);
	     Thread.sleep(1000);
	   }
	   catch(InterruptedException e) {
	   }
	   catch(IOException e) {
	     System.err.println("I/O Transmission Error");
	     System.exit(5);
	   }
      }
	}
}	
