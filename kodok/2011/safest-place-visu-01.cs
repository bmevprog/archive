namespace SafestPlace_visu
{
    partial class FormVisu
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormVisu));
			this.picField = new System.Windows.Forms.PictureBox();
			this.btnClear = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.togglePerPixel = new System.Windows.Forms.CheckBox();
			this.btnRegu2 = new System.Windows.Forms.Button();
			this.btnRegu1 = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.picField)).BeginInit();
			this.SuspendLayout();
			// 
			// picField
			// 
			this.picField.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.picField.Location = new System.Drawing.Point(12, 12);
			this.picField.Name = "picField";
			this.picField.Size = new System.Drawing.Size(610, 610);
			this.picField.TabIndex = 0;
			this.picField.TabStop = false;
			this.picField.MouseMove += new System.Windows.Forms.MouseEventHandler(this.picField_MouseMove);
			this.picField.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picField_MouseDown);
			this.picField.Paint += new System.Windows.Forms.PaintEventHandler(this.picField_Paint);
			this.picField.MouseUp += new System.Windows.Forms.MouseEventHandler(this.picField_MouseUp);
			// 
			// btnClear
			// 
			this.btnClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnClear.Location = new System.Drawing.Point(628, 585);
			this.btnClear.Name = "btnClear";
			this.btnClear.Size = new System.Drawing.Size(150, 37);
			this.btnClear.TabIndex = 1;
			this.btnClear.Text = "Clear all points";
			this.btnClear.UseVisualStyleBackColor = true;
			this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
			// 
			// label1
			// 
			this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.label1.Location = new System.Drawing.Point(628, 163);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(150, 271);
			this.label1.TabIndex = 2;
			this.label1.Text = resources.GetString("label1.Text");
			// 
			// togglePerPixel
			// 
			this.togglePerPixel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.togglePerPixel.Appearance = System.Windows.Forms.Appearance.Button;
			this.togglePerPixel.Location = new System.Drawing.Point(628, 437);
			this.togglePerPixel.Name = "togglePerPixel";
			this.togglePerPixel.Size = new System.Drawing.Size(150, 36);
			this.togglePerPixel.TabIndex = 4;
			this.togglePerPixel.Text = "Show per-pixel distances";
			this.togglePerPixel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.togglePerPixel.UseVisualStyleBackColor = true;
			this.togglePerPixel.CheckedChanged += new System.EventHandler(this.togglePerPixel_CheckedChanged);
			// 
			// btnRegu2
			// 
			this.btnRegu2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnRegu2.Location = new System.Drawing.Point(628, 542);
			this.btnRegu2.Name = "btnRegu2";
			this.btnRegu2.Size = new System.Drawing.Size(150, 37);
			this.btnRegu2.TabIndex = 5;
			this.btnRegu2.Text = "Regular layout #2";
			this.btnRegu2.UseVisualStyleBackColor = true;
			this.btnRegu2.Click += new System.EventHandler(this.btnRegu2_Click);
			// 
			// btnRegu1
			// 
			this.btnRegu1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnRegu1.Location = new System.Drawing.Point(628, 499);
			this.btnRegu1.Name = "btnRegu1";
			this.btnRegu1.Size = new System.Drawing.Size(150, 37);
			this.btnRegu1.TabIndex = 6;
			this.btnRegu1.Text = "Regular layout #1";
			this.btnRegu1.UseVisualStyleBackColor = true;
			this.btnRegu1.Click += new System.EventHandler(this.btnRegu1_Click);
			// 
			// FormVisu
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(790, 634);
			this.Controls.Add(this.btnRegu1);
			this.Controls.Add(this.btnRegu2);
			this.Controls.Add(this.togglePerPixel);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnClear);
			this.Controls.Add(this.picField);
			this.Name = "FormVisu";
			this.Text = "Maximum minimum distance";
			((System.ComponentModel.ISupportInitialize)(this.picField)).EndInit();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox picField;
		private System.Windows.Forms.Button btnClear;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox togglePerPixel;
		private System.Windows.Forms.Button btnRegu2;
		private System.Windows.Forms.Button btnRegu1;
    }
}

