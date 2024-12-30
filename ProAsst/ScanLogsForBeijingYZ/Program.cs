using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScanLogsForBeijingYZ
{
    class Program
    {
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
            // Read the file and display it line by line.  
            foreach (string line in System.IO.File.ReadLines(path, Encoding.GetEncoding("GB2312")))
            {
                if (!line.Contains("收到PIS应答："))
                    continue;

                string dt = GetDateTime(line);

                string data = GetData(line);

                string info = Parse(data);

                string log = dt + " " + data + " " + info;

                Log(log);
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

        static string Parse(string logString)
        {
            string log = logString;
            log.TrimStart();
            log.TrimEnd(' ');

            string[] datas = log.Split(' ');

            if (datas.Count() != 13)
                return "";

            int nDirection = Int32.Parse(datas[3]);
            int nKM = String2Int(datas[5], datas[4]);

            string szDirection, szStation;

            if (nDirection == 0)
            {
                szDirection = "未知 ";
                szStation = "";
            }
            else if(nDirection == 1)
            {
                szDirection = "上行 ";

                szStation = GetStation(nKM,true) + " ";
            }
            else if (nDirection == 2)
            {
                szDirection = "下行 ";
                szStation = GetStation(nKM,false) + " ";
            }
            else
            {
                szDirection = "其他 ";
                szStation = "";
            }

            int nSpeed = String2Int(datas[7],datas[6]);

            return szDirection + nKM.ToString() + " " + szStation + nSpeed.ToString();
        }

        static string GetData(string logString)
        {
            return logString.Substring(logString.LastIndexOf("：")+1);
        }

        static string GetDateTime(string logString)
        {
            int len = logString.IndexOf(']') - logString.IndexOf('[') + 1;
            return logString.Substring(logString.IndexOf(""), len);
        }

        static int String2Int(string high, string low)
        {
            int nIntHight = Int32.Parse(high,System.Globalization.NumberStyles.HexNumber);
            int nIntLow = Int32.Parse(low, System.Globalization.NumberStyles.HexNumber);

            return nIntHight * 256 + nIntLow;
        }

        static string GetStation(int km, bool bUP)
        {
            if(km <= 496)
            {
                return "老观里站";
            }
            else if(km <= 1394)
            {
                if(bUP)
                    return "老观里站 - 屈庄站";
                else
                    return "屈庄站 - 老观里站";
            }
            else if (km <= 1414)
            {
                return "屈庄站";
            }
            else if (km <= 2156)
            {
                if (bUP)
                    return "屈庄站 - 融兴街站";
                else
                    return "融兴街站 - 屈庄站";
            }
            else if (km <= 2196)
            {
                return "融兴街站";
            }
            else if (km <= 2957)
            {
                if (bUP)
                    return "融兴街站 - 瑞合庄站";
                else
                    return "瑞合庄站 - 融兴街站";
            }
            else if (km <= 2997)
            {
                return "瑞合庄站";
            }
            else if (km <= 4248)
            {
                if (bUP)
                    return "瑞合庄站 - 太和桥北站";
                else
                    return "太和桥北站 - 瑞合庄站";
            }
            else if (km <= 4288)
            {
                return "太和桥北站";
            }
            else if (km <= 4887)
            {
                if (bUP)
                    return "太和桥北站 - 四海庄站";
                else
                    return "四海庄站 - 太和桥北站";

            }
            else if (km <= 4927)
            {
                return "四海庄站";
            }
            else if (km <= 5881)
            {
                if (bUP)
                    return "四海庄站 - 九号村站";
                else
                    return "九号村站 - 四海庄站";
            }
            else if (km <= 5921)
            {
                return "九号村站";
            }
            else if (km <= 6487)
            {
                if (bUP)
                    return "九号村站 - 泰和路站";
                else
                    return "泰和路站 - 九号村站";
            }
            else if (km <= 6527)
            {
                return "泰和路站";
            }
            else if (km <= 7226)
            {
                if (bUP)
                    return "泰和路站 - 鹿泉东站";
                else
                    return "鹿泉东站 - 泰和路站";
            }
            else if (km <= 7266)
            {
                return "鹿泉东站";
            }
            else if (km <= 8454)
            {
                if (bUP)
                    return "鹿泉东站 - 亦庄同仁站";
                else
                    return "亦庄同仁站 - 鹿泉东站";
            }
            else if (km <= 8494)
            {
                return "亦庄同仁站";
            }
            else if (km <= 9059)
            {
                if (bUP)
                    return "亦庄同仁站 - 荣昌东街站";
                else
                    return "荣昌东街站 - 亦庄同仁站";
            }
            else if (km <= 9099)
            {
                return "荣昌东街站";
            }
            else if (km <= 9667)
            {
                if (bUP)
                    return "荣昌东街站 - 亦创会展中心站";
                else
                    return "亦创会展中心站 - 荣昌东街站";
            }
            else if (km <= 9707)
            {
                return "亦创会展中心站";
            }
            else if (km <= 11036)
            {
                if (bUP)
                    return "亦创会展中心站 - 经海一路站";
                else
                    return "经海一路站 - 亦创会展中心站";
            }
            else if (km <= 11076)
            {
                return "经海一路站";
            }
            else if (km <= 12207)
            {
                if (bUP)
                    return "经海一路站 - 定海园西站";
                else
                    return "定海园西站 - 经海一路站";
            }
            else if (km <= 12247)
            {
                return "定海园西站";
            }
            else if (km <= 13175)
            {
                if (bUP)
                    return "定海园西站 - 定海园站";
                else
                    return "定海园站 - 定海园西站";
            }
            else
            {
                return "定海园站";
            }
        }
    }
}
