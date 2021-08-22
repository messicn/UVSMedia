namespace UVS_Rec
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
            this.video = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.venc = new System.Windows.Forms.ComboBox();
            this.encusage = new System.Windows.Forms.ComboBox();
            this.framerate = new System.Windows.Forms.ComboBox();
            this.crop = new System.Windows.Forms.ComboBox();
            this.scale = new System.Windows.Forms.ComboBox();
            this.filedur = new System.Windows.Forms.ComboBox();
            this.filesz = new System.Windows.Forms.ComboBox();
            this.scaleusage = new System.Windows.Forms.ComboBox();
            this.rc = new System.Windows.Forms.ComboBox();
            this.maxbitrate = new System.Windows.Forms.ComboBox();
            this.encbitrate = new System.Windows.Forms.ComboBox();
            this.aenc = new System.Windows.Forms.ComboBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.maindir = new System.Windows.Forms.TextBox();
            this.subdir = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.status = new System.Windows.Forms.TextBox();
            this.recstart = new System.Windows.Forms.Button();
            this.recpause = new System.Windows.Forms.Button();
            this.mainbrowse = new System.Windows.Forms.Button();
            this.subbrowse = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.SuspendLayout();
            // 
            // video
            // 
            this.video.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.video.Location = new System.Drawing.Point(2, 3);
            this.video.Name = "video";
            this.video.Size = new System.Drawing.Size(725, 424);
            this.video.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 437);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Video Encoder";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 461);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Encode Usage";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 485);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(107, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "Encode Frame Rate";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 509);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "Video Crop";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(19, 533);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 12);
            this.label5.TabIndex = 5;
            this.label5.Text = "Video Scale";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 557);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(83, 12);
            this.label6.TabIndex = 6;
            this.label6.Text = "File Duration";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(373, 557);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 12;
            this.label7.Text = "File Size";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(373, 533);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(71, 12);
            this.label8.TabIndex = 11;
            this.label8.Text = "Scale Usage";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(373, 509);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(95, 12);
            this.label9.TabIndex = 10;
            this.label9.Text = "Bitrate Control";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(373, 485);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(113, 12);
            this.label10.TabIndex = 9;
            this.label10.Text = "Encode Max Bitrate";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(373, 461);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(89, 12);
            this.label11.TabIndex = 8;
            this.label11.Text = "Encode Bitrate";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(373, 437);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(83, 12);
            this.label12.TabIndex = 7;
            this.label12.Text = "Audio Encoder";
            // 
            // venc
            // 
            this.venc.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.venc.FormattingEnabled = true;
            this.venc.Items.AddRange(new object[] {
            "Intel GPU H.264",
            "Intel GPU H.265",
            "Nvidia GPU H.264",
            "Nvidia GPU H.265",
            "Software H.264"});
            this.venc.Location = new System.Drawing.Point(140, 432);
            this.venc.Name = "venc";
            this.venc.Size = new System.Drawing.Size(214, 20);
            this.venc.TabIndex = 13;
            // 
            // encusage
            // 
            this.encusage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.encusage.FormattingEnabled = true;
            this.encusage.Items.AddRange(new object[] {
            "High Performance",
            "Balance",
            "High Quality"});
            this.encusage.Location = new System.Drawing.Point(140, 456);
            this.encusage.Name = "encusage";
            this.encusage.Size = new System.Drawing.Size(214, 20);
            this.encusage.TabIndex = 14;
            // 
            // framerate
            // 
            this.framerate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.framerate.FormattingEnabled = true;
            this.framerate.Location = new System.Drawing.Point(140, 480);
            this.framerate.Name = "framerate";
            this.framerate.Size = new System.Drawing.Size(214, 20);
            this.framerate.TabIndex = 15;
            // 
            // crop
            // 
            this.crop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.crop.FormattingEnabled = true;
            this.crop.Items.AddRange(new object[] {
            "None",
            "640 x 480",
            "1280 x 720"});
            this.crop.Location = new System.Drawing.Point(140, 504);
            this.crop.Name = "crop";
            this.crop.Size = new System.Drawing.Size(214, 20);
            this.crop.TabIndex = 16;
            // 
            // scale
            // 
            this.scale.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.scale.FormattingEnabled = true;
            this.scale.Items.AddRange(new object[] {
            "None",
            "640 x 480",
            "1920 x 1080"});
            this.scale.Location = new System.Drawing.Point(140, 528);
            this.scale.Name = "scale";
            this.scale.Size = new System.Drawing.Size(214, 20);
            this.scale.TabIndex = 17;
            // 
            // filedur
            // 
            this.filedur.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.filedur.FormattingEnabled = true;
            this.filedur.Items.AddRange(new object[] {
            "None",
            "1min",
            "5min",
            "15min"});
            this.filedur.Location = new System.Drawing.Point(140, 552);
            this.filedur.Name = "filedur";
            this.filedur.Size = new System.Drawing.Size(214, 20);
            this.filedur.TabIndex = 18;
            // 
            // filesz
            // 
            this.filesz.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.filesz.FormattingEnabled = true;
            this.filesz.Items.AddRange(new object[] {
            "None",
            "128MB",
            "256MB",
            "512MB"});
            this.filesz.Location = new System.Drawing.Point(497, 552);
            this.filesz.Name = "filesz";
            this.filesz.Size = new System.Drawing.Size(214, 20);
            this.filesz.TabIndex = 24;
            // 
            // scaleusage
            // 
            this.scaleusage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.scaleusage.FormattingEnabled = true;
            this.scaleusage.Items.AddRange(new object[] {
            "High Performance",
            "Balance",
            "Quality",
            "High Quality"});
            this.scaleusage.Location = new System.Drawing.Point(497, 528);
            this.scaleusage.Name = "scaleusage";
            this.scaleusage.Size = new System.Drawing.Size(214, 20);
            this.scaleusage.TabIndex = 23;
            // 
            // rc
            // 
            this.rc.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rc.FormattingEnabled = true;
            this.rc.Items.AddRange(new object[] {
            "VBR",
            "CBR",
            "CQP",
            "AVBR"});
            this.rc.Location = new System.Drawing.Point(497, 504);
            this.rc.Name = "rc";
            this.rc.Size = new System.Drawing.Size(214, 20);
            this.rc.TabIndex = 22;
            // 
            // maxbitrate
            // 
            this.maxbitrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.maxbitrate.FormattingEnabled = true;
            this.maxbitrate.Items.AddRange(new object[] {
            "8000Kbps",
            "12000Kbps"});
            this.maxbitrate.Location = new System.Drawing.Point(497, 480);
            this.maxbitrate.Name = "maxbitrate";
            this.maxbitrate.Size = new System.Drawing.Size(214, 20);
            this.maxbitrate.TabIndex = 21;
            // 
            // encbitrate
            // 
            this.encbitrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.encbitrate.FormattingEnabled = true;
            this.encbitrate.Items.AddRange(new object[] {
            "4000Kbps",
            "8000Kbps",
            "10000Kbps"});
            this.encbitrate.Location = new System.Drawing.Point(497, 456);
            this.encbitrate.Name = "encbitrate";
            this.encbitrate.Size = new System.Drawing.Size(214, 20);
            this.encbitrate.TabIndex = 20;
            // 
            // aenc
            // 
            this.aenc.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.aenc.FormattingEnabled = true;
            this.aenc.Items.AddRange(new object[] {
            "None",
            "AAC",
            "MP3"});
            this.aenc.Location = new System.Drawing.Point(497, 432);
            this.aenc.Name = "aenc";
            this.aenc.Size = new System.Drawing.Size(214, 20);
            this.aenc.TabIndex = 19;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(19, 585);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(95, 12);
            this.label13.TabIndex = 25;
            this.label13.Text = "Main Stream Rec";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(19, 611);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(89, 12);
            this.label14.TabIndex = 26;
            this.label14.Text = "Sub Stream Rec";
            // 
            // maindir
            // 
            this.maindir.Location = new System.Drawing.Point(140, 579);
            this.maindir.Name = "maindir";
            this.maindir.Size = new System.Drawing.Size(507, 21);
            this.maindir.TabIndex = 27;
            // 
            // subdir
            // 
            this.subdir.Location = new System.Drawing.Point(140, 605);
            this.subdir.Name = "subdir";
            this.subdir.Size = new System.Drawing.Size(507, 21);
            this.subdir.TabIndex = 28;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(19, 646);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(83, 12);
            this.label15.TabIndex = 29;
            this.label15.Text = "Encode Status";
            // 
            // status
            // 
            this.status.Location = new System.Drawing.Point(140, 631);
            this.status.Multiline = true;
            this.status.Name = "status";
            this.status.ReadOnly = true;
            this.status.Size = new System.Drawing.Size(189, 40);
            this.status.TabIndex = 30;
            // 
            // recstart
            // 
            this.recstart.Location = new System.Drawing.Point(377, 634);
            this.recstart.Name = "recstart";
            this.recstart.Size = new System.Drawing.Size(117, 37);
            this.recstart.TabIndex = 31;
            this.recstart.Text = "Record Start";
            this.recstart.UseVisualStyleBackColor = true;
            this.recstart.Click += new System.EventHandler(this.OnStart);
            // 
            // recpause
            // 
            this.recpause.Location = new System.Drawing.Point(530, 634);
            this.recpause.Name = "recpause";
            this.recpause.Size = new System.Drawing.Size(117, 37);
            this.recpause.TabIndex = 32;
            this.recpause.Text = "Record Pause";
            this.recpause.UseVisualStyleBackColor = true;
            this.recpause.Click += new System.EventHandler(this.OnPause);
            // 
            // mainbrowse
            // 
            this.mainbrowse.Location = new System.Drawing.Point(653, 575);
            this.mainbrowse.Name = "mainbrowse";
            this.mainbrowse.Size = new System.Drawing.Size(58, 25);
            this.mainbrowse.TabIndex = 33;
            this.mainbrowse.Text = "...";
            this.mainbrowse.UseVisualStyleBackColor = true;
            this.mainbrowse.Click += new System.EventHandler(this.OnMainBrowse);
            // 
            // subbrowse
            // 
            this.subbrowse.Location = new System.Drawing.Point(653, 605);
            this.subbrowse.Name = "subbrowse";
            this.subbrowse.Size = new System.Drawing.Size(58, 25);
            this.subbrowse.TabIndex = 34;
            this.subbrowse.Text = "...";
            this.subbrowse.UseVisualStyleBackColor = true;
            this.subbrowse.Click += new System.EventHandler(this.OnSubBrowse);
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.OnTimer);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(729, 674);
            this.Controls.Add(this.subbrowse);
            this.Controls.Add(this.mainbrowse);
            this.Controls.Add(this.recpause);
            this.Controls.Add(this.recstart);
            this.Controls.Add(this.status);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.subdir);
            this.Controls.Add(this.maindir);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.filesz);
            this.Controls.Add(this.scaleusage);
            this.Controls.Add(this.rc);
            this.Controls.Add(this.maxbitrate);
            this.Controls.Add(this.encbitrate);
            this.Controls.Add(this.aenc);
            this.Controls.Add(this.filedur);
            this.Controls.Add(this.scale);
            this.Controls.Add(this.crop);
            this.Controls.Add(this.framerate);
            this.Controls.Add(this.encusage);
            this.Controls.Add(this.venc);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.video);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OnClosed);
            this.Load += new System.EventHandler(this.OnLoad);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel video;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ComboBox venc;
        private System.Windows.Forms.ComboBox encusage;
        private System.Windows.Forms.ComboBox framerate;
        private System.Windows.Forms.ComboBox crop;
        private System.Windows.Forms.ComboBox scale;
        private System.Windows.Forms.ComboBox filedur;
        private System.Windows.Forms.ComboBox filesz;
        private System.Windows.Forms.ComboBox scaleusage;
        private System.Windows.Forms.ComboBox rc;
        private System.Windows.Forms.ComboBox maxbitrate;
        private System.Windows.Forms.ComboBox encbitrate;
        private System.Windows.Forms.ComboBox aenc;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox maindir;
        private System.Windows.Forms.TextBox subdir;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox status;
        private System.Windows.Forms.Button recstart;
        private System.Windows.Forms.Button recpause;
        private System.Windows.Forms.Button mainbrowse;
        private System.Windows.Forms.Button subbrowse;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
    }
}

