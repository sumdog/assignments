import java.lang.Thread;
class MyThread implements Runnable 
{

  private Thread thread;
  
  MyThread()
  {
    thread = new Thread(this);
    thread.start();
  }
  
  public void run()
  {
    for(int i=0; i<3000; i++)
    { 
      System.out.println("Thread " + thread.toString() + " looping " + i);
    }
  }

  public Thread getThread() { return thread; }

  public static void main(String[]args) 
  {
    MyThread t1;
    MyThread t2;
    t1 = new MyThread();
    t2 = new MyThread();
    try 
    {
       t1.getThread().join();
       t2.getThread().join();
    }
    catch(Exception ex)
    {}
  }
}
