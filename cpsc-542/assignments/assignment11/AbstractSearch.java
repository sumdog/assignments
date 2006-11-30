import java.io.File;


public abstract class AbstractSearch {

	protected File xmlfile;
	
	protected String query; 
	
	public AbstractSearch(File f, String q) {
		xmlfile = f;
		query = q;
	}
	
	public abstract void processSearch();
}
