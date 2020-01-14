using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//using System.Windows.Forms;

namespace MonoTK
{
  // The class that handles the creation of the application windows
//  class MyApplicationContext : ApplicationContext
//  {
//    private MyApplicationContext()
//    {

//    }
//  }

  public class MainForm
  {
    public MainForm()
    {

    }
public void exec(){
      Console.WriteLine("Hello World!");
      Console.ReadKey();
      //string c = Convert.ToChar();
      // Console.WriteLine("You typed: " + c + " type another key to exit.");
      //c = Convert.ToChar(Console.ReadKey());
    }
  }
  public static class Program
  {
    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    //[STAThread] //Reuuired to communicate with COM, we're not using COM with Mono so this isn't necessary
    static void Main(string[] args)
    {
      MainForm mf = new MainForm();
      mf.exec();
     // Application.EnableVisualStyles();
    //  Application.SetCompatibleTextRenderingDefault(false);
    //  Application.Run(new MainForm());
    }
  }

}



