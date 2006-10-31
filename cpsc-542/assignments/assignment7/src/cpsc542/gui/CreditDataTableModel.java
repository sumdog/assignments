package cpsc542.gui;

import javax.swing.table.AbstractTableModel;

import cpsc542.xml.TotalCreditData;

public class CreditDataTableModel extends AbstractTableModel {

	private TotalCreditData[] data;
	
	public CreditDataTableModel(TotalCreditData[] d) {
		data = d;
	}
	
	public int getColumnCount() {
		return 2;
	}

	public int getRowCount() {
		return data.length; 
	}

	public Object getValueAt(int x, int y) {
		switch(y) {
		  case 0:
			  return data[x].getCourse();
		  case 1:
			  return data[x].getTotal();
		  default:
			  return "";
		}
	}
    
    public String getColumnName(int col) {
        switch(col) {
        case 0:
        	return "Course";
        	case 1:
        	return "Total Hours";
        	default:
        	return "";
        }
    }
	
	public boolean isCellEditable(int row, int col)
    { return false; }
}
