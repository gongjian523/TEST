using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Configuration;

namespace TestTCPClientCS
{
    class Program
    {
        private static readonly object obj = new object();

        /// <summary>
        /// 是否继续连接了
        /// </summary>
        static bool isContinueConnect = false;
        static TcpClient tcpClient;
        static System.Timers.Timer timerReconnect;
        static System.Timers.Timer timerSendMsg;


        static AsyncTcpClient client;

        static Action action = null;
        static Action continueConnect = null;

        static bool isExit = false;

        static string addr;
        static int port;

        static void Main(string[] args)
        {
            var appSettings = ConfigurationManager.AppSettings;

            addr = appSettings["Address"] ?? "Not Found";

            port = Int16.Parse(appSettings["Port"]);


            int interval = 1000*10;
            timerReconnect = new System.Timers.Timer(1000*10);
            timerReconnect.Elapsed += new System.Timers.ElapsedEventHandler(onTimerReconnect);

            timerSendMsg = new System.Timers.Timer(1000);
            timerSendMsg.AutoReset = true;
            timerSendMsg.Elapsed += new System.Timers.ElapsedEventHandler(onTimerSendMsg);

            client = AsyncTcpClient.Instance;
            client.ConnectServer(addr, port);
            client.ErrorOccuredHandler += new AsyncTcpClient.ErrorOccuredDelegate(onReconnet);
            client.ConnectSucceedHandler += new AsyncTcpClient.ConnectSucceedDelegate(onConnectSucceed);

            //continueConnect = () =>
            //{
            //    timerReconnect.Stop();
            //    lock (obj)
            //    {
            //        if (!isContinueConnect)
            //        {
            //            isContinueConnect = true;
            //            action();
            //        }
            //    }
            //};

            //action = () =>
            //{
            //    if (tcpClient != null)
            //        tcpClient.Dispose();

            //    tcpClient = new TcpClient();

            //    tcpClient.BeginConnect(IPAddress.Parse("127.0.0.1"), 9866, a =>
            //    {
            //        //TcpClient tcpClient = null;
            //        try
            //        {
            //            tcpClient = (TcpClient)a.AsyncState;
            //            tcpClient.EndConnect(a);
            //            WriteLogs("连接服务器成功");
            //            isContinueConnect = false;
            //            timerReconnect.Start(); 

            //            NetworkStream networkStream = tcpClient.GetStream();

            //            Task t1 = Task.Run(async () =>
            //            {
            //                while (true)
            //                {
            //                    try
            //                    {
            //                        if (!networkStream.CanWrite)
            //                        {
            //                            continue;
            //                        }
            //                        //发送消息到服务器
            //                        string input = "武松去九岭岗" + DateTime.Now.ToLongTimeString();
            //                        WriteLogs("发送到服务器:" + input);
            //                        ReadOnlyMemory<byte> buffer = Encoding.Unicode.GetBytes(input).AsMemory();
            //                        await networkStream.WriteAsync(buffer);
            //                        await networkStream.FlushAsync();

            //                        Thread.Sleep(2000);
            //                    }
            //                    catch (Exception ex)
            //                    {
            //                        WriteLogs("连接服务器异常" + ex.Message);
            //                        if (timerReconnect.Enabled)
            //                            continueConnect();
            //                        break;
            //                    }
            //                }
            //            });

            Task t2 = Task.Run(async () =>
            {
                while (true)
                {
                    try
                    {
                        if (!networkStream.CanRead)
                        {
                            continue;
                        }
                                    //收到服务器消息
                                    List<byte> list = new List<byte>();
                        do
                        {
                            Memory<byte> buffer3 = new byte[200];
                            await networkStream.ReadAsync(buffer3);
                            list.AddRange(buffer3.ToArray());
                        } while (networkStream.DataAvailable);
                        string msg = Encoding.Unicode.GetString(list.ToArray());
                        msg = msg.TrimEnd('\0', '\r', '\n');
                        WriteLogs("收到服务器消息：" + msg);
                    }
                    catch (Exception ex)
                    {
                        WriteLogs("连接服务器异常" + ex.Message);
                        if (timerReconnect.Enabled)
                            continueConnect();
                        break;
                    }
                }
            });
            //        }
            //        catch (Exception ex)
            //        {

            //            WriteLogs(ex.Message + ",10秒后重新连接");
            //            Thread.Sleep(10000);
            //            action();
            //        }
            //    }, tcpClient);
            //};

            //action();

            while (!isExit)
            {
                Thread.Sleep(1000 * 60);
            }

            //Console.ReadKey();
        }
        static  private void onTimerReconnect(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                timerReconnect.Stop();
                client.ConnectServer(addr, port);
            }
            catch (Exception ex)
            {
                isExit = true;
            }
        }

        static int count = 0;

        static private void onTimerSendMsg(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                if(client.IsConnected())
                {
                    if(count<10)
                    {
                        string input = "武松去九岭岗" + DateTime.Now.ToLongTimeString();
                        Log.WriteLogs("发送到服务器:" + input);
                        client.SendMsg(input);
                        count++;
                    }
                    else
                    {
                        client.Close();
                        onReconnet("");
                    }
                }
                else
                {
                    onReconnet("");
                }

            }
            catch (Exception ex)
            {
                isExit = true;
            }
        }


        static private void onReconnet(string error)
        {
            if(error != "")
                Log.WriteLogs(error);

            if (!timerReconnect.Enabled)
                timerReconnect.Start();
            timerSendMsg.Stop();

            count = 0;

        }

        static private void onConnectSucceed()
        {
            timerSendMsg.Start();
        }

    }
}
