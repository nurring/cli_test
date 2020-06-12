using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ClamirCLR;

namespace ClamirView
{
    public partial class Form1 : Form
    {
        ClamirCLR.ClamirCLR clamirCLR = new ClamirCLR.ClamirCLR();
        bool retry = true;
        static int connection_result = 1;
        static int connection_retry_n = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox3.Text =
            clamirCLR.Add(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text)).ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox3.Text =
            clamirCLR.Subtract(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text)).ToString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBox3.Text =
            clamirCLR.Multiply(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text)).ToString();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox3.Text =
            clamirCLR.Divide(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text)).ToString();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Clicked!");
            while (retry)
            {
                MessageBox.Show("Try connection..");
                connection_result = clamirCLR.ConnectDevice();
                if (connection_result == 0)
                {
                    MessageBox.Show("Connected!");
                    retry = false;
                }
                else
                {
                    if (connection_retry_n < 2)
                    {
                        connection_retry_n++;
                        MessageBox.Show("Retrying again in a second. Try number ", connection_retry_n.ToString());
                    }
                    else
                    {
                        MessageBox.Show("Closing this application. Check if a CLAMIR system is connected to your network.");
                        retry = false;
                    }
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            clamirCLR.DisconnectDevice();
        }
    }
}
