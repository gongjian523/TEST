using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestTCPClientCS
{
    class Log
    {
        static public void WriteLogs(string log)
        {
            string path = AppDomain.CurrentDomain.BaseDirectory + "\\Log";

            Console.WriteLine(log);

            if (!Directory.Exists(path))
                Directory.CreateDirectory(path);

            try
            {
                var file = path + "\\" + DateTime.Now.ToString("yyyyMMdd_HH") + ".log";
                var context = log + DateTime.Now + "\n";

                var fs = new FileStream(file, FileMode.OpenOrCreate, FileAccess.Write);
                var sw = new StreamWriter(fs);
                sw.BaseStream.Seek(0, SeekOrigin.End);
                sw.WriteLine(context);

                sw.Flush();
                sw.Close();
                fs.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine("WriteLogs:" + ex.ToString());
            }
        }
    }
}
