using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCsharp
{
    class ListTest
    {
        public class A
        {
            public A(int a1, int a2)
            {
                A1 = a1;
                A2 = a2;
            }
            public int  A1 { get; set; }
            public int  A2 { get; set; }
        }

        static public void DeleteWhileTravellThrough()
        {
            List<A> list = new List<A>();
            list.Add(new A(1, 1));
            list.Add(new A(2, 2));
            list.Add(new A(2, 3));

            var tempHis = list;

            tempHis.Add(new A(3, 3));


            //for(int i = list.Count-1; i>=0;i--)
            //{
            //    if (list[i].A1 == 2)
            //        list.Remove(list[i]);
            //}

            list.RemoveAll(s => s.A1 == 2);


            list.Add(new A(2, 2));
            list.Add(new A(2, 3));

            List<A> tempHisB = new List<A>(list);

            try
            {
                tempHisB.ForEach(e =>
                {
                    if (e.A1==1)
                    {
                        list.Remove(e);
                    }
                });
            }
            catch (Exception ex)
            {
                Console.WriteLine("TX2Worker", "更新保存任务类型历史异常：" + ex.Message + ex.StackTrace);
            }

            bool bSuc = list.Remove(new A(2,3));
        }
    }
}
