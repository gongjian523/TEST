using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCsharp
{
    class Program
    {

        static string JobTime = "20211231053532";

        public static long ToTimeSpan(string curTime)
        {
            long timeSpan = 0;

            DateTime dtJob, dtCur;

            if (!DateTime.TryParseExact(curTime, "yyyyMMddHHmmss", System.Globalization.CultureInfo.CurrentCulture, System.Globalization.DateTimeStyles.None, out dtCur))
            {
                return timeSpan;
            }

            if (!DateTime.TryParseExact(JobTime, "yyyyMMddHHmmss", System.Globalization.CultureInfo.CurrentCulture, System.Globalization.DateTimeStyles.None, out dtJob))
            {
                return timeSpan;
            }

            try
            {
                //timeSpan = Math.Abs(long.Parse(curTime) - long.Parse(JobTime));

                timeSpan = Math.Abs((long)(dtCur - dtJob).TotalSeconds);
            }
            catch (Exception ex)
            {
                //LocalNLogHelper.Error("AcquireJobStorage", "计算时间间隔异常" + ex.Message);
            }
            return timeSpan;
        }

        static void Main(string[] args)
        {

            //Json.JsonTest();

            //ListTest.DeleteWhileTravellThrough();

            //DateTimeTest.DateTimeTryParse();

            //string passingTypeHisFile = @"D:\134Package\Host\modules\TX2Service_LD\PassingTypeHistory.json";
            //string passingTypeHisBakFile = passingTypeHisFile.Substring(0, passingTypeHisFile.LastIndexOf("json")) + "bak";

            //SystemTimersTest.Test();

            //string path = "\\\\127.0.0.1\\cdtydata\\RailsideData\\20240215\\172527\\TrainBody360\\CameraXZ\\TX360000";
            string path = "d:\\cdtydata\\RailsideData\\20240215\\172527\\TrainBody360\\CameraXZ\\TX360000";
            try
            {
                Directory.CreateDirectory(path);
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("创建文件夹{0}失败：{1}", path, ex.Message));
            }

            Console.ReadKey();
        }
    }
}
