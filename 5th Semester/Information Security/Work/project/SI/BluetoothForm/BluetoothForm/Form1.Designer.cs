namespace BluetoothForm
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.portsBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.findPorts = new System.Windows.Forms.Button();
            this.selectButton = new System.Windows.Forms.Button();
            this.closeButton = new System.Windows.Forms.Button();
            this.beethovenButton = new System.Windows.Forms.Button();
            this.piratesButton = new System.Windows.Forms.Button();
            this.crazyfrogButton = new System.Windows.Forms.Button();
            this.marioButton = new System.Windows.Forms.Button();
            this.titanicButton = new System.Windows.Forms.Button();
            this.tempoplusButton = new System.Windows.Forms.Button();
            this.tempominusButton = new System.Windows.Forms.Button();
            this.tempoequalButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // portsBox
            // 
            this.portsBox.BackColor = System.Drawing.Color.White;
            this.portsBox.FormattingEnabled = true;
            this.portsBox.Location = new System.Drawing.Point(12, 25);
            this.portsBox.Name = "portsBox";
            this.portsBox.Size = new System.Drawing.Size(121, 21);
            this.portsBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Ports";
            // 
            // findPorts
            // 
            this.findPorts.Location = new System.Drawing.Point(149, 25);
            this.findPorts.Name = "findPorts";
            this.findPorts.Size = new System.Drawing.Size(77, 23);
            this.findPorts.TabIndex = 2;
            this.findPorts.Text = "Find";
            this.findPorts.UseVisualStyleBackColor = true;
            this.findPorts.Click += new System.EventHandler(this.findPorts_Click);
            // 
            // selectButton
            // 
            this.selectButton.Location = new System.Drawing.Point(240, 25);
            this.selectButton.Name = "selectButton";
            this.selectButton.Size = new System.Drawing.Size(77, 23);
            this.selectButton.TabIndex = 3;
            this.selectButton.Text = "Start";
            this.selectButton.UseVisualStyleBackColor = true;
            this.selectButton.Click += new System.EventHandler(this.selectButton_Click);
            // 
            // closeButton
            // 
            this.closeButton.Location = new System.Drawing.Point(240, 63);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(77, 23);
            this.closeButton.TabIndex = 6;
            this.closeButton.Text = "Close";
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // beethovenButton
            // 
            this.beethovenButton.Location = new System.Drawing.Point(64, 150);
            this.beethovenButton.Name = "beethovenButton";
            this.beethovenButton.Size = new System.Drawing.Size(75, 23);
            this.beethovenButton.TabIndex = 7;
            this.beethovenButton.Text = "Beethoven";
            this.beethovenButton.UseVisualStyleBackColor = true;
            this.beethovenButton.Click += new System.EventHandler(this.beethovenButton_Click);
            // 
            // piratesButton
            // 
            this.piratesButton.Location = new System.Drawing.Point(169, 149);
            this.piratesButton.Name = "piratesButton";
            this.piratesButton.Size = new System.Drawing.Size(75, 23);
            this.piratesButton.TabIndex = 8;
            this.piratesButton.Text = "He\'s a pirate";
            this.piratesButton.UseVisualStyleBackColor = true;
            this.piratesButton.Click += new System.EventHandler(this.piratesButton_Click);
            // 
            // crazyfrogButton
            // 
            this.crazyfrogButton.Location = new System.Drawing.Point(270, 149);
            this.crazyfrogButton.Name = "crazyfrogButton";
            this.crazyfrogButton.Size = new System.Drawing.Size(75, 23);
            this.crazyfrogButton.TabIndex = 9;
            this.crazyfrogButton.Text = "Crazy frog";
            this.crazyfrogButton.UseVisualStyleBackColor = true;
            this.crazyfrogButton.Click += new System.EventHandler(this.crazyfrogButton_Click);
            // 
            // marioButton
            // 
            this.marioButton.Location = new System.Drawing.Point(64, 203);
            this.marioButton.Name = "marioButton";
            this.marioButton.Size = new System.Drawing.Size(75, 23);
            this.marioButton.TabIndex = 10;
            this.marioButton.Text = "Mario";
            this.marioButton.UseVisualStyleBackColor = true;
            this.marioButton.Click += new System.EventHandler(this.marioButton_Click);
            // 
            // titanicButton
            // 
            this.titanicButton.Location = new System.Drawing.Point(270, 203);
            this.titanicButton.Name = "titanicButton";
            this.titanicButton.Size = new System.Drawing.Size(75, 23);
            this.titanicButton.TabIndex = 11;
            this.titanicButton.Text = "Titanic";
            this.titanicButton.UseVisualStyleBackColor = true;
            this.titanicButton.Click += new System.EventHandler(this.titanicButton_Click);
            // 
            // tempoplusButton
            // 
            this.tempoplusButton.Location = new System.Drawing.Point(64, 270);
            this.tempoplusButton.Name = "tempoplusButton";
            this.tempoplusButton.Size = new System.Drawing.Size(75, 23);
            this.tempoplusButton.TabIndex = 12;
            this.tempoplusButton.Text = "Tempo+";
            this.tempoplusButton.UseVisualStyleBackColor = true;
            this.tempoplusButton.Click += new System.EventHandler(this.tempoplusButton_Click);
            // 
            // tempominusButton
            // 
            this.tempominusButton.Location = new System.Drawing.Point(270, 270);
            this.tempominusButton.Name = "tempominusButton";
            this.tempominusButton.Size = new System.Drawing.Size(75, 23);
            this.tempominusButton.TabIndex = 13;
            this.tempominusButton.Text = "Tempo-";
            this.tempominusButton.UseVisualStyleBackColor = true;
            this.tempominusButton.Click += new System.EventHandler(this.tempominusButton_Click);
            // 
            // tempoequalButton
            // 
            this.tempoequalButton.Location = new System.Drawing.Point(169, 270);
            this.tempoequalButton.Name = "tempoequalButton";
            this.tempoequalButton.Size = new System.Drawing.Size(75, 23);
            this.tempoequalButton.TabIndex = 14;
            this.tempoequalButton.Text = "Tempo=";
            this.tempoequalButton.UseVisualStyleBackColor = true;
            this.tempoequalButton.Click += new System.EventHandler(this.tempoequalButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(398, 436);
            this.Controls.Add(this.tempoequalButton);
            this.Controls.Add(this.tempominusButton);
            this.Controls.Add(this.tempoplusButton);
            this.Controls.Add(this.titanicButton);
            this.Controls.Add(this.marioButton);
            this.Controls.Add(this.crazyfrogButton);
            this.Controls.Add(this.piratesButton);
            this.Controls.Add(this.beethovenButton);
            this.Controls.Add(this.closeButton);
            this.Controls.Add(this.selectButton);
            this.Controls.Add(this.findPorts);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.portsBox);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox portsBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button findPorts;
        private System.Windows.Forms.Button selectButton;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.Button beethovenButton;
        private System.Windows.Forms.Button piratesButton;
        private System.Windows.Forms.Button crazyfrogButton;
        private System.Windows.Forms.Button marioButton;
        private System.Windows.Forms.Button titanicButton;
        private System.Windows.Forms.Button tempoplusButton;
        private System.Windows.Forms.Button tempominusButton;
        private System.Windows.Forms.Button tempoequalButton;
    }
}

