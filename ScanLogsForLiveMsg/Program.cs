using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScanLogsForLiveMsg
{
    class Program
    {
        static string reslut;

        static void Main(string[] args)
        {
            string logPath = AppDomain.CurrentDomain.BaseDirectory + "Log";

            string[] Files = Directory.GetFiles(logPath);

            foreach (var file in Files)
            {
                Log(file);
                ReadLogs(file);
            }

            Console.ReadLine();
        }

        static void ReadLogs(string path)
        {

            DateTime curDT = DateTime.MinValue;
            DateTime preDT = DateTime.MinValue;

            string curString = "", preString = "";

            // Read the file and display it line by line.  
            foreach (string line in System.IO.File.ReadLines(path, Encoding.GetEncoding("GB2312")))
            {
                if (!line.Contains("杭州机场线，发送数据到trdp转发器,生命信号"))
                    continue;

                if(curDT == DateTime.MinValue)
                {
                    curDT = GetDateTime(line);
                    curString = line;
                }
                else 
                {
                    preDT = curDT;
                    preString = curString;

                    curDT = GetDateTime(line);
                    curString = line;

                    TimeSpan ts = curDT - preDT;
                    if (ts.TotalMilliseconds > 1000)
                    {
                        Log(preString);
                        Log(curString);
                    }

                }
            }
        }

        static void Log(string logString)
        {
            Console.WriteLine(logString);
            try
            {
                var file = AppDomain.CurrentDomain.BaseDirectory + "\\" + DateTime.Now.ToString("yyyyMMdd_HH") + ".log";
                var context = logString;

                var fs = new FileStream(file, FileMode.OpenOrCreate, FileAccess.Write);
                var sw = new StreamWriter(fs);
                sw.BaseStream.Seek(0, SeekOrigin.End);
                sw.WriteLine(context);

                sw.Flush();
                sw.Close();
                fs.Close();
            }
            catch (Exception)
            {
                throw;
            }
        }


        static DateTime GetDateTime(string logString)
        {
            int len = logString.IndexOf(']') - logString.IndexOf('[')-1;
            return DateTime.ParseExact(logString.Substring(logString.IndexOf("") + 1, len), "yyyy-MM-dd HH:mm:ss.ffffff", System.Globalization.CultureInfo.CurrentCulture);
        }
    }
}
