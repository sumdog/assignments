
/**
 * 
 * Modified from original version for Sumllin's cpsc-251 class
 *  by Sumit Khanna
 *  
 *  Note: this program is dependent on having the "fortune" program
 *  installed and in the host enviroment's path.
 * 
 * Fortune server listening to port 6013.
 *
 * Figure 3.19
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Seventh Edition
 * Copyright John Wiley & Sons - 2005.
 */
 
import java.net.*;
import java.io.*;

public class ThreadedFortuneServer extends Thread
{
	
	/* added thread implementation */
	private Socket client;
	public ThreadedFortuneServer(Socket s) {
		client = s;
	}
	public void run() {
		try {
		  PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
		  // write the Date to the socket
		  pout.println(getFortune());

		  // close the socket and resume listening for more connections
		  client.close();
		}
		catch(IOException e) {
		  System.err.println("I/O Error with Client");	  
		}
	}
	/* end thread implementation */
	
	/*
	 * this function calls the system's "fortune" command and returns the output
	 */
	public static String getFortune() {
		BufferedReader in;
		String retval = "", s;
		try {
			Process p = Runtime.getRuntime().exec("fortune");
			in = new BufferedReader(new 
	                 InputStreamReader(p.getInputStream()));

			while((s = in.readLine()) != null) {
				retval = retval + s + "\n";
			}
			return retval;
		} catch (IOException e) {
			System.err.println("Broken Pipe");
			System.exit(3);
		}
		return null;
	}
	
	public static void main(String[] args)  {
		try {
			ServerSocket sock = new ServerSocket(6013);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				// start thread
		        new ThreadedFortuneServer(client).start();		

			}
		}
		catch (IOException ioe) {
				System.err.println("Error creating Server Socket");
		}
	}
}
