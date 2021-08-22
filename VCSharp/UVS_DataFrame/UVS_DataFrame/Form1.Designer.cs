namespace UVS_DataFrame
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
            this.flip = new System.Windows.Forms.CheckBox();
            this.audio = new System.Windows.Forms.CheckBox();
            this.mirror = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.rotate = new System.Windows.Forms.ComboBox();
            this.scale = new System.Windows.Forms.ComboBox();
            this.acopy = new System.Windows.Forms.Button();
            this.acallback = new System.Windows.Forms.Button();
            this.alock = new System.Windows.Forms.Button();
            this.vlock = new System.Windows.Forms.Button();
            this.vcallback = new System.Windows.Forms.Button();
            this.callback = new System.Windows.Forms.Button();
            this.snapshot = new System.Windows.Forms.Button();
            this.vcopy = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.SuspendLayout();
            // 
            // video
            // 
            this.video.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.video.Location = new System.Drawing.Point(1, 2);
            this.video.Name = "video";
            this.video.Size = new System.Drawing.Size(794, 473);
            this.video.TabIndex = 0;
            // 
            // flip
            // 
            this.flip.AutoSize = true;
            this.flip.Location = new System.Drawing.Point(12, 485);
            this.flip.Name = "flip";
            this.flip.Size = new System.Drawing.Size(120, 16);
            this.flip.TabIndex = 1;
            this.flip.Text = "Video Frame Flip";
            this.flip.UseVisualStyleBackColor = true;
            // 
            // audio
            // 
            this.audio.AutoSize = true;
            this.audio.Location = new System.Drawing.Point(161, 485);
            this.audio.Name = "audio";
            this.audio.Size = new System.Drawing.Size(132, 16);
            this.audio.TabIndex = 2;
            this.audio.Text = "Audio Frame Encode";
            this.audio.UseVisualStyleBackColor = true;
            // 
            // mirror
            // 
            this.mirror.AutoSize = true;
            this.mirror.Location = new System.Drawing.Point(12, 514);
            this.mirror.Name = "mirror";
            this.mirror.Size = new System.Drawing.Size(132, 16);
            this.mirror.TabIndex = 3;
            this.mirror.Text = "Video Frame Mirror";
            this.mirror.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 547);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "Video Rotate";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 572);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "Video Scale";
            // 
            // rotate
            // 
            this.rotate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rotate.FormattingEnabled = true;
            this.rotate.Items.AddRange(new object[] {
            "None",
            "90",
            "180",
            "270"});
            this.rotate.Location = new System.Drawing.Point(109, 543);
            this.rotate.Name = "rotate";
            this.rotate.Size = new System.Drawing.Size(130, 20);
            this.rotate.TabIndex = 6;
            // 
            // scale
            // 
            this.scale.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.scale.FormattingEnabled = true;
            this.scale.Items.AddRange(new object[] {
            "None",
            "640 x 480",
            "3840 x 2160"});
            this.scale.Location = new System.Drawing.Point(109, 569);
            this.scale.Name = "scale";
            this.scale.Size = new System.Drawing.Size(130, 20);
            this.scale.TabIndex = 7;
            // 
            // acopy
            // 
            this.acopy.Location = new System.Drawing.Point(626, 478);
            this.acopy.Name = "acopy";
            this.acopy.Size = new System.Drawing.Size(157, 36);
            this.acopy.TabIndex = 8;
            this.acopy.Text = "Audio Frame Copy";
            this.acopy.UseVisualStyleBackColor = true;
            this.acopy.Click += new System.EventHandler(this.OnAudioCopy);
            // 
            // acallback
            // 
            this.acallback.Location = new System.Drawing.Point(626, 517);
            this.acallback.Name = "acallback";
            this.acallback.Size = new System.Drawing.Size(157, 36);
            this.acallback.TabIndex = 9;
            this.acallback.Text = "Audio Frame Callback";
            this.acallback.UseVisualStyleBackColor = true;
            this.acallback.Click += new System.EventHandler(this.OnAudioCallback);
            // 
            // alock
            // 
            this.alock.Location = new System.Drawing.Point(626, 556);
            this.alock.Name = "alock";
            this.alock.Size = new System.Drawing.Size(157, 36);
            this.alock.TabIndex = 10;
            this.alock.Text = "Audio Frame Lock";
            this.alock.UseVisualStyleBackColor = true;
            this.alock.Click += new System.EventHandler(this.OnAudioLock);
            // 
            // vlock
            // 
            this.vlock.Location = new System.Drawing.Point(440, 556);
            this.vlock.Name = "vlock";
            this.vlock.Size = new System.Drawing.Size(157, 36);
            this.vlock.TabIndex = 13;
            this.vlock.Text = "Video Frame Lock";
            this.vlock.UseVisualStyleBackColor = true;
            this.vlock.Click += new System.EventHandler(this.OnVideoLock);
            // 
            // vcallback
            // 
            this.vcallback.Location = new System.Drawing.Point(440, 517);
            this.vcallback.Name = "vcallback";
            this.vcallback.Size = new System.Drawing.Size(157, 36);
            this.vcallback.TabIndex = 12;
            this.vcallback.Text = "Video Frame Callback";
            this.vcallback.UseVisualStyleBackColor = true;
            this.vcallback.Click += new System.EventHandler(this.OnVideoCallback);
            // 
            // callback
            // 
            this.callback.Location = new System.Drawing.Point(440, 478);
            this.callback.Name = "callback";
            this.callback.Size = new System.Drawing.Size(157, 36);
            this.callback.TabIndex = 11;
            this.callback.Text = "Encode Frame Callback";
            this.callback.UseVisualStyleBackColor = true;
            this.callback.Click += new System.EventHandler(this.OnEncCallback);
            // 
            // snapshot
            // 
            this.snapshot.Location = new System.Drawing.Point(254, 556);
            this.snapshot.Name = "snapshot";
            this.snapshot.Size = new System.Drawing.Size(157, 36);
            this.snapshot.TabIndex = 15;
            this.snapshot.Text = "Video Snapshot";
            this.snapshot.UseVisualStyleBackColor = true;
            this.snapshot.Click += new System.EventHandler(this.OnSnapshot);
            // 
            // vcopy
            // 
            this.vcopy.Location = new System.Drawing.Point(254, 517);
            this.vcopy.Name = "vcopy";
            this.vcopy.Size = new System.Drawing.Size(157, 36);
            this.vcopy.TabIndex = 14;
            this.vcopy.Text = "Video Frame Copy";
            this.vcopy.UseVisualStyleBackColor = true;
            this.vcopy.Click += new System.EventHandler(this.OnVideoCopy);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(795, 594);
            this.Controls.Add(this.snapshot);
            this.Controls.Add(this.vcopy);
            this.Controls.Add(this.vlock);
            this.Controls.Add(this.vcallback);
            this.Controls.Add(this.callback);
            this.Controls.Add(this.alock);
            this.Controls.Add(this.acallback);
            this.Controls.Add(this.acopy);
            this.Controls.Add(this.scale);
            this.Controls.Add(this.rotate);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.mirror);
            this.Controls.Add(this.audio);
            this.Controls.Add(this.flip);
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
        private System.Windows.Forms.CheckBox flip;
        private System.Windows.Forms.CheckBox audio;
        private System.Windows.Forms.CheckBox mirror;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox rotate;
        private System.Windows.Forms.ComboBox scale;
        private System.Windows.Forms.Button acopy;
        private System.Windows.Forms.Button acallback;
        private System.Windows.Forms.Button alock;
        private System.Windows.Forms.Button vlock;
        private System.Windows.Forms.Button vcallback;
        private System.Windows.Forms.Button callback;
        private System.Windows.Forms.Button snapshot;
        private System.Windows.Forms.Button vcopy;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
    }
}

