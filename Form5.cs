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
    public partial class Form5 : Form
    {
        public static Form5 instance;
        public Label lab5;
        public Form5()
        {
            InitializeComponent();
            instance = this;
            lab5 = label1;
        }

        private void Form5_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form1 f1 = new Form1();
            f1.Show();
            Visible = false;
        }


        private void button3_Click_1(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
            Visible = false;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
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

    }
}
