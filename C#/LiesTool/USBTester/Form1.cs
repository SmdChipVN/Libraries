using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using USB;

namespace USBTester
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        USBDevice usb = null;
        string PID, VID;
        bool send_done = false;
        private void button1_Click(object sender, EventArgs e)
        {
            Match pid = Regex.Match(textBox1.Text, @"[ABCDEFabcdef\d]{4}");
            Match vid = Regex.Match(textBox2.Text, @"[ABCDEFabcdef\d]{4}");
            if (pid.Success && vid.Success)
            {
                if (usb == null || PID != pid.Value || VID != vid.Value)
                {
                    usb = new USBDevice(int.Parse(vid.Value, System.Globalization.NumberStyles.HexNumber),
                        int.Parse(pid.Value, System.Globalization.NumberStyles.HexNumber));
                    PID = pid.Value;
                    VID = vid.Value;
                }
                textBox1.Text = pid.Value; 
                textBox2.Text = vid.Value; 
                if (usb.Connect())
                    richTextBox1.Text += "is connect\n";
                else
                    richTextBox1.Text += "not connect\n";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            button2_Click(null, null);
            if (send_done)
            {
                byte[] data;
                if (radioButton1.Checked)
                    data = usb.ReadControl();
                else
                    data = usb.Read();
                if (data != null && data.Length > 3)
                    richTextBox1.Text += "received: " + System.Text.Encoding.Default.GetString(data, 0, 4) + "\n";
                else
                    richTextBox1.Text += "received: null\n";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (usb != null && usb.Connect() && textBox3.Text.Length > 0)
            {
                byte[] data = new byte[textBox3.Text.Length];
                for (int i = 0; i < textBox3.Text.Length; i++)
                    data[i] = (byte)textBox3.Text[i];
                bool done;
                if (radioButton1.Checked)
                    done = usb.WriteControl(data);
                else
                    done = usb.Write(data);
                if (done)
                {
                    richTextBox1.Text += "send: " + textBox3.Text + "\n";
                    send_done = true;
                }
                else
                {
                    richTextBox1.Text += "send failed\n";
                    send_done = false;
                }
            }
            else
                send_done = false;
        }
    }
}
