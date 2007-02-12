import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JFrame;
import javax.swing.JApplet;

public class HelloWorldApplet extends JApplet {

   public void init() {
      add(new HelloWorldPanel());
   }

}

class HelloWorldPanel extends JPanel {


   public HelloWorldPanel() {
     super();
     add(new JLabel("Hello World"));
   }

}
