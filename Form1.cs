using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public static Form1 instance;
        public Form1()
        {
            InitializeComponent();
            instance = this;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
            Visible = false;
            Form2.instance.lab2.Text = textBox1.Text;
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
