using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestXml
{
    class Program
    {
        static void Main(string[] args)
        {
            string configFilePath = AppDomain.CurrentDomain.BaseDirectory + @"\HardSpot.xml";

            HardSpotConfig config = new HardSpotConfig();

            config.AccelerationBase = 4;

            List<Record> records = new List<Record>();
            records.Add(new Record(1, 1866, 0));
            records.Add(new Record(2, 1919, 15));
            records.Add(new Record(3, 1981, 30));
            records.Add(new Record(4, 2039, 45));
            records.Add(new Record(5, 2111, 60));
            
            config.Devices = new List<Device>();
            
            config.Devices.Add(new Device(1, "Pressure1", records));
            config.Devices.Add(new Device(2, "Pressure2", records));
            config.Devices.Add(new Device(3, "Pressure3", records));
            config.Devices.Add(new Device(4, "Pressure4", records));


            XmlSerializerTool.EntityToXmlFile(config, configFilePath);

            HardSpotConfig configNew = XmlSerializerTool.XmlFileToEntity<HardSpotConfig>(configFilePath);

            Console.ReadLine();
        }
    }
}
