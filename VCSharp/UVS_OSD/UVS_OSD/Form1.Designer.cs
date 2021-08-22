namespace UVS_OSD
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
            this.timeosd = new System.Windows.Forms.CheckBox();
            this.textosd = new System.Windows.Forms.CheckBox();
            this.imgosd = new System.Windows.Forms.CheckBox();
            this.rectosd = new System.Windows.Forms.CheckBox();
            this.ellipseosd = new System.Windows.Forms.CheckBox();
            this.lineosd = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.date = new System.Windows.Forms.ComboBox();
            this.week = new System.Windows.Forms.ComboBox();
            this.hours = new System.Windows.Forms.ComboBox();
            this.font = new System.Windows.Forms.Button();
            this.text = new System.Windows.Forms.TextBox();
            this.image = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.rectstyle = new System.Windows.Forms.ComboBox();
            this.ellipsestyle = new System.Windows.Forms.ComboBox();
            this.multiline = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.osd = new System.Windows.Forms.ComboBox();
            this.control = new System.Windows.Forms.ComboBox();
            this.browse = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.fontDialog1 = new System.Windows.Forms.FontDialog();
            this.SuspendLayout();
            // 
            // video
            // 
            this.video.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.video.Location = new System.Drawing.Point(2, 1);
            this.video.Name = "video";
            this.video.Size = new System.Drawing.Size(733, 411);
            this.video.TabIndex = 0;
            // 
            // timeosd
            // 
            this.timeosd.AutoSize = true;
            this.timeosd.Location = new System.Drawing.Point(27, 415);
            this.timeosd.Name = "timeosd";
            this.timeosd.Size = new System.Drawing.Size(72, 16);
            this.timeosd.TabIndex = 1;
            this.timeosd.Text = "Time OSD";
            this.timeosd.UseVisualStyleBackColor = true;
            this.timeosd.Click += new System.EventHandler(this.OnTimeosd);
            // 
            // textosd
            // 
            this.textosd.AutoSize = true;
            this.textosd.Location = new System.Drawing.Point(27, 441);
            this.textosd.Name = "textosd";
            this.textosd.Size = new System.Drawing.Size(72, 16);
            this.textosd.TabIndex = 2;
            this.textosd.Text = "Text OSD";
            this.textosd.UseVisualStyleBackColor = true;
            this.textosd.Click += new System.EventHandler(this.OnTextosd);
            // 
            // imgosd
            // 
            this.imgosd.AutoSize = true;
            this.imgosd.Location = new System.Drawing.Point(27, 467);
            this.imgosd.Name = "imgosd";
            this.imgosd.Size = new System.Drawing.Size(78, 16);
            this.imgosd.TabIndex = 3;
            this.imgosd.Text = "Image OSD";
            this.imgosd.UseVisualStyleBackColor = true;
            this.imgosd.Click += new System.EventHandler(this.OnImageosd);
            // 
            // rectosd
            // 
            this.rectosd.AutoSize = true;
            this.rectosd.Location = new System.Drawing.Point(27, 493);
            this.rectosd.Name = "rectosd";
            this.rectosd.Size = new System.Drawing.Size(72, 16);
            this.rectosd.TabIndex = 4;
            this.rectosd.Text = "Rect OSD";
            this.rectosd.UseVisualStyleBackColor = true;
            this.rectosd.Click += new System.EventHandler(this.OnRectosd);
            // 
            // ellipseosd
            // 
            this.ellipseosd.AutoSize = true;
            this.ellipseosd.Location = new System.Drawing.Point(27, 519);
            this.ellipseosd.Name = "ellipseosd";
            this.ellipseosd.Size = new System.Drawing.Size(90, 16);
            this.ellipseosd.TabIndex = 5;
            this.ellipseosd.Text = "Ellipse OSD";
            this.ellipseosd.UseVisualStyleBackColor = true;
            this.ellipseosd.Click += new System.EventHandler(this.OnEllipseosd);
            // 
            // lineosd
            // 
            this.lineosd.AutoSize = true;
            this.lineosd.Location = new System.Drawing.Point(27, 545);
            this.lineosd.Name = "lineosd";
            this.lineosd.Size = new System.Drawing.Size(72, 16);
            this.lineosd.TabIndex = 6;
            this.lineosd.Text = "Line OSD";
            this.lineosd.UseVisualStyleBackColor = true;
            this.lineosd.Click += new System.EventHandler(this.OnLineosd);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(129, 419);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "Date";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(307, 419);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "Week";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(478, 419);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "Time";
            // 
            // date
            // 
            this.date.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.date.FormattingEnabled = true;
            this.date.Items.AddRange(new object[] {
            "YY-MM-DD",
            "MM-DD-YY",
            "DD-MM-YY",
            "Mn DD YY"});
            this.date.Location = new System.Drawing.Point(169, 415);
            this.date.Name = "date";
            this.date.Size = new System.Drawing.Size(121, 20);
            this.date.TabIndex = 10;
            this.date.SelectedIndexChanged += new System.EventHandler(this.OnDate);
            // 
            // week
            // 
            this.week.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.week.FormattingEnabled = true;
            this.week.Items.AddRange(new object[] {
            "None",
            "Full Name",
            "Short Name"});
            this.week.Location = new System.Drawing.Point(346, 415);
            this.week.Name = "week";
            this.week.Size = new System.Drawing.Size(121, 20);
            this.week.TabIndex = 11;
            this.week.SelectedIndexChanged += new System.EventHandler(this.OnWeek);
            // 
            // hours
            // 
            this.hours.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.hours.FormattingEnabled = true;
            this.hours.Items.AddRange(new object[] {
            "24 Hour",
            "12 Hour",
            "12 Hour AMPM"});
            this.hours.Location = new System.Drawing.Point(521, 415);
            this.hours.Name = "hours";
            this.hours.Size = new System.Drawing.Size(121, 20);
            this.hours.TabIndex = 12;
            this.hours.SelectedIndexChanged += new System.EventHandler(this.OnHours);
            // 
            // font
            // 
            this.font.Location = new System.Drawing.Point(651, 413);
            this.font.Name = "font";
            this.font.Size = new System.Drawing.Size(77, 24);
            this.font.TabIndex = 13;
            this.font.Text = "Font";
            this.font.UseVisualStyleBackColor = true;
            this.font.Click += new System.EventHandler(this.OnFont);
            // 
            // text
            // 
            this.text.Location = new System.Drawing.Point(131, 439);
            this.text.Name = "text";
            this.text.Size = new System.Drawing.Size(511, 21);
            this.text.TabIndex = 14;
            this.text.Text = "UVS Text Sample";
            // 
            // image
            // 
            this.image.Location = new System.Drawing.Point(131, 465);
            this.image.Name = "image";
            this.image.Size = new System.Drawing.Size(511, 21);
            this.image.TabIndex = 15;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(129, 497);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 12);
            this.label4.TabIndex = 16;
            this.label4.Text = "Style";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(129, 523);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 17;
            this.label5.Text = "Style";
            // 
            // rectstyle
            // 
            this.rectstyle.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rectstyle.FormattingEnabled = true;
            this.rectstyle.Items.AddRange(new object[] {
            "Solid",
            "Dash",
            "Dot",
            "Dash Dot"});
            this.rectstyle.Location = new System.Drawing.Point(181, 493);
            this.rectstyle.Name = "rectstyle";
            this.rectstyle.Size = new System.Drawing.Size(155, 20);
            this.rectstyle.TabIndex = 18;
            this.rectstyle.SelectedIndexChanged += new System.EventHandler(this.OnRectstyle);
            // 
            // ellipsestyle
            // 
            this.ellipsestyle.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ellipsestyle.FormattingEnabled = true;
            this.ellipsestyle.Items.AddRange(new object[] {
            "Solid",
            "Dash",
            "Dot",
            "Dash Dot"});
            this.ellipsestyle.Location = new System.Drawing.Point(181, 519);
            this.ellipsestyle.Name = "ellipsestyle";
            this.ellipsestyle.Size = new System.Drawing.Size(155, 20);
            this.ellipsestyle.TabIndex = 19;
            this.ellipsestyle.SelectedIndexChanged += new System.EventHandler(this.OnEllipsestyle);
            // 
            // multiline
            // 
            this.multiline.AutoSize = true;
            this.multiline.Location = new System.Drawing.Point(394, 493);
            this.multiline.Name = "multiline";
            this.multiline.Size = new System.Drawing.Size(156, 16);
            this.multiline.TabIndex = 20;
            this.multiline.Text = "Text OSD Multiple Line";
            this.multiline.UseVisualStyleBackColor = true;
            this.multiline.Click += new System.EventHandler(this.OnMultiLine);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(394, 522);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 21;
            this.label6.Text = "OSD Select";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(394, 548);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(71, 12);
            this.label7.TabIndex = 22;
            this.label7.Text = "OSD Control";
            // 
            // osd
            // 
            this.osd.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.osd.FormattingEnabled = true;
            this.osd.Items.AddRange(new object[] {
            "Time OSD",
            "Text OSD",
            "Image OSD",
            "Rect OSD",
            "Ellipse OSD"});
            this.osd.Location = new System.Drawing.Point(477, 519);
            this.osd.Name = "osd";
            this.osd.Size = new System.Drawing.Size(165, 20);
            this.osd.TabIndex = 23;
            this.osd.SelectedIndexChanged += new System.EventHandler(this.OnSelect);
            // 
            // control
            // 
            this.control.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.control.FormattingEnabled = true;
            this.control.Items.AddRange(new object[] {
            "None",
            "Blink",
            "Roll",
            "Scroll 1",
            "Scroll 2",
            "Rect Clean",
            "Fade"});
            this.control.Location = new System.Drawing.Point(477, 545);
            this.control.Name = "control";
            this.control.Size = new System.Drawing.Size(165, 20);
            this.control.TabIndex = 24;
            this.control.SelectedIndexChanged += new System.EventHandler(this.OnControl);
            // 
            // browse
            // 
            this.browse.Location = new System.Drawing.Point(651, 463);
            this.browse.Name = "browse";
            this.browse.Size = new System.Drawing.Size(77, 24);
            this.browse.TabIndex = 25;
            this.browse.Text = "...";
            this.browse.UseVisualStyleBackColor = true;
            this.browse.Click += new System.EventHandler(this.OnBrowse);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.OnTimer);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(737, 569);
            this.Controls.Add(this.browse);
            this.Controls.Add(this.control);
            this.Controls.Add(this.osd);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.multiline);
            this.Controls.Add(this.ellipsestyle);
            this.Controls.Add(this.rectstyle);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.image);
            this.Controls.Add(this.text);
            this.Controls.Add(this.font);
            this.Controls.Add(this.hours);
            this.Controls.Add(this.week);
            this.Controls.Add(this.date);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lineosd);
            this.Controls.Add(this.ellipseosd);
            this.Controls.Add(this.rectosd);
            this.Controls.Add(this.imgosd);
            this.Controls.Add(this.textosd);
            this.Controls.Add(this.timeosd);
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
        private System.Windows.Forms.CheckBox timeosd;
        private System.Windows.Forms.CheckBox textosd;
        private System.Windows.Forms.CheckBox imgosd;
        private System.Windows.Forms.CheckBox rectosd;
        private System.Windows.Forms.CheckBox ellipseosd;
        private System.Windows.Forms.CheckBox lineosd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox date;
        private System.Windows.Forms.ComboBox week;
        private System.Windows.Forms.ComboBox hours;
        private System.Windows.Forms.Button font;
        private System.Windows.Forms.TextBox text;
        private System.Windows.Forms.TextBox image;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox rectstyle;
        private System.Windows.Forms.ComboBox ellipsestyle;
        private System.Windows.Forms.CheckBox multiline;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox osd;
        private System.Windows.Forms.ComboBox control;
        private System.Windows.Forms.Button browse;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.FontDialog fontDialog1;
    }
}

