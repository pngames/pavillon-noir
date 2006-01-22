using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace RSSReader
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            RSSReaderMain rssmain = new RSSReaderMain();
           
            Application.Run(rssmain);
           
           
        }
    }
}