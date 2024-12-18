using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace TestXml
{
    [XmlRoot("HardSpotConfig", IsNullable = false)]
    public class HardSpotConfig
    {
        public HardSpotConfig()
        {
        }
        public HardSpotConfig(int a, string d, List<Device> lsitDevice)
        {
            AccelerationBase = a;
            Devices = lsitDevice;
        }

        [XmlAttribute("accelerationBase")]
        public int AccelerationBase { get; set; }

        [XmlArray]
        public List<Device> Devices { get; set; }
    }

    [Serializable]
    public class Record
    {
        public Record()
        {
        }
        public Record(int i, int r, int v)
        {
            Index = i;
            Rate = r;
            Value = v;
        }

        [XmlAttribute("index")]
        public int Index { get; set; }

        [XmlAttribute("rate")]
        public int Rate { get; set; }

        [XmlAttribute("value")]
        public int Value { get; set; }

    }

    [Serializable]
    public class Device
    {
        public Device()
        {
        }
        public Device(int i, string d, List<Record> lsitRecord)
        {
            Index = i;
            Desc = d;
            Records = lsitRecord;
        }

        [XmlAttribute("index")]
        public int Index { get; set; }

        [XmlAttribute("desc")]
        public string Desc { get; set; }

        [XmlArray]
        public List<Record> Records { get; set; }
    }

    public class XmlSerializerTool
    {
        /// <summary>
        /// 文件反序列化为模型
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static T XmlFileToEntity<T>(string filePath)
        {
            try
            {
                FileStream fileStream = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.Read);
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(T));
                T t = (T)xmlSerializer.Deserialize(fileStream);
                fileStream.Dispose();
                return t;
            }
            catch (Exception)
            {
            }
            return default;
        }

        public static bool EntityToXmlFile<T>(T t, string xmlFilePath)
        {
            bool result = false;
            try
            {
                string text = Serializer<T>(t);
                text = text.Replace("utf-16", "utf-8");
                XmlDocument xmlDocument = new XmlDocument();
                xmlDocument.LoadXml(text);
                xmlDocument.Save(xmlFilePath);
                result = true;
            }
            catch (Exception)
            {
            }
            return result;
        }

        private static string Serializer<T>(T t)
        {
            XmlSerializerNamespaces xmlSerializerNamespaces = new XmlSerializerNamespaces();
            xmlSerializerNamespaces.Add(string.Empty, string.Empty);
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(T));
            StringWriter stringWriter = new StringWriter();
            xmlSerializer.Serialize(stringWriter, t, xmlSerializerNamespaces);
            string result = stringWriter.ToString();
            stringWriter.Close();
            stringWriter.Dispose();
            return result;
        }

        public static void Serializer<T>(T t, string xmlPath)
        {
            try
            {
                XmlWriterSettings xws = new XmlWriterSettings();
                xws.Indent = true;
                xws.OmitXmlDeclaration = false;
                xws.Encoding = Encoding.UTF8;
                using (XmlWriter xtw = XmlTextWriter.Create(xmlPath, xws))
                {
                    XmlSerializer xmldes = new XmlSerializer(typeof(T));
                    XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                    ns.Add("", "");
                    xmldes.Serialize(xtw, t, ns);
                }
            }
            catch (Exception e)
            {
            }
        }
    }
}
