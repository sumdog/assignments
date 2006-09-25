import java.io.*;
import java.net.*;
import java.util.Calendar;
import java.text.DecimalFormat;
import java.text.NumberFormat;

public class PingClient implements Runnable {

    /**
     * program entry point.
     */
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
	
	/**
	 * port to send and recieve pings on 
	 */
	private int port;
	
	/**
	 * Internet address representation of hostname
	 */
	private InetAddress addr;
	
	/**
	 * Record of sending times to calculuate delay
	 */
	private Calendar[] pingtimes;
	
	
	/*
	 * Stores stats
	 */
	private long min, max, average, transmitted, recieved;
	
	/**
	 * creates an object to ping a <code>PingServer</code> ten times.
	 *@param hostname network name or IP of server to ping
	 *@param port port to send requests and listen for replies on
	 */
	public PingClient(String hostname, int port) {

       //initalize the class
	   this.port = port;
	   pingtimes = new Calendar[10];
	   recieved = 0;
	   transmitted = 0;
	   min = Long.MAX_VALUE;
	   max = 0;
	   average = 0;
	   
	   //determine hostname
	   try{
	     addr = InetAddress.getByName(hostname);
	   }
	   catch (UnknownHostException uhe) {
	     System.err.println("Unknown Host "+hostname);
	     System.exit(4);
	   }  
	
	    try{
           sock = new DatagramSocket();
        }
        catch(SocketException se) {
          System.err.println("Error Creating Socket");
          System.exit(3);
        }
        
        //start our ping
        Thread t = new Thread(this);
        t.start();
        
        //wait for replies
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
           
           //calculate the ms delay
           long diff = Calendar.getInstance().getTimeInMillis() - pingtimes[ Integer.parseInt(line.split(" ")[1]) ].getTimeInMillis();
           int seq = Integer.parseInt(line.split(" ")[1]);
           recieved++;
           if(diff > max) { max = diff; }
           if(diff < min) { min = diff; }
           average = average + diff;
           String output = "Recieved Reply From: " + p.getAddress().getHostAddress() +" Seq: " + seq + " Time: " + diff+"ms";
           System.out.println(output);
        }
	}
	
	/**
	 * Outputs ping stats and then exits program.
	 */
	public void outputStats() {
	   
	   DecimalFormat df = (DecimalFormat) NumberFormat.getInstance();
	   df.applyPattern("##.##");
	   double per = (1.0 - ((double) recieved / (double) transmitted)) * 100;
	   System.out.println(transmitted + " Packets Transmitted, " + recieved + " packets recieved, " + df.format(per) + "% packet loss");
	   System.out.println("RTT min=" + min + "ms avg=" + average / transmitted + "ms max=" + max + "ms");
       System.exit(0);
	}
	
	public void run() {
	
	  for(int i=0; i<10; i++) {
	   //get time
	   Calendar now = Calendar.getInstance();
	   pingtimes[i] = now;
	   
	   //establish string to send
	   String sndstring = "PING " + i + " " + 
	     now.get(now.HOUR_OF_DAY) +":"+now.get(now.MINUTE)
	     +":"+now.get(now.SECOND)+"\r\n";
	
	   //send at one second intervals
	   try{
	     byte[] buf = sndstring.getBytes();
	     DatagramPacket p = new DatagramPacket(buf, buf.length,addr,port);
	     sock.send(p);
	     transmitted++;
	     Thread.sleep(1000);
	   }
	   catch(InterruptedException e) {
	   }
	   catch(IOException e) {
	     System.err.println("I/O Transmission Error");
	     System.exit(5);
	   }
      }
      
      //after we're done sending, wait two seconds
      // and then calculate the results
      // *assume remaining packets are lost
      //  after 2 second wait
      try{ Thread.sleep(2000); }
      catch(InterruptedException e) {};
      outputStats();
	}
}	
