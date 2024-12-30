using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScanLogsDelete
{
    class Program
    {

        static void Main(string[] args)
        {
            string logPath = AppDomain.CurrentDomain.BaseDirectory + "Log";

            string[] Files = Directory.GetFiles(logPath);

            foreach (var file in Files)
            {
                generateNewLog(file);
            }

            Console.ReadLine();
        }

        static void generateNewLog(string path)
        {
            Console.WriteLine(path);

            string name = path.Substring(path.LastIndexOf('\\'));

            string newpath = AppDomain.CurrentDomain.BaseDirectory + "NewLog\\" + name;

            string logPath2 = AppDomain.CurrentDomain.BaseDirectory + "NewLog\\LOG.txt";

            foreach (string line in System.IO.File.ReadLines(path, Encoding.GetEncoding("GB2312")))
            {
                if (line.Contains("最高温度"))
                    continue;

                WriteTxt(line, newpath);
                WriteTxt(line, logPath2);
            }
        }


        private static bool WriteTxt(string log, string filepath)
        {
            try
            {
                string folder = filepath.Substring(0, filepath.LastIndexOf('\\'));
                // 创建目录
                if (Directory.Exists(folder) == false)
                {
                    Directory.CreateDirectory(folder);
                }
                // 当文件不存在时创建文件
                if (File.Exists(filepath) == false)
                {
                    FileStream fs = File.Create(filepath);
                    fs.Close();
                }
                // 写入文件内容
                File.AppendAllText(filepath, log + "\r\n",  Encoding.Default);
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}


