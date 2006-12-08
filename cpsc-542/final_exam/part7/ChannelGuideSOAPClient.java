import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Date;

import org.apache.axis.client.Call;
import org.apache.axis.client.Service;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.xml.namespace.QName;

public class ChannelGuideSOAPClient {

	
	public static void main(String[] args) {
		JClient clientwindow = new JClient();
	
	}
	
	public static String[][] makeRequest(String host, int hour) {
		String endpoint = host;
		
		try{
			Service service = new Service();
			Call call = (Call) service.createCall();
			
			call.setTargetEndpointAddress( new java.net.URL(endpoint));
			call.setOperationName(new QName("http://localhost/axis","hexCast"));
		
			String[][] ret = (String[][]) call.invoke( new Object[] { hour } );
			return ret;

		}
		catch(Exception e) {
		    System.err.println(e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

}

class JClient extends JFrame implements ActionListener {
	
	private JTextField tb_server;
	private JTextField tb_hour;
	private JTextArea ta_output;
	private JButton b_request;
	
	public JClient() {
	
		b_request = new JButton("Send Request");
		tb_server = new JTextField("http://localhost:8080/axis/services/ChannelGuideSOAP");
		tb_hour = new JTextField("21");
		ta_output = new JTextArea();
		
		JPanel jp_top = new JPanel();
		jp_top.setLayout(new GridLayout(0,1));
		jp_top.add(new JLabel("Web Service Endpoint:"));
		jp_top.add(tb_server);
		jp_top.add(new JLabel("Hour: "));
		jp_top.add(tb_hour);
		
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(jp_top,BorderLayout.NORTH);
		getContentPane().add(ta_output,BorderLayout.CENTER);
		getContentPane().add(b_request,BorderLayout.SOUTH);
	
		b_request.addActionListener(this);
		
		setSize(640,480);
		
		Dimension dim = getToolkit().getScreenSize();
		Rectangle abounds = getBounds();
		setLocation((dim.width - abounds.width) / 2,
		  (dim.height - abounds.height) / 2);
		
		setVisible(true);
		setTitle("ChannelGuide SOAP Client");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private void setInfo(String[][] s) {

		String out = "";
		for(int i=0;i<s.length; i++ ) {
			out = out + "Show: " + s[i][4] + "\n";
			out = out + "Channel: " + s[i][0] + " (" + s[i][1] + ")" + "\n";
			out = out + "Show Time: " + s[i][2] +" - "+ s[i][3] + "\n" ;
			out = out + "Genre : " + s[i][5] + "\n";
			out = out + "Staring: " + s[i][7] + "\n\n";
		}
		ta_output.setText(out);
	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == b_request) {
			try {
			  setInfo(ChannelGuideSOAPClient.makeRequest(tb_server.getText(), Integer.parseInt(tb_hour.getText())));
			}
			catch(NumberFormatException e1) {
				JOptionPane.showMessageDialog(new JFrame(),"Invalid Hour","Error",JOptionPane.ERROR_MESSAGE);
			}
		}
	}
}






