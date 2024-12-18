using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCsharp
{
    class DateTimeTest
    {
        static public void DateTimeTryParse()
        {

            string[] ListDt = new string[2] { "20220620", "TX2MonitoringService" };

            foreach (string dirItem in ListDt)
            {
                DateTime dt;
                if (DateTime.TryParseExact(dirItem, "yyyyMMdd", System.Globalization.CultureInfo.CurrentCulture, DateTimeStyles.None, out dt))
                {

                    TimeSpan ts = DateTime.Now - dt;

                    //if (ts.Days > 2)
                    //{
                    //    dirItem.Delete(true);
                    //}

                    Console.WriteLine("是正确的日期格式类型" + dirItem);
                }
                else
                {
                    Console.WriteLine("不是正确的日期格式类型"+ dirItem);
                }
            }
        }

    }
}
