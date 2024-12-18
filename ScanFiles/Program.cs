using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScanFiles
{
    class Program
    {
        static string logPath;

        static void Main(string[] args)
        {
            logPath = AppDomain.CurrentDomain.BaseDirectory + "\\Log";

            if (!Directory.Exists(logPath))
                Directory.CreateDirectory(logPath);

            string stDataPath = "d:\\cdtydata\\RailsideData";

            if (!Directory.Exists(stDataPath))
            {
                Log(stDataPath + "不存在");
            }

            string[] Dirs = Directory.GetDirectories(stDataPath);

            foreach (var dir in Dirs)
            {
                if (!Directory.Exists(dir))
                    continue;

                string fileName = Path.GetFileNameWithoutExtension(dir);

                //try
                //{
                //    DateTime.Parse(fileName);
                //}
                //catch
                //{
                //    continue;
                //}

                string[] SubDirs = Directory.GetDirectories(dir);

                foreach (var dateDir in SubDirs)
                {
                    if (!Directory.Exists(dateDir))
                        continue;

                    string subfileName = Path.GetFileNameWithoutExtension(dateDir);

                    Log("#################################");

                    ScanLD(dateDir);

                    Scan360(dateDir);
                }
            }

            Console.ReadLine();
        }


        static void ScanLD(string path)
        {
            string[] fullpaths = new string[2];
            fullpaths[0] = path + "\\TrainBody360\\CameraXZ\\TX360000";
            fullpaths[1] = path + "\\TrainBody360\\CameraXZ\\TX360001";

            foreach (var fullpath in fullpaths)
            {
                if (!Directory.Exists(fullpath))
                {
                    Log(fullpath + "不存在");
                    continue;
                }
                else
                {
                    DirectoryInfo info = new DirectoryInfo(fullpath);
                    Log(fullpath + "下有" + info.GetFiles("*.jpg").Length.ToString() + "个jpg," + info.GetFiles("*.json").Length.ToString() + "个json");

                }
            }
        }

        static void Scan360(string path)
        {
            string fullpath = path + "\\WheelTreads";

            if (!Directory.Exists(fullpath))
            {
                Log(fullpath + "不存在");
                return;
            }

            DirectoryInfo info = new DirectoryInfo(fullpath);

            for (int i = 1; i < 7; i++)
            {
                string subFullPath = fullpath + "\\" + i.ToString();

                if (!Directory.Exists(subFullPath))
                {
                    Log(subFullPath + "不存在");
                    continue;
                }

                DirectoryInfo subinfo = new DirectoryInfo(subFullPath);

                int jpgCnt = subinfo.GetFiles("*.jpg").Length;

                Log(subinfo + "下有" + jpgCnt.ToString() + "个jpg");

                if (jpgCnt != 32)
                {
                    for (int j = 1; j < 9; j++)
                    {
                        for (int k = 1; k < 5; k++)
                        {
                            string pic = subFullPath + "\\" + i.ToString() + "_" + j.ToString() + "_" + k.ToString() + ".jpg";

                            if (!File.Exists(pic))
                                Log(pic + "不存在");
                        }
                    }
                }
            }

            if (info.GetFiles("*.json").Length != 4)
            {
                for (int i = 1; i < 5; i++)
                {
                    string json = fullpath + "\\defects_" + i.ToString() + ".json";

                    if (!File.Exists(json))
                        Log(json + "不存在");
                }
            }
        }

        static void Log(string logString)
        {
            Console.WriteLine(logString);
            try
            {
                var file = logPath + "\\" + DateTime.Now.ToString("yyyyMMdd_HH") + ".log";
                var context = DateTime.Now + " " + logString;

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
    }
}
