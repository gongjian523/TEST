using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScanLogsWithTemprature
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
                generateNewLog(file);
            }

            Console.ReadLine();
        }

        static void generateNewLog(string path)
        {
            string newpath = path.Insert(path.Length - 4, ".new");

            foreach (string line in System.IO.File.ReadLines(path, Encoding.GetEncoding("GB2312")))
            {
                if (line.Contains("杭州机场线，发送数据到trdp转发器,生命信号"))
                    continue;

                WriteTxt(line, newpath);
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
