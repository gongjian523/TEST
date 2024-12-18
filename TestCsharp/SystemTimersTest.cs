using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCsharp
{
    class SystemTimersTest
    {
        static private System.Timers.Timer timer1;
        
        static private System.Timers.Timer timer2;

        static public void Test()
        {
            timer1 = new System.Timers.Timer(1000 * 5);
            timer1.AutoReset = true;
            timer1.Enabled = true;
            timer1.Elapsed += timer1_Elapsed;

            timer2 = new System.Timers.Timer(1000 * 10);
            timer2.AutoReset = false;
            timer2.Elapsed += timer2_Elapsed;

            timer1.Start();
            timer2.Start();

            if (timer1.Enabled)
            {
                Console.WriteLine("timer1 is eanbled");
                timer1.Stop();
            }
            else
            {
                Console.WriteLine("timer1 is ont  eanbled");
            }

            Console.WriteLine(";;;;;;;");

            if (timer1.Enabled)
            {
                Console.WriteLine("timer1 is eanbled");
            }
            else
            {
                Console.WriteLine("timer1 is ont  eanbled");
            }
        }

        static private void timer1_Elapsed(object sender, System.Timers.ElapsedEventArgs e) 
        {
            Console.WriteLine("timer1_Elapsed");
        }

        static private void timer2_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            Console.WriteLine("timer2_Elapsed");
        }
    }
}
