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
    public partial class Form3 : Form
    {
        public static Form3 instance;
        public Label lab1;
        public Form3()
        {
            InitializeComponent();
            instance = this;
            lab1 = label1;
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }


        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }
        public void LoadFileIntoDataGridView(string filePath)
        {
            DataTable dataTable = new DataTable();
            string[] fileContent = File.ReadAllLines(filePath);

            // Assuming the file is comma-separated
            if (fileContent.Length > 0)
            {
                // Create columns based on the first line
                string[] columns = fileContent[0].Split(',');
                foreach (string column in columns)
                {
                    dataTable.Columns.Add(column.Trim());
                }

                // Add rows
                for (int i = 1; i < fileContent.Length; i++)
                {
                    string[] rowData = fileContent[i].Split(',');
                    dataTable.Rows.Add(rowData);
                }
            }

            dataGridView1.DataSource = dataTable;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form4 f4 = new Form4();
            f4.Show();
            Visible = false;
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
            Visible = false;
        }
    }
    
}
