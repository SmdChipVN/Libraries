using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CreateFont
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }
        public void UpdateData(string Data)
        {
            rtxt_data.Text = txt_name.Text + "\n{" + Data + "\n}";
            this.ShowDialog();
        }
    }
}
