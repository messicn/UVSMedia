namespace UVS_Device
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
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.video = new System.Windows.Forms.Panel();
            this.status = new System.Windows.Forms.TextBox();
            this.file = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.mode = new System.Windows.Forms.ComboBox();
            this.background = new System.Windows.Forms.Button();
            this.apply = new System.Windows.Forms.Button();
            this.browse = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 405);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Input Status";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Image File";
            // 
            // video
            // 
            this.video.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.video.Location = new System.Drawing.Point(1, 1);
            this.video.Name = "video";
            this.video.Size = new System.Drawing.Size(697, 393);
            this.video.TabIndex = 4;
            // 
            // status
            // 
            this.status.Enabled = false;
            this.status.Location = new System.Drawing.Point(114, 400);
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(174, 21);
            this.status.TabIndex = 5;
            // 
            // file
            // 
            this.file.Location = new System.Drawing.Point(114, 21);
            this.file.Name = "file";
            this.file.Size = new System.Drawing.Size(518, 21);
            this.file.TabIndex = 6;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 7;
            this.label3.Text = "Image Mode";
            // 
            // mode
            // 
            this.mode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.mode.FormattingEnabled = true;
            this.mode.Items.AddRange(new object[] {
            "Stretch",
            "Center"});
            this.mode.Location = new System.Drawing.Point(114, 52);
            this.mode.Name = "mode";
            this.mode.Size = new System.Drawing.Size(127, 20);
            this.mode.TabIndex = 8;
            // 
            // background
            // 
            this.background.Location = new System.Drawing.Point(365, 50);
            this.background.Name = "background";
            this.background.Size = new System.Drawing.Size(116, 23);
            this.background.TabIndex = 9;
            this.background.Text = "Background Color";
            this.background.UseVisualStyleBackColor = true;
            this.background.Click += new System.EventHandler(this.OnColor);
            // 
            // apply
            // 
            this.apply.Location = new System.Drawing.Point(526, 50);
            this.apply.Name = "apply";
            this.apply.Size = new System.Drawing.Size(97, 23);
            this.apply.TabIndex = 10;
            this.apply.Text = "Apply";
            this.apply.UseVisualStyleBackColor = true;
            this.apply.Click += new System.EventHandler(this.OnApply);
            // 
            // browse
            // 
            this.browse.Location = new System.Drawing.Point(638, 21);
            this.browse.Name = "browse";
            this.browse.Size = new System.Drawing.Size(51, 23);
            this.browse.TabIndex = 11;
            this.browse.Text = "...";
            this.browse.UseVisualStyleBackColor = true;
            this.browse.Click += new System.EventHandler(this.OnBrowse);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.apply);
            this.groupBox1.Controls.Add(this.browse);
            this.groupBox1.Controls.Add(this.background);
            this.groupBox1.Controls.Add(this.mode);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.file);
            this.groupBox1.Location = new System.Drawing.Point(1, 431);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(698, 85);
            this.groupBox1.TabIndex = 12;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "No Signal Setting(Valid after device reopen)";
            // 
            // timer1
            // 
            this.timer1.Interval = 300;
            this.timer1.Tick += new System.EventHandler(this.OnTimer);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(699, 512);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.status);
            this.Controls.Add(this.video);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OnClosed);
            this.Load += new System.EventHandler(this.Onload);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel video;
        private System.Windows.Forms.TextBox status;
        private System.Windows.Forms.TextBox file;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox mode;
        private System.Windows.Forms.Button background;
        private System.Windows.Forms.Button apply;
        private System.Windows.Forms.Button browse;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ColorDialog colorDialog1;
    }
}

