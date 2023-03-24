using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;


namespace BluetoothForm
{
    public partial class Form1 : Form
    {

        SerialPort port = new SerialPort();
        public Form1()
        {
            InitializeComponent();
            selectButton.Enabled = false;
            closeButton.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }


        private static void SendSampleData()
        {
            // Instantiate the communications
            // port with some basic settings
            SerialPort port = new SerialPort( "COM1", 9600, Parity.None, 8, StopBits.One);

            // Open the port for communications
            port.Open();

            // Write a string
            port.Write("Hello World");

            // Write a set of bytes
            

            // Close the port
            port.Close();
        }

        private void findPorts_Click(object sender, EventArgs e)
        {
            Dictionary<string, string> comboSource = new Dictionary<string, string>();
       
            foreach (string s in SerialPort.GetPortNames())
            {
                comboSource.Add(s,s);
            }

            portsBox.DataSource = new BindingSource(comboSource, null);
            portsBox.DisplayMember = "Value";
            portsBox.ValueMember = "Key";

            selectButton.Enabled = true;
        }

        private void selectButton_Click(object sender, EventArgs e)
        {
            string key = ((KeyValuePair<string, string>)portsBox.SelectedItem).Key;
            string value = ((KeyValuePair<string, string>)portsBox.SelectedItem).Value;

            //textBox1.Text = key;
           // textBox2.Text = value;

            port = new SerialPort(value, 9600, Parity.None, 8, StopBits.One);
            //MessageBox.Show(value);

            try
            {
                port.Open();
            }
            catch (Exception exp)
            {
                MessageBox.Show(exp.ToString());
            }

            //port.Write(new byte[] { 0x0A, 0xE2, 0xFF }, 0, 3);
            //port.Write("2");

            selectButton.Enabled = false;
            closeButton.Enabled = true;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            port.Close();
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            port.Close();
            selectButton.Enabled = true;
            closeButton.Enabled = false;
        }

        private void beethovenButton_Click(object sender, EventArgs e)
        {
            port.Write("1");
            this.BackgroundImage = Image.FromFile("C:\\Users\\zeg68\\Documents\\Arduino\\SI\\Beethoven.jpg");
        }

        private void piratesButton_Click(object sender, EventArgs e)
        {
            port.Write("2");
            this.BackgroundImage = Image.FromFile("C:\\Users\\zeg68\\Documents\\Arduino\\SI\\Pirate.jpg");
        }

        private void crazyfrogButton_Click(object sender, EventArgs e)
        {
            port.Write("3");
            this.BackgroundImage = Image.FromFile("C:\\Users\\zeg68\\Documents\\Arduino\\SI\\CrazyFrog.jpg");
        }

        private void marioButton_Click(object sender, EventArgs e)
        {
            port.Write("4");
            this.BackgroundImage = Image.FromFile("C:\\Users\\zeg68\\Documents\\Arduino\\SI\\mario.jpg");
        }

        private void titanicButton_Click(object sender, EventArgs e)
        {
            port.Write("5");
            this.BackgroundImage = Image.FromFile("C:\\Users\\zeg68\\Documents\\Arduino\\SI\\titanic.jpg");
        }

        private void tempoplusButton_Click(object sender, EventArgs e)
        {
            port.Write("+");
        }

        private void tempominusButton_Click(object sender, EventArgs e)
        {
            port.Write("-");
        }

        private void tempoequalButton_Click(object sender, EventArgs e)
        {
            port.Write("=");
        }
    }
}
