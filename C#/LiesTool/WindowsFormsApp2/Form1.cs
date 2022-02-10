using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        int crc_16(List<bool> data, List<bool> poly)
        {
            List<bool> result = new List<bool>();
            result.Add(data[0]);
            for (int i = 0; i < poly.Count - 1; i++)
            {
                data.Add(false);
                result.Add(data[i + 1]);
            }
            for (int i = poly.Count; i < data.Count; i++)
            {
                if (result[0])
                {
                    for (int j = 0; j < poly.Count; j++)
                        result[j] = (result[j] != poly[j]);
                    result.RemoveAt(0);
                    result.Add(data[i]);
                }
                else
                {
                    result.RemoveAt(0);
                    result.Add(data[i]);
                }
            }
            int ret = 0;
            for (int i = result.Count - 1, j = 0; i > - 1; i--, j++)
            {
                if (result[j])
                    ret += (1 << i);
            }
            return ret;
        }


        int reverse8(int input)
        {
            int x = input;
            x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
            x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
            x = ((x >> 4) | (x << 4));
            return x & 0xFF;
        }


        int reverse16(int input)
        {
            int x = input;
            x = (((x & 0XAAAA) >> 1) | ((x & 0X5555) << 1));
            x = (((x & 0xCCCC) >> 2) | ((x & 0X3333) << 2));
            x = (((x & 0xF0F0) >> 4) | ((x & 0X0F0F) << 4));
            x = ((x >> 8) | (x << 8));
            return x;
        }


        uint reverse32(uint input)
        {
            uint x = input;
            x = (((x & 0xAAAAAAAA) >> 1) | ((x & 0x55555555) << 1));
            x = (((x & 0xCCCCCCCC) >> 2) | ((x & 0x33333333) << 2));
            x = (((x & 0xF0F0F0F0) >> 4) | ((x & 0x0F0F0F0F) << 4));
            x = (((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8));
            x = (x >> 16) | (x << 16);
            return x;
        }

        UInt64 reverse64(UInt64 input)
        {
            UInt64 x = input;
            x = (((x & 0xAAAAAAAAAAAAAAAA) >> 1) | ((x & 0x5555555555555555) << 1));
            x = (((x & 0xCCCCCCCCCCCCCCCC) >> 2) | ((x & 0x3333333333333333) << 2));
            x = (((x & 0xF0F0F0F0F0F0F0F0) >> 4) | ((x & 0x0F0F0F0F0F0F0F0F) << 4));
            x = (((x & 0xFF00FF00FF00FF00) >> 8) | ((x & 0x00FF00FF00FF00FF) << 8));
            x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16));
            x = (x >> 32) | (x << 32);
            return x;
        }


        // CRC POLYNOME = x15 + 1 =  1000 0000 0000 0001 = 0x8001
        int crc16(byte[] array, int polynome = 0x8001, int startmask = 0x0000, int endmask = 0x0000, bool reverseIn = false, bool reverseOut = false)
        {
            int crc = startmask;
            for (int j = 0; j < array.Length; j++)
            {
                int data = array[j];
                if (reverseIn) data = reverse8(data);
                crc ^= ((int)data) << 8;
                for (int i = 8; i > 0; i--)
                {
                    if ((crc & (1 << 15)) > 0)
                    {
                        crc <<= 1;
                        crc ^= polynome;
                    }
                    else
                    {
                        crc <<= 1;
                    }
                }
            }
            if (reverseOut) crc = reverse16(crc);
            crc ^= endmask;
            return crc & 0xFFFF;
        }

        static int AddCheckSum16(byte[] Buffer)
        {
            int crc = 0xFFFF;
            for (int j = 0; j < Buffer.Length; j++)
            {
                crc ^= Buffer[j];
                for (int i = 0; i < 8; i++)
                {
                    if ((crc & 0x01) > 0)
                    {
                        crc >>= 1;
                        crc ^= 0xA001;
                    }
                    else
                        crc >>= 1;
                }
            }
            return crc;
        }

        int CRC16(byte[] nData, int wLength)
        {
            int[] wCRCTable = {
       0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
       0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
       0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
       0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
       0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
       0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
       0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
       0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
       0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
       0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
       0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
       0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
       0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
       0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
       0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
       0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
       0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
       0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
       0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
       0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
       0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
       0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
       0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
       0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
       0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
       0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
       0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
       0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
       0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
       0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
       0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
       0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

            int nTemp;
            int wCRCWord = 0xFFFF;
            for (int i = 0; i < wLength; i++)
            {
                nTemp = nData[i] ^ wCRCWord;
                wCRCWord >>= 8;
                wCRCWord ^= wCRCTable[nTemp & 0xFF];
            }
            return wCRCWord;
        } // End: CRC16
        private void button1_Click(object sender, EventArgs e)
        {
            //string s = "const unsigned char __code ReverseByte[256] = {\n//";
            //for (int i = 0; i < 256; i += 16)
            //{
            //    for (int j = 0; j < 16; j++)
            //        s += "0x" + (i + j).ToString("X2") + "  ";
            //    s += "\n  ";
            //    for (int j = 0; j < 16; j++)
            //        s += "0x" + reverse8(i + j).ToString("X2") + ", ";
            //    s += "\n//";
            //}
            //richTextBox1.Text = s + "};";

            //SerialPort port = new SerialPort("COM22", 9600);
            //port.Open();
            //byte[] on = new byte[] { 83, 79, 76, 49, 79, 78, 10 , 10};
            //byte[] of = new byte[] { 83, 79, 76, 49, 79, 70, 10 , 10};
            //port.Write(on, 0, 8);
            //Thread.Sleep(100);
            //port.Write(of, 0, 8);
            //port.Close();
            //return;



            //List<bool> data = new List<bool>();
            //List<bool> poly = new List<bool>();
            //MatchCollection mc = Regex.Matches(richTextBox1.Text, @"[ABCDEFabcdef\d]{2}");
            //foreach (Match m in mc)
            //{
            //    int num = int.Parse(m.Value, System.Globalization.NumberStyles.HexNumber);
            //    for (int  i = 7; i > -1; i--)
            //        data.Add((num & (1 << i)) > 0);
            //}
            //mc = Regex.Matches(richTextBox2.Text, @"[^,]+");
            //int max = int.Parse(mc[0].Value);
            //for (int i = max, j = 0; i > -1; i--)
            //{
            //    if (mc[j].Value == i.ToString())
            //    {
            //        poly.Add(true);
            //        j++;
            //    }
            //    else
            //        poly.Add(false);
            //}            

            //richTextBox1.Text = crc_16(data, poly).ToString("X4");

            List<byte> data = new List<byte>();
            MatchCollection mc = Regex.Matches(richTextBox1.Text, @"[ABCDEFabcdef\d]{2}");
            foreach (Match m in mc)
            {
                byte num = byte.Parse(m.Value, System.Globalization.NumberStyles.HexNumber);
                data.Add(num);
            }
            //richTextBox1.Text = crc16(data.ToArray(), 0x8005, 0xFFFF, 0x0000, true, true).ToString("X4");
            richTextBox2.Text = crc16(data.ToArray(), int.Parse(textBox1.Text, System.Globalization.NumberStyles.HexNumber)
                , int.Parse(textBox2.Text, System.Globalization.NumberStyles.HexNumber),
                int.Parse(textBox3.Text, System.Globalization.NumberStyles.HexNumber),
                checkBox1.Checked, checkBox2.Checked).ToString("X4");
            richTextBox2.Text += "\n" + AddCheckSum16(data.ToArray()).ToString("X4");
            richTextBox2.Text += "\n" + CRC16(data.ToArray(), data.Count).ToString("X4");

            //string s0 = "#include \"font.h\"\nstatic const unsigned char FontData[] PROGMEM = {\n  ";
            //string s1 = "const Font_TypeDef Font[] PROGMEM = {\n";
            //MatchCollection char_line = Regex.Matches(richTextBox1.Text, @"[^\r\n]+");
            //int cindex = 0;
            //for (int i = 0; i < char_line.Count; i++)
            //{
            //    MatchCollection mc = Regex.Matches(char_line[i].Value, @"[ABCDEFabcdef\d]{4}");
            //    s1 += "  {" + mc.Count + ", " + cindex + "},      //" + (char)((int)' ' + i) + "\n";
            //    cindex += mc.Count * 2;
            //    for (int j = 0; j < mc.Count; j++)
            //        s0 += "0x" + mc[j].Value.Substring(0, 2) + ", ";
            //    for (int j = 0; j < mc.Count; j++)
            //        s0 += "0x" + mc[j].Value.Substring(2, 2) + ", ";
            //    s0 += "     //" + (char)((int)' ' + i) + "\n  ";
            //}
            //richTextBox1.Text = s0 + "};\n" + s1 + "};";

            //string s1 = "const Font_TypeDef Number[] PROGMEM = {\n";
            //MatchCollection double_newline = Regex.Matches(richTextBox1.Text, @"\n{2}");
            //int str_index = 0;
            //int byte_index = 0;
            //for (int i = 0; i < 10; i++)
            //{
            //    Match first_line = Regex.Match(richTextBox1.Text.Substring(str_index, double_newline[i].Index - str_index), @"[^\n]+");
            //    int width = Regex.Matches(first_line.Value, @"0x").Count;
            //    s1 += "  {" + width + ", " + byte_index + "},      //" + i.ToString() + "\n";
            //    str_index = double_newline[i].Index + 0;
            //    byte_index += width * 5;
            //}
            //string[] num_comment = { ".", "°", "C" };
            //for (int i = 0; i < 3; i++)
            //{
            //    Match first_line = Regex.Match(richTextBox1.Text.Substring(str_index, double_newline[i + 10].Index - str_index), @"[^\n]+");
            //    int width = Regex.Matches(first_line.Value, @"0x").Count;
            //    s1 += "  {" + width + ", " + byte_index + "},      //" + num_comment[i] + "\n";
            //    str_index = double_newline[i + 10].Index + 0;
            //    byte_index += width * 5;
            //}
            //richTextBox1.Text = s1 + "};";


        }

        SerialPort port = null;
        private void button4_Click(object sender, EventArgs e)
        {
            if (port != null)
                return;
            comboBox1.Items.Clear();
            foreach (string s in SerialPort.GetPortNames())
                comboBox1.Items.Add(s);
            if (comboBox1.Items.Count > 0)
                comboBox1.SelectedIndex = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (button2.Text == "disconnect")
            {
                try { port.Close(); } catch { }
                button2.Text = "connect";
                port.Dispose();
                port = null;
            }
            else
            {
                if (port != null || comboBox1.SelectedIndex < 0)
                    return;
                SerialPort p = new SerialPort((string)comboBox1.SelectedItem);
                try { p.Open(); }
                catch { MessageBox.Show("can not open " + p.PortName); return; }
                port = p;
                button2.Text = "disconnect";
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0)
                return;
            if (port != null)
            {
                try { port.Close(); } catch { }
                button2.Text = "connect";
                port.Dispose();
                port = null;
            }
            else
            {
                SerialPort p = new SerialPort((string)comboBox1.SelectedItem);
                try { p.Close(); } catch { }
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
                numericUpDown1.Enabled = true;
            else
                numericUpDown1.Enabled = false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (port != null)
            {
                byte[][] on = new byte[2][]
                {
                    new byte[] { 8, 85, 1, 18, 0, 0, 0, 1, 105 },
                    new byte[] { 6, 83, 79, 76, 49, 79, 78, },
                };
                byte[][] of = new byte[2][]
                {
                    new byte[] { 8, 85, 1, 17, 0, 0, 0, 1, 104 },
                    new byte[] { 6, 83, 79, 76, 49, 79, 70, },
                };
                string[] text_on = new string[]
                {
                    "write on by 85,1,...\n",
                    "write on by SOL1ON\n",
                };
                string[] text_of = new string[]
                {
                    "write off by 85,1,...\n",
                    "write off by SOL1ON\n",
                };
                int index = radioButton1.Checked ? 0 : 1;
                try { port.Write(on[index], 1, on[index][0]); } 
                catch { 
                    MessageBox.Show("write on faild");
                    button2_Click(null, null);
                    return;
                }
                richTextBox1.Text += text_on[index];
                if (checkBox3.Checked)
                {
                    Thread.Sleep((int)numericUpDown1.Value);
                    try { port.Write(of[index], 1, of[index][0]); }
                    catch
                    {
                        MessageBox.Show("write off faild");
                        button2_Click(null, null);
                        return;
                    }
                    richTextBox1.Text += text_of[index];
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (port != null)
            {
                byte[][] on = new byte[2][]
                {
                    new byte[] { 8, 85, 1, 18, 0, 0, 0, 1, 105 },
                    new byte[] { 6, 83, 79, 76, 49, 79, 78, },
                };
                string[] text_on = new string[]
                {
                    "write on by 85,1,...\n",
                    "write on by SOL1ON\n",
                };
                int index = radioButton1.Checked ? 0 : 1;
                try { port.Write(on[index], 1, on[index][0]); }
                catch
                {
                    MessageBox.Show("write on faild");
                    button2_Click(null, null);
                    return;
                }
                richTextBox1.Text += text_on[index];
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (port != null)
            {
                byte[][] of = new byte[2][]
                {
                    new byte[] { 8, 85, 1, 17, 0, 0, 0, 1, 104 },
                    new byte[] { 6, 83, 79, 76, 49, 79, 70, },
                };
                string[] text_of = new string[]
                {
                    "write off by 85,1,...\n",
                    "write off by SOL1OF\n",
                };
                int index = radioButton1.Checked ? 0 : 1;
                try { port.Write(of[index], 1, of[index][0]); }
                catch
                {
                    MessageBox.Show("write off faild");
                    button2_Click(null, null);
                    return;
                }
                richTextBox1.Text += text_of[index];
            }
        }
    }
}
