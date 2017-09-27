using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace beautycode2
{
    class Program
    {
        static void makeusage(float level)
        {
            PerformanceCounter p = new PerformanceCounter("Processor", "% Processor Time", "_Total");
            while (true)
            {
                if (p.NextValue() > level)
                    System.Threading.Thread.Sleep(10);
            }
        }
        static void Main(string[] args)
        {
            makeusage((float)0.5);
        }
    }
}
