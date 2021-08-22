namespace UVS_Preview
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
            this.video = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.acap = new System.Windows.Forms.ComboBox();
            this.vcap = new System.Windows.Forms.ComboBox();
            this.arender = new System.Windows.Forms.ComboBox();
            this.vrender = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.mirror = new System.Windows.Forms.CheckBox();
            this.flip = new System.Windows.Forms.CheckBox();
            this.mute = new System.Windows.Forms.CheckBox();
            this.fullscreen = new System.Windows.Forms.Button();
            this.zoomin = new System.Windows.Forms.Button();
            this.freeze = new System.Windows.Forms.Button();
            this.zoomout = new System.Windows.Forms.Button();
            this.brightness = new System.Windows.Forms.TrackBar();
            this.contrast = new System.Windows.Forms.TrackBar();
            this.saturation = new System.Windows.Forms.TrackBar();
            this.gamma = new System.Windows.Forms.TrackBar();
            this.volume = new System.Windows.Forms.TrackBar();
            this.balance = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.brightness)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.contrast)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.saturation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gamma)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.volume)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.balance)).BeginInit();
            this.SuspendLayout();
            // 
            // video
            // 
            this.video.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.video.Location = new System.Drawing.Point(2, 2);
            this.video.Name = "video";
            this.video.Size = new System.Drawing.Size(728, 425);
            this.video.TabIndex = 0;
            this.video.Click += new System.EventHandler(this.OnClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 434);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Audio Capture";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(383, 434);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Video Capture";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 459);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(89, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "Audio Renderer";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(383, 459);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "Video Renderer";
            // 
            // acap
            // 
            this.acap.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.acap.FormattingEnabled = true;
            this.acap.Location = new System.Drawing.Point(137, 432);
            this.acap.Name = "acap";
            this.acap.Size = new System.Drawing.Size(223, 20);
            this.acap.TabIndex = 5;
            this.acap.SelectedIndexChanged += new System.EventHandler(this.OnChanged);
            // 
            // vcap
            // 
            this.vcap.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.vcap.FormattingEnabled = true;
            this.vcap.Location = new System.Drawing.Point(484, 432);
            this.vcap.Name = "vcap";
            this.vcap.Size = new System.Drawing.Size(225, 20);
            this.vcap.TabIndex = 6;
            this.vcap.SelectedIndexChanged += new System.EventHandler(this.OnChanged);
            // 
            // arender
            // 
            this.arender.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.arender.FormattingEnabled = true;
            this.arender.Location = new System.Drawing.Point(137, 457);
            this.arender.Name = "arender";
            this.arender.Size = new System.Drawing.Size(223, 20);
            this.arender.TabIndex = 7;
            this.arender.SelectedIndexChanged += new System.EventHandler(this.OnChanged);
            // 
            // vrender
            // 
            this.vrender.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.vrender.FormattingEnabled = true;
            this.vrender.Items.AddRange(new object[] {
            "DirectX 3D",
            "Direct Draw"});
            this.vrender.Location = new System.Drawing.Point(484, 455);
            this.vrender.Name = "vrender";
            this.vrender.Size = new System.Drawing.Size(225, 20);
            this.vrender.TabIndex = 8;
            this.vrender.SelectedIndexChanged += new System.EventHandler(this.OnPreview);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(19, 487);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "Brightness";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 516);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "Saturation";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(383, 487);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = "Contrast";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(383, 516);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 12);
            this.label8.TabIndex = 12;
            this.label8.Text = "Gamma";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(383, 545);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 13;
            this.label9.Text = "Balance";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(19, 545);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 12);
            this.label10.TabIndex = 14;
            this.label10.Text = "Volume";
            // 
            // mirror
            // 
            this.mirror.AutoSize = true;
            this.mirror.Location = new System.Drawing.Point(19, 573);
            this.mirror.Name = "mirror";
            this.mirror.Size = new System.Drawing.Size(96, 16);
            this.mirror.TabIndex = 16;
            this.mirror.Text = "Video Mirror";
            this.mirror.UseVisualStyleBackColor = true;
            // 
            // flip
            // 
            this.flip.AutoSize = true;
            this.flip.Location = new System.Drawing.Point(137, 573);
            this.flip.Name = "flip";
            this.flip.Size = new System.Drawing.Size(84, 16);
            this.flip.TabIndex = 17;
            this.flip.Text = "Video Flip";
            this.flip.UseVisualStyleBackColor = true;
            // 
            // mute
            // 
            this.mute.AutoSize = true;
            this.mute.Location = new System.Drawing.Point(19, 596);
            this.mute.Name = "mute";
            this.mute.Size = new System.Drawing.Size(84, 16);
            this.mute.TabIndex = 18;
            this.mute.Text = "Audio Mute";
            this.mute.UseVisualStyleBackColor = true;
            // 
            // fullscreen
            // 
            this.fullscreen.Location = new System.Drawing.Point(242, 575);
            this.fullscreen.Name = "fullscreen";
            this.fullscreen.Size = new System.Drawing.Size(108, 33);
            this.fullscreen.TabIndex = 19;
            this.fullscreen.Text = "Full Screen";
            this.fullscreen.UseVisualStyleBackColor = true;
            this.fullscreen.Click += new System.EventHandler(this.OnFullscreen);
            // 
            // zoomin
            // 
            this.zoomin.Location = new System.Drawing.Point(367, 575);
            this.zoomin.Name = "zoomin";
            this.zoomin.Size = new System.Drawing.Size(108, 33);
            this.zoomin.TabIndex = 20;
            this.zoomin.Text = "Zoom In";
            this.zoomin.UseVisualStyleBackColor = true;
            this.zoomin.Click += new System.EventHandler(this.OnZoomin);
            // 
            // freeze
            // 
            this.freeze.Location = new System.Drawing.Point(492, 575);
            this.freeze.Name = "freeze";
            this.freeze.Size = new System.Drawing.Size(108, 33);
            this.freeze.TabIndex = 21;
            this.freeze.Text = "Display Freeze";
            this.freeze.UseVisualStyleBackColor = true;
            this.freeze.Click += new System.EventHandler(this.OnFreeze);
            // 
            // zoomout
            // 
            this.zoomout.Location = new System.Drawing.Point(617, 575);
            this.zoomout.Name = "zoomout";
            this.zoomout.Size = new System.Drawing.Size(108, 33);
            this.zoomout.TabIndex = 22;
            this.zoomout.Text = "Zoom Out";
            this.zoomout.UseVisualStyleBackColor = true;
            this.zoomout.Click += new System.EventHandler(this.OnZoomout);
            // 
            // brightness
            // 
            this.brightness.AutoSize = false;
            this.brightness.Location = new System.Drawing.Point(130, 484);
            this.brightness.Name = "brightness";
            this.brightness.Size = new System.Drawing.Size(230, 29);
            this.brightness.TabIndex = 23;
            this.brightness.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // contrast
            // 
            this.contrast.AutoSize = false;
            this.contrast.Location = new System.Drawing.Point(475, 484);
            this.contrast.Name = "contrast";
            this.contrast.Size = new System.Drawing.Size(230, 29);
            this.contrast.TabIndex = 24;
            this.contrast.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // saturation
            // 
            this.saturation.AutoSize = false;
            this.saturation.Location = new System.Drawing.Point(130, 510);
            this.saturation.Name = "saturation";
            this.saturation.Size = new System.Drawing.Size(230, 29);
            this.saturation.TabIndex = 25;
            this.saturation.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // gamma
            // 
            this.gamma.AutoSize = false;
            this.gamma.Location = new System.Drawing.Point(475, 510);
            this.gamma.Name = "gamma";
            this.gamma.Size = new System.Drawing.Size(230, 29);
            this.gamma.TabIndex = 26;
            this.gamma.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // volume
            // 
            this.volume.AutoSize = false;
            this.volume.Location = new System.Drawing.Point(130, 539);
            this.volume.Maximum = 100;
            this.volume.Name = "volume";
            this.volume.Size = new System.Drawing.Size(230, 29);
            this.volume.TabIndex = 27;
            this.volume.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // balance
            // 
            this.balance.AutoSize = false;
            this.balance.Location = new System.Drawing.Point(475, 539);
            this.balance.Maximum = 100;
            this.balance.Minimum = -100;
            this.balance.Name = "balance";
            this.balance.Size = new System.Drawing.Size(230, 29);
            this.balance.TabIndex = 28;
            this.balance.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(732, 617);
            this.Controls.Add(this.balance);
            this.Controls.Add(this.volume);
            this.Controls.Add(this.gamma);
            this.Controls.Add(this.saturation);
            this.Controls.Add(this.contrast);
            this.Controls.Add(this.brightness);
            this.Controls.Add(this.zoomout);
            this.Controls.Add(this.freeze);
            this.Controls.Add(this.zoomin);
            this.Controls.Add(this.fullscreen);
            this.Controls.Add(this.mute);
            this.Controls.Add(this.flip);
            this.Controls.Add(this.mirror);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.vrender);
            this.Controls.Add(this.arender);
            this.Controls.Add(this.vcap);
            this.Controls.Add(this.acap);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.video);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OnClosed);
            this.Load += new System.EventHandler(this.OnLoad);
            ((System.ComponentModel.ISupportInitialize)(this.brightness)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.contrast)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.saturation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gamma)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.volume)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.balance)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel video;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox acap;
        private System.Windows.Forms.ComboBox vcap;
        private System.Windows.Forms.ComboBox arender;
        private System.Windows.Forms.ComboBox vrender;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox mirror;
        private System.Windows.Forms.CheckBox flip;
        private System.Windows.Forms.CheckBox mute;
        private System.Windows.Forms.Button fullscreen;
        private System.Windows.Forms.Button zoomin;
        private System.Windows.Forms.Button freeze;
        private System.Windows.Forms.Button zoomout;
        private System.Windows.Forms.TrackBar brightness;
        private System.Windows.Forms.TrackBar contrast;
        private System.Windows.Forms.TrackBar saturation;
        private System.Windows.Forms.TrackBar gamma;
        private System.Windows.Forms.TrackBar volume;
        private System.Windows.Forms.TrackBar balance;
    }
}

