using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using FileManager;

namespace Test
{
    public partial class Form1 : Form
    {
        Bitmap bmp = null;
        public Form1()
        {
            InitializeComponent();
            bmp = new Bitmap(128, 64);
        }
        int count_bit(int value)
        {
            int ret = 0;
            for (int i = 0; i < 8; i++)
            {
                if ((value & (1 << i)) > 0)
                    ret++;
            }
            return ret;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            XMLNode xml = new XMLNode()
            {
                TypeName = "aaa_TypeDef",
                Attributes = new Dictionary<string, string>()
                {
                    {"Name", "aaa" },
                    {"Version", "1.0" },
                },
            };
            xml.AddChild(new XMLNode()
            {
                TypeName = "bbb_TypeDef",
                Attributes = new Dictionary<string, string>()
                {
                    {"Name", "b0" },
                    {"Value", "10" },
                },
            });
            xml.AddChild(new XMLNode()
            {
                TypeName = "bbb_TypeDef",
                Attributes = new Dictionary<string, string>()
                {
                    {"Name", "b1" },
                    {"Value", "20" },
                },
            });
            xml.AddChild(new XMLNode()
            {
                TypeName = "bbb_TypeDef",
                Attributes = new Dictionary<string, string>()
                {
                    {"Name", "b2" },
                    {"Value", "30" },
                },
            });
            xml.GetChild(0).AddChild(new XMLNode()
            {
                TypeName = "ccc_TypeDef",
                Attributes = new Dictionary<string, string>()
                {
                    {"Name", "ccc" },
                    {"Date", "11/10/2021" },
                },
            });
            //richTextBox1.Text = xml.GetChild(0).GetText();
            //XMLNode node = xml.GetChildren("bbb_TypeDef")[(int)numericUpDown1.Value];
            //richTextBox1.Text = node.GetText(node.GetLevel());
            richTextBox1.Text = xml["Name"];
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (fontDialog1.ShowDialog() == DialogResult.OK)
            {
                label1.Text = fontDialog1.Font.Name + ",  " + fontDialog1.Font.Size.ToString("0.00");
                checkBox1.Checked = fontDialog1.Font.Bold;
                checkBox2.Checked = fontDialog1.Font.Italic;

                if (pictureBox1.Image != null)
                    pictureBox1.Dispose();
                //using (Graphics gr = Graphics.FromImage(bmp))
                //{
                //    //gr.Clear(Color.Black);
                //    gr.DrawString("Abcd", fontDialog1.Font, Brushes.White, 0, 0);
                //}
                using (Graphics gr = Graphics.FromImage(bmp)) // SourceImage is a Bitmap object
                {
                    //gr.Clear(Color.Black);
                    gr.DrawString("Abcd", fontDialog1.Font, Brushes.White, 0, 0);
                    var gray_matrix = new float[][] {
                        new float[] { 0.299f, 0.299f, 0.299f, 0, 0 },
                        new float[] { 0.587f, 0.587f, 0.587f, 0, 0 },
                        new float[] { 0.114f, 0.114f, 0.114f, 0, 0 },
                        new float[] { 0,      0,      0,      1, 0 },
                        new float[] { 0,      0,      0,      0, 1 }
                        };
                    var ia = new System.Drawing.Imaging.ImageAttributes();
                    ia.SetColorMatrix(new System.Drawing.Imaging.ColorMatrix(gray_matrix));
                    ia.SetThreshold(0.8f); // Change this threshold as needed
                    var rc = new Rectangle(0, 0, bmp.Width, bmp.Height);
                    gr.DrawImage(bmp, rc, 0, 0, bmp.Width, bmp.Height, GraphicsUnit.Pixel, ia);
                }
                {
                    Bitmap img = new Bitmap(pictureBox1.Width, pictureBox1.Height);
                    Graphics gimg = Graphics.FromImage(img);
                    gimg.Clear(Color.Black);
                    for (int i = 0; i < bmp.Height; i++)
                    {
                        for (int j = 0; j < bmp.Width; j++)
                        {
                            if (bmp.GetPixel(j, i).R > 128)
                                gimg.FillRectangle(Brushes.White, j * 4, i * 4, 4, 4);
                        }
                    }
                    gimg.Dispose();
                    pictureBox1.Image = img;
                }
            }    
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MatchCollection mc = Regex.Matches(richTextBox1.Text, @"0x[ABCDEFabcdef\d]{2}");
            string s = "";
            if (mc.Count > 0)
            {
                foreach (Match m in mc)
                {
                    int value = int.Parse(m.Value.Substring(2), System.Globalization.NumberStyles.HexNumber);
                    int data = 0;
                    for (int i = 0; i < 8; i++)
                        data |= ((value & (1 << i)) > 0) ? 0x80 >> i : 0;
                    s += "0x" + data.ToString("X2") + "\n";
                }
            }
            richTextBox1.Text = s;
        }
    }
}
