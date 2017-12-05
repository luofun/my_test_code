///testuse52
using System;
using System.Management;
using System.Windows.Forms;

namespace WMISample
{
    public class MyWMIQuery
    {
        public static void Main()
        {
            try
            {
                ManagementObjectSearcher searcher =
                    new ManagementObjectSearcher("root\\WMI",
                    "SELECT * FROM MSSmBios_RawSMBiosTables");

                foreach (ManagementObject queryObj in searcher.Get())
                {
                    Console.WriteLine("-----------------------------------");
                    Console.WriteLine("MSSmBios_RawSMBiosTables instance");
                    Console.WriteLine("-----------------------------------");

                    if (queryObj["SMBiosData"] == null)
                        Console.WriteLine("SMBiosData: {0}", queryObj["SMBiosData"]);
                    else
                    {
                        Byte[] arrSMBiosData = (Byte[])(queryObj["SMBiosData"]);
                        Console.WriteLine("data:");
                        int i = 0;
                        foreach (Byte arrValue in arrSMBiosData)
                        {
                            if (i % 16 == 0)
                                Console.WriteLine("");
                            i++;
                            if (arrValue < 16)
                            {
                                Console.Write("{0:x}  ", arrValue);
                            }
                            else
                            {
                                Console.Write("{0:x} ", arrValue);
                            }
                        }
                    }
                }
            }
            catch (ManagementException e)
            {
                MessageBox.Show("An error occurred while querying for WMI data: " + e.Message);
            }
        }
    }
}
///end