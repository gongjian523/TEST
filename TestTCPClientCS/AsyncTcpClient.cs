using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace TestTCPClientCS
{
    class AsyncTcpClient
    {

        public delegate void ErrorOccuredDelegate(string errString); //定义一个委托
        public ErrorOccuredDelegate ErrorOccuredHandler;

        public delegate void ConnectSucceedDelegate(); //定义一个委托
        public ConnectSucceedDelegate ConnectSucceedHandler;

        private string ip1;
        private int port1;
        byte[] ReadBytes = new byte[1024 * 1024];
        //单例
        public static AsyncTcpClient Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new AsyncTcpClient();
                }
                return instance;
            }
        }
        private static AsyncTcpClient instance;

        System.Net.Sockets.TcpClient tcpClient;

        //连接服务器
        public void ConnectServer(string ip, int port)//填写服务端IP与端口
        {
            //Debuger.EnableSave = true;
            ip1 = ip;
            port1 = port;
            try
            {
                tcpClient = new System.Net.Sockets.TcpClient();//构造Socket
                tcpClient.BeginConnect(IPAddress.Parse(ip), port, ConnectCallBack, null);//开始异步
            }
            catch (Exception e)
            {
                ErrorOccuredHandler("ConnectServer:" + e.Message);
            }
        }

        //连接判断
        void ConnectCallBack(IAsyncResult ar)
        {
            if (!tcpClient.Connected)
            {
                ErrorOccuredHandler("ConnectCallBack:连接服务器失败");
            }
            else
            {
                tcpClient.EndConnect(ar);//结束异步连接
                tcpClient.GetStream().BeginRead(ReadBytes, 0, ReadBytes.Length, ReceiveCallBack, null);

                ConnectSucceedHandler();
            }
        }


        //接收消息
        void ReceiveCallBack(IAsyncResult ar)
        {
            if (!IsConnected())
                return;

            try
            {
                int len = tcpClient.GetStream().EndRead(ar);//结束异步读取
                if (len > 0)
                {
                    string str = Encoding.UTF8.GetString(ReadBytes, 0, len);

                    //将接收到的消息写入日志
                    Log.WriteLogs(string.Format("收到主机:{0}发来的消息|{1}", ip1, str));
                    tcpClient.GetStream().BeginRead(ReadBytes, 0, ReadBytes.Length, ReceiveCallBack, null);
                }
                else
                {
                    tcpClient = null;
                    ErrorOccuredHandler("ReceiveCallBack:读取0个字节数据");
                }
            }
            catch (Exception e)
            {
                ErrorOccuredHandler("ReceiveCallBack " + e.Message);
            }
        }

        //发送消息
        public void SendMsg(string msg)
        {
            byte[] msgBytes = Encoding.UTF8.GetBytes(msg);
            tcpClient.GetStream().BeginWrite(msgBytes, 0, msgBytes.Length, (ar) => {
                tcpClient.GetStream().EndWrite(ar);//结束异步发送
            }, null);//开始异步发送
        }

        /// <summary>
        /// 断开连接
        /// </summary>
        public void Close()
        {
            if(IsConnected())
                tcpClient.Close();
        }

        public bool IsConnected()
        {
            if (tcpClient == null)
                return false;

            if (tcpClient.Client == null)
                return false;

            if (tcpClient.Client.Connected)
                return true;
            else
                return false;
        }
    }
}
