using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCsharp
{
    public class Json
    {
        public class Defect
        {
            [JsonProperty]
            public string dstImage { get; set; }

            [JsonProperty]
            public string srcImage { get; set; }

            [JsonProperty]
            public string defectType { get; private set; }

            [JsonProperty]
            public DefectValue defectValue { get; private set; }
        }

        public class DefectValue
        {
            [JsonProperty]
            public int type { get; private set; }

            [JsonProperty]
            public Position srcRect { get; private set; }

            [JsonProperty]
            public Position dstRect { get; private set; }

        }

        public class Position
        {
            [JsonProperty]
            public int right { get; set; }

            [JsonProperty]
            public int top { get; set; }

            [JsonProperty]
            public int bottom { get; set; }

            [JsonProperty]
            public int left { get; set; }
        }

        public class LocationIn
        {
            [JsonProperty]
            public int x { get; set; }

            [JsonProperty]
            public int y { get; set; }

            [JsonProperty]
            public int w { get; set; }

            [JsonProperty]
            public int h { get; set; }
        }


        public class DefectIn
        {
            [JsonProperty]
            public string deviceID { get; set; }

            [JsonProperty]
            public string defectType { get; set; }

            [JsonProperty]
            public string defectLevel { get; set; }

            [JsonProperty]
            public int speed { get; set; }

            [JsonProperty]
            public string discoverTime { get; set; }


            [JsonProperty]
            public List<string> filePath { get; set; }


            [JsonProperty]
            public List<LocationIn> location { get; set; }

            [JsonProperty]
            public string defectDesc { get; set; }

            [JsonProperty]
            public string uploader { get; set; }
        }

        public class LocationOut
        {
            public LocationOut(int ix, int iy, int iw, int ih)
            {
                x = ix;
                y = iy;
                width = iw;
                height = ih;
            }

            [JsonProperty]
            public int x { get; set; }

            [JsonProperty]
            public int y { get; set; }

            [JsonProperty]
            public int width { get; set; }

            [JsonProperty]
            public int height { get; set; }
        }

        public class Profession
        {
            public Profession()
            {
                locations = new List<LocationOut>();
            }

            [JsonProperty]
            public string wheelNum { get; set; }

            [JsonProperty]
            public string boxNum { get; set; }

            [JsonProperty]
            public List<LocationOut> locations { get; set; }
        }


        public class DefectOut
        {
            public DefectOut()
            {
                filePath = new List<string>();
                profession = new Profession();
            }

            [JsonProperty]
            public string defectType { get; set; }

            [JsonProperty]
            public int defectLevel { get; set; }

            [JsonProperty]
            public float defectValue { get; set; }

            [JsonProperty]
            public string discoverTime { get; set; }

            [JsonProperty]
            public int speed { get; set; }

            [JsonProperty]
            public List<string> filePath { get; set; }

            [JsonProperty]
            public string lineCode { get; set; }

            [JsonProperty]
            public string siteName { get; set; }

            [JsonProperty]
            public int direction { get; set; }


            [JsonProperty]
            public string carriage { get; set; }

            [JsonProperty]
            public int detectDataID { get; set; }


            [JsonProperty]
            public string status { get; set; }

            [JsonProperty]
            public string jobId { get; set; }

            [JsonProperty]
            public int jobIndex { get; set; }

            [JsonProperty]
            public string defectDesc { get; set; }

            [JsonProperty]
            public string uploader { get; set; }

            [JsonProperty]
            public Profession profession { get; set; }
        }


        static public void JsonTest()
        {
            string str = System.IO.File.ReadAllText(@"D:\1.json");

            JObject jObject = new JObject();        //新建 操作对象
            List<DefectIn> defects = JsonConvert.DeserializeObject<List<DefectIn>>(str);
            byte[] byteNewJson = new byte[5];


            if (defects != null && defects.Count > 0)
            {
                DefectIn defIn = defects[0];
                DefectOut defOut = new DefectOut();

                defOut.defectType = defIn.defectType;
                defOut.defectLevel = int.Parse(defIn.defectLevel);
                defOut.defectValue = 0;
                defOut.discoverTime = defIn.discoverTime;
                defOut.speed = defIn.speed;

                if (defIn.filePath != null && defIn.filePath.Count != 0)
                {
                    defOut.profession.wheelNum = "3";
                    defOut.profession.boxNum = "2";
                    defOut.filePath.Add(defIn.filePath[0]);
                }
                else
                {
                    defOut.profession.wheelNum = "0";
                    defOut.profession.boxNum = "0";

                    //defOut.filePath.Add("");
                }

                defOut.lineCode = "";
                defOut.siteName = "";
                defOut.direction = 0;
                defOut.carriage = "";
                defOut.detectDataID = 0;
                defOut.status = "";

                defOut.jobId = "";

                defOut.jobIndex = 0;
                defOut.defectDesc = defIn.defectDesc;
                defOut.uploader = defIn.uploader;

                if (defIn.location != null && defIn.location.Count != 0)
                {
                    defOut.profession.locations.Add(new LocationOut(defIn.location[0].x, defIn.location[0].y, defIn.location[0].w, defIn.location[0].h));
                }
                //else
                //{
                //    defOut.profession.locations.Add(new LocationOut());

                //    defOut.profession.locations[0].x = 0;
                //    defOut.profession.locations[0].y = 0;
                //    defOut.profession.locations[0].width = 0;
                //    defOut.profession.locations[0].height = 0;
                //}

                List<DefectOut> defsOut = new List<DefectOut>();
                defsOut.Add(defOut);
                string newStr = JsonConvert.SerializeObject(defsOut);

                byteNewJson = System.Text.Encoding.UTF8.GetBytes(newStr);
            }
            else
            {
                byteNewJson = System.Text.Encoding.UTF8.GetBytes(str);
            }

            //保存文件
            Task.Run(() =>
            {
                try
                {
                    FileStream fs = new FileStream(@"D:\defect_1.json", FileMode.Create, FileAccess.Write);

                    fs.Write(byteNewJson, 0, byteNewJson.Length);
                    fs.Close();

                }
                catch (Exception ex)
                {

                }
            });

        }
    }
}
