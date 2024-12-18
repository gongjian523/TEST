using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Generate5CRecFiles
{
    class Program
    {

        static void CreateFiles(string path, bool bUp)
        {
            string[] Dirs = Directory.GetDirectories(path);

            foreach (var dir in Dirs)
            {
                if (!Directory.Exists(dir))
                    continue;

                Console.WriteLine(dir);

                string szDate = Path.GetFileName(dir);

                string[] SubDirs = Directory.GetDirectories(dir);

                foreach (var subDir in SubDirs)
                {
                    if (!Directory.Exists(subDir))
                        continue;

                    string szTime = Path.GetFileName(subDir);
                    szTime = szTime.Substring(0, szTime.IndexOf('_'));

                    string szDstPath = AppDomain.CurrentDomain.BaseDirectory + "图像识别\\等待识别\\";
                    string szFilePath = szDstPath + szDate + " " + szTime + (bUp ? "_上.txt" : "_下.txt");

                    if (File.Exists(szFilePath))
                        File.Delete(szFilePath);

                    if (!File.Exists(szFilePath))
                    {
                        // 创建一个要写入的文件。
                        string[] createText = new string[1];

                        byte[] bytes = Encoding.GetEncoding("gb2312").GetBytes(subDir);


                        
                        File.WriteAllBytes(szFilePath, bytes);
                    }
                }

            }
        }


        static void Main(string[] args)
        {
            string szScrPathUP = AppDomain.CurrentDomain.BaseDirectory + "picture\\Cache\\上行";
            string szScrPathDW = AppDomain.CurrentDomain.BaseDirectory + "picture\\Cache\\下行";

            if(Directory.Exists(szScrPathUP))
                CreateFiles(szScrPathUP, true);
            if (Directory.Exists(szScrPathDW))
                CreateFiles(szScrPathDW, false);

            Console.ReadLine();
        }
    }
}
