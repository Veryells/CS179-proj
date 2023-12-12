using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;


namespace WindowsFormsApp1
{
    public partial class Form2 : Form
    {
        public static Form2 instance;
        public Label lab2;
        public string SelectedFilePath { get; private set; }


        public Form2()
        {
            InitializeComponent();
            instance = this;
            lab2 = label2;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "txt files (*.txt)|*.txt|All Files (*.*)|*.*";

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                // SelectedFilePath = ofd.FileName; 
                // Form3 f3 = new Form3();
                // f3.Show(); 
                // this.Hide(); 
                textBox1.Text = ofd.FileName;
            }
           
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form3 f3 = new Form3();
            f3.LoadFileIntoDataGridView(textBox1.Text); // Call the method to load the file
            f3.Show();
            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form5 f5 = new Form5();
            f5.LoadFileIntoDataGridView(textBox1.Text);
            f5.Show();
            this.Hide();
        }
    }
}
