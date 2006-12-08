import java.io.IOException;

import org.apache.xmlrpc.WebServer;

public class ChannelGuideXMLRPCServer {

	
	public static void main(String[] args) {
		
		int port = 0;
		try{
		  port = (args.length >= 1) ? Integer.parseInt(args[0]) : 8080;
		}
		catch(NumberFormatException e) {
			printUsage();
			System.exit(2);
		}
		
		WebServer server = new WebServer(port);  
		server.start();
		server.addHandler("ChannelGuide", new ChannelGuideHandler());
		System.out.println("Server is running on port " + port);

		while(true) {
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				System.exit(0);
			}
		}
	}
	
	public static void printUsage() {
		System.err.println("\nUsage: java -ChannelGuideServer <port>\n");
	}
	
}
