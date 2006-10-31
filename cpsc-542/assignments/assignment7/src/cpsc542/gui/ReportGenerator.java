package cpsc542.gui;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

import cpsc542.xml.TotalCreditData;

public class ReportGenerator extends JFrame {
	
	private JTable jt_data;
	
	private CreditDataTableModel datamodel;
	
	private JPanel p_primary;
	
	public ReportGenerator(TotalCreditData[] tcd) {
		
		p_primary = new JPanel();
		datamodel = new CreditDataTableModel(tcd);
		jt_data = new JTable(datamodel);
		p_primary.add(new JScrollPane(jt_data));
		
		getContentPane().add(p_primary);
		setSize(500,500);
		setTitle("Class Hours Report");
		setVisible(true);
		
		addWindowListener( new WindowAdapter() {
			
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
	}
}
