using EasyBioCapture;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EasyBioCaptureTestApp
{
    public partial class Form1 : Form
    {
        BackgroundWorker bw;
        public Form1()
        {
            InitializeComponent();
            bw = new BackgroundWorker();
            bw.WorkerSupportsCancellation = true;
            bw.WorkerReportsProgress = true;
            bw.DoWork += bw_DoWork;
            bw.RunWorkerCompleted += bw_RunWorkerCompleted;
        }

        void bw_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            ScanTest();
        }

        void bw_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            BeginInvoke(new Action(() =>
            {
                button1.Text = "Scan Now";
                button1.Enabled = true;
            }));
        }

        public void ScanTest()
        {
            EasyBioCaptureSample b = EasyBioCapture.EasyBioCapture.CaptureSample();
            byte[] incoming = b.buffer;
            BeginInvoke(new Action(() =>
            {
                richTextBox1.AppendText(b.Width + "\n");
                richTextBox1.AppendText(b.Height + "\n");
                richTextBox1.AppendText(b.PixelDepth + "\n");
            }));
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < incoming.Length; i++)
            {
                sb.Append(incoming[i]).Append(", ");
            }
            BeginInvoke(new Action(() =>
            {
                richTextBox1.AppendText(sb.ToString());
            }));
            Bitmap bmp;
            bmp = new Bitmap((b.Width / 3), b.Height, PixelFormat.Format24bppRgb);
            BitmapData bmData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadWrite, bmp.PixelFormat);
            IntPtr pNative = bmData.Scan0;
            Marshal.Copy(incoming, 0, pNative, bmp.Width * bmp.Height * 3);
            bmp.UnlockBits(bmData);
            BeginInvoke(new Action(() =>
            {
                pictureBox1.Image = bmp;
            }));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            bw.RunWorkerAsync();
            richTextBox1.Clear();
            button1.Text = "Place Finger on the Scanner";
            button1.Enabled = false;
        }
    }
}
