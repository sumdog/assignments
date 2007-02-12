import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JFrame;

public class HelloWorld extends JPanel {


   public HelloWorld() {
     super();
     add(new JLabel("Hello World"));
   }

   public static void main(String[] args) {
     JFrame s = new JFrame();
     s.setSize(200,200);
     s.getContentPane().add(new HelloWorld());
     s.setVisible(true);
   }

}
