using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScanLogsForShanghai18
{
    class Program
    {
        static string szLogFile = "";

        static void Main(string[] args)
        {
            string szLogDir = AppDomain.CurrentDomain.BaseDirectory + "\\统计结果";

            if (!Directory.Exists(szLogDir))
            {
                Directory.CreateDirectory(szLogDir);
            }

            szLogFile = szLogDir + "\\" + DateTime.Now.ToString("yyyyMMdd_HHmmss") + ".log";

            if (args.Length != 0)
            {
                for (int i = 0; i < args.Length; i++)
                {
                    if (args[i].ToLower().Contains("localpath"))
                        szLogDir = AppDomain.CurrentDomain.BaseDirectory + args[i].Substring(args[i].IndexOf('=') + 1);
                    else if (args[i].Contains("fullpath"))
                        szLogDir = args[i].Substring(args[i].IndexOf('=') + 1);
                }
            }
            else
            {
                szLogDir = " D:\\项目资料\\弓网采集软件-04-上海地铁18号线\\日志\\230315-102\\";
          
            }

            Log(szLogDir);

            string szVideo = szLogDir + "视频软件";
            string szZipper = szLogDir + "缺陷软件";
            string szUploader = szLogDir + "上传软件";
            string szReceiver = szLogDir + "接收服务器";

            //Console.WriteLine("视频软件日志：" + szVideo);
            //Console.WriteLine("缺陷软件日志：" + szZipper);
            //Console.WriteLine("上传软件日志：" + szUploader);
            //Console.WriteLine("接收服务器日志：" + szReceiver);

            List<string> listVideoSendout = new List<string>();
            List<string> listVideoCmdRev = new List<string>();
            List<string> listVideoCmdSelf = new List<string>();
            List<string> listVideoDoneForZip = new List<string>();
            List<string> listVideoDoneForSelf = new List<string>();
            ScanVideoLog(szVideo, listVideoSendout, listVideoCmdRev, listVideoCmdSelf,listVideoDoneForZip, listVideoDoneForSelf);

            List<string> listRevFromVideo = new List<string>();
            List<string> listZip = new List<string>();
            ScanZipLog(szZipper, listRevFromVideo, listZip);

            JudgeVideoFiles(listVideoSendout, listRevFromVideo, listVideoCmdRev, listVideoCmdSelf,listVideoDoneForZip, listVideoDoneForSelf);

            List<string> listToUpload = new List<string>();
            List<string> listUploaded = new List<string>();
            ScanUploadLog(szUploader, listToUpload, listUploaded);

            JudgeZipFiles(listZip, listToUpload);

            JudgeUploadFiles(listToUpload, listUploaded);

            List<string> list2Down = new List<string>();
            List<string> listDownS = new List<string>();
            List<string> listDownF = new List<string>();

            ScanServerLog(szReceiver, list2Down, listDownS, listDownF);

            JudgeServerFiles(listUploaded, list2Down, listDownS);

            Console.ReadLine();
        }

        static void ScanVideoLog(string logdir, List<string> listvideosendout, List<string> listvideocmdrev, List<string> listvideocmdself, List<string> listvideodoneforzip, List<string> listvideodoneforself)
        {
            string szlog;
            if (!Directory.Exists(logdir))
            {
                szlog = "视频软件日志" + logdir + "不存在";
                Log(szlog);
                return;
            }

            string[] files = Directory.GetFiles(logdir);
            if (files.Count() == 0)
            {
                szlog = "视频软件日志" + logdir + "内没有文件";
                Log(szlog);
                return;
            }

            foreach (var file in files)
            {
                foreach (string line in System.IO.File.ReadLines(file, Encoding.GetEncoding("GB2312")))
                {
                    if (line.Contains("收到有效报警数据"))
                    {
                        int nfirstIdx = line.IndexOf("文件名：") + ("文件名：").Length;
                        int nLastIdx = line.IndexOf("远端路径：");
                        string path = line.Substring(nfirstIdx, nLastIdx - nfirstIdx).Trim();

                        if (!line.Contains("（"))
                        {
                            if (!listvideocmdrev.Contains(path))
                                listvideocmdrev.Add(path);
                        }
                        else
                        {
                            path = path + ".mp4";
                            if (!listvideocmdself.Contains(path))
                                listvideocmdself.Add(path);
                        }

                    }
                    else if (line.Contains("缺陷视频截取完毕："))
                    {
                        int nfirstZipIdx;
                        string path;

                        nfirstZipIdx = line.LastIndexOf("\\") + ("\\").Length;
                        path = line.Substring(nfirstZipIdx).Trim();

                        int nfirstSharpIdx = path.IndexOf("#");
                        path = path.Substring(0, nfirstSharpIdx);

                        if(!line.Contains("PantoDefect#1"))
                        {
                            if (!listvideodoneforself.Contains(path))
                                listvideodoneforself.Add(path);
                        }
                        else
                        {
                            if (!listvideodoneforzip.Contains(path))
                                listvideodoneforzip.Add(path);
                        }

                        if (!listvideosendout.Contains(path))
                            listvideosendout.Add(path);
                    }
                    else
                    {
                        continue;
                    }
                }
            }

        }

        static void ScanZipLog(string logdir, List<string> listrev, List<string> listzip)
        {
            string szlog;

            if (!Directory.Exists(logdir))
            {
                szlog = "缺陷软件日志" + logdir + "不存在";
                Log(szlog);
                return;
            }

            string[] files = Directory.GetFiles(logdir);
            if (files.Count() == 0)
            {
                szlog = "缺陷软件日志" + logdir + "内没有文件";
                Log(szlog);
                return;
            }

            foreach (var item in files)
            {
                foreach (string line in System.IO.File.ReadLines(item, Encoding.GetEncoding("GB2312")))
                {
                    if (line.Contains("pathTemp="))
                    {
                        int nfirstZipIdx = line.LastIndexOf("\\") + ("\\").Length;
                        string file = line.Substring(nfirstZipIdx).Trim();

                        //Console.WriteLine(file);
                        if (!listrev.Contains(file))
                            listrev.Add(file);
                    }
                    else if (line.Contains("zipFilePath="))
                    {
                        int nfirstZipIdx = line.IndexOf("Zip\\") + ("Zip\\").Length;
                        string file = line.Substring(nfirstZipIdx).Trim();

                        //Console.WriteLine(file);
                        if (!listzip.Contains(file))
                            listzip.Add(file);
                    }
                    else
                    {
                        continue;
                    }
                }
            }

        }

        static void JudgeVideoFiles(List<string> listvideosendout, List<string> listrevfromvideo,List<string> listvideocmdrev, List<string> listvideocmdself, List<string> listvideodoneforzip, List<string> listvideodoneforself)
        {
            string szlog;

            Log("-----------------------------------------------------------------------------");

            szlog = "视频软件收到了" + listvideocmdrev.Count() + "个来自缺陷软件截取视频的命令，成功截取了" + listvideodoneforzip.Count()+"个视频";
            Log(szlog);

            if(listvideocmdrev.Count()!= 0)
            {
                int count = 0;
                foreach (string file1 in listvideocmdrev)
                {
                    if (!listvideodoneforzip.Contains(file1))
                    {
                        if(count == 0)
                            Log("以下命令没有截取视频:");
                        count++;
                        Log(file1);
                    }
                }

                szlog = count + "个缺陷软件的截取视频的命令没有起效";
                Log(szlog);
            }

            szlog = "视频软件试图截取" + listvideocmdself.Count()+"视频,成功截取了"+listvideodoneforself.Count() + "个因为视频检测截取的视频";
            Log(szlog);

            if (listvideocmdself.Count() != 0)
            {
                int count = 0;
                foreach (string file1 in listvideocmdself)
                {
                    if (!listvideodoneforself.Contains(file1))
                    {
                        if (count == 0)
                            Log("以下命令没有截取视频:");
                        count++;
                        Log(file1);
                    }
                }

                szlog = count + "个视频软件的截取视频的命令没有起效";
                Log(szlog);
            }


            if (listvideosendout.Count() == 0)
            {
                Log("没有获取到视频软件截取的缺陷视频信息");
            }

            if (listrevfromvideo.Count() == 0)
            {
                Log("没有获取缺陷软件收到的缺陷视频信息");
            }

            if (listvideosendout.Count() == 0 || listrevfromvideo.Count() == 0)
            {
                return;
            }

            if (listvideosendout.Count() == listrevfromvideo.Count())
            {
                szlog = "所有" + listvideosendout.Count() + "个缺陷视频都送到了缺陷软件";
                Log(szlog);
            }
            //else if (listvideosendout.Count() < listrevfromvideo.Count())
            //{
            //    Log("缺陷软件中收到的缺陷视频比视频软件截取的视频多:");
            //    int count = 0;
            //    foreach (string file1 in listrevfromvideo)
            //    {
            //        if (!listvideosendout.Contains(file1))
            //        {
            //            count++;
            //            Log(file1);
            //        }
            //    }
            //    szlog = count + "个缺陷视频无法在视频软件日志中找到";
            //    Log(szlog);
            //}
            else
            {
                Log("以下缺陷视频没有送到缺陷软件:");
                int count = 0;
                foreach (string file1 in listvideosendout)
                {
                    if (!listrevfromvideo.Contains(file1))
                    {
                        count++;
                        Log(file1);
                    }
                }
                szlog = count + "个缺陷视频没有送到缺陷软件";
                Log(szlog);
            }
        }


        static void JudgeZipFiles(List<string> listzip, List<string> listoupload)
        {
            string szlog;

            Log("-----------------------------------------------------------------------------");

            if (listzip.Count() == 0)
            {
                Log("没有获取缺陷软件打包信息");
            }

            if (listoupload.Count() == 0)
            {
                Log("没有获取上传软件上传Zip包信息");
            }

            if (listzip.Count() == 0 || listoupload.Count() == 0)
            {
                return;
            }

            if (listzip.Count() == listoupload.Count())
            {
                szlog = "所有" + listzip.Count() + "个Zip都送到了上传软件";
                Log(szlog);
            }
            else if(listzip.Count() < listoupload.Count())
            {
                Log("上传软件中收到的Zip包比缺陷软件中的多:");
                int count = 0;
                foreach (string file1 in listoupload)
                {
                    if (!listzip.Contains(file1))
                    {
                        count++;
                        Log(file1);
                    }
                }
                szlog = count + "个zip在缺陷软件中没有找到";
                Log(szlog);
            }
            else
            {
                Log("以下文件没有送到上传软件:");
                int count = 0;
                foreach (string file1 in listzip)
                {
                    if (!listoupload.Contains(file1))
                    {
                        count++;
                        Log(file1);
                    }
                }
                szlog = count + "个zip没有送到上传软件";
                Log(szlog);
            }
        }

        static void ScanUploadLog(string logdir, List<string> listoupload, List<string> listouploaded)
        {
            string szlog;
            if (!Directory.Exists(logdir))
            {
                szlog = "上传软件日志" + logdir + "不存在";
                Log(szlog);
                return;
            }

            string[] files = Directory.GetFiles(logdir);
            if (files.Count() == 0)
            {
                szlog = "上传软件日志" + logdir + "内没有文件";
                Log(szlog);
                return;
            }

            foreach (var item in files)
            {
                foreach (string line in System.IO.File.ReadLines(item, Encoding.GetEncoding("GB2312")))
                {
                    if (line.Contains("FTP上传器收到任务"))
                    {
                        int nfirstZipIdx = line.IndexOf("Zip/") + ("Zip/").Length;
                        int nlastZipIdx = line.LastIndexOf("zip") + ("zip").Length;
                        string file = line.Substring(nfirstZipIdx, nlastZipIdx - nfirstZipIdx);

                        //Console.WriteLine(file);
                        if (!listoupload.Contains(file))
                            listoupload.Add(file);
                    }
                    else if (line.Contains("FTP上传成功 文件"))
                    {
                        int nfirstZipIdx = line.IndexOf("Zip/") + ("Zip/").Length;
                        int nlastZipIdx = line.LastIndexOf("zip") + ("zip").Length;
                        string file = line.Substring(nfirstZipIdx, nlastZipIdx - nfirstZipIdx);

                        //Console.WriteLine(file);
                        if (!listouploaded.Contains(file))
                            listouploaded.Add(file);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

        static void JudgeUploadFiles(List<string> listoupload, List<string> listouploaded)
        {
            string szlog;

            Log("-----------------------------------------------------------------------------");

            if (listoupload.Count() == 0)
            {
                Log("没有上传软件中找到需要上传zip信息");
            }

            if (listouploaded.Count() == 0)
            {
                Log("没有上传软件中找到成功上传zip信息");
            }

            if (listoupload.Count() == 0 || listouploaded.Count() == 0)
            {
                return;
            }


            if (listoupload.Count() == listouploaded.Count())
            {
                szlog = "所有" + listoupload.Count() + "个Zip都上传成功";
                Log(szlog);
            }
            else
            {
                Log("以下文件上传失败:");
                int count = 0;
                foreach (string file1 in listoupload)
                {
                    if (!listouploaded.Contains(file1))
                    {
                        szlog = file1 + "上传失败";
                        count++;
                        Log(file1);
                    }
                }
                szlog = count + "上传失败";
                Log(szlog);
            }
        }

        static void ScanServerLog(string logdir, List<string> listtodown, List<string> listdownf,List<string> listdowns)
        {
            string szlog;
            if (!Directory.Exists(logdir))
            {
                szlog = "接收服务器日志" + logdir + "不存在";
                Log(szlog);
                return;
            }

            string[] files = Directory.GetFiles(logdir);
            if (files.Count() == 0)
            {
                szlog = "接收服务器日志" + logdir + "内没有文件";
                Log(szlog);
                return;
            }

            foreach (var item in files)
            {
                foreach (string line in System.IO.File.ReadLines(item, Encoding.UTF8))
                {
                    if (line.Contains("下载SFTP文件"))
                    {
                        int nfirstZipIdx = line.LastIndexOf("/") + ("/").Length;
                        string file = line.Substring(nfirstZipIdx).Trim();

                        //Console.WriteLine(file);
                        if (!listtodown.Contains(file))
                            listtodown.Add(file);
                    }
                    else if (line.Contains("zip文件不存在"))
                    {
                        int nfirstZipIdx = line.LastIndexOf("/") + ("/").Length;
                        string file = line.Substring(nfirstZipIdx).Trim();

                        //Console.WriteLine(file);
                        if (!listdownf.Contains(file))
                            listdownf.Add(file);
                    }
                    else if (line.Contains("下载文件:"))
                    {
                        int nfirstZipIdx = line.LastIndexOf("/") + ("/").Length;
                        string file = line.Substring(nfirstZipIdx).Trim();

                        //Console.WriteLine(file);
                        if (!listdowns.Contains(file))
                            listdowns.Add(file);
                        if (listdownf.Contains(file))
                            listdownf.Remove(file);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

        static void JudgeServerFiles(List<string> listuploaded, List<string> listtodown, List<string> listtodowns)
        {
            string szlog;

            Log("-----------------------------------------------------------------------------");

            if (listuploaded.Count() == 0)
            {
                Log("没有上传软件上传成功zip包数据");
            }

            if (listtodown.Count() == 0)
            {
                Log("没有接收服务器需要下载zip包数据");
            }

            if (listuploaded.Count() == 0 || listtodown.Count() == 0)
            {
                return;
            }

            if (listuploaded.Count() == listtodown.Count())
            {
                szlog = "所有" + listuploaded.Count() + "个Zip都送到服务器";
                Log(szlog);
            }
            //else if(listuploaded.Count() < listtodown.Count())
            //{
            //    szlog = "需要下载的数据比成功上传的多：";
            //    Log(szlog);
            //    int count = 0;
            //    foreach (string file1 in listtodown)
            //    {
            //        if (!listuploaded.Contains(file1))
            //        {
            //            szlog = file1 + "上传失败";
            //            count++;
            //            Log(file1);
            //        }
            //    }
            //    szlog = count + "上传失败";
            //    Log(szlog);
            //}
            else
            {
                szlog = "下面zip没有送到服务器：";
                Log(szlog);
                int count = 0;
                foreach (string file1 in listuploaded)
                {
                    if (!listtodown.Contains(file1))
                    {
                        szlog = file1;
                        count++;
                        Log(file1);
                    }
                }
                szlog = count + "个zip没有送到";
                Log(szlog);

                szlog = "下面zip送到服务器：";
                Log(szlog);
                count = 0;
                foreach (string file1 in listuploaded)
                {
                    if (listtodown.Contains(file1))
                    {
                        szlog = file1;
                        count++;
                        Log(file1);
                    }
                }
                szlog = count + "个zip送到";
                Log(szlog);
            }

            if(listtodowns.Count() > 0)
            {
                szlog = listtodowns.Count() + "个zip下载失败";
                Log(szlog);
                foreach (string file1 in listtodowns)
                {
                   Log(file1);
                }
            }
        }

        static void Log(string logString,bool onlySave2File = false)
        {
            if(!onlySave2File)
                Console.WriteLine(logString);
            
            try
            {
                //var file = AppDomain.CurrentDomain.BaseDirectory + "\\" + DateTime.Now.ToString("yyyyMMdd_HHmmss") + ".log";
                var context = logString;

                var fs = new FileStream(szLogFile, FileMode.OpenOrCreate, FileAccess.Write);
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
