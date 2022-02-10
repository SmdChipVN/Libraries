
namespace CreateFont
{
    partial class Form2
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
            this.rtxt_data = new System.Windows.Forms.RichTextBox();
            this.txt_name = new System.Windows.Forms.TextBox();
            this.btn_rename = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // rtxt_data
            // 
            this.rtxt_data.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.rtxt_data.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtxt_data.Location = new System.Drawing.Point(12, 38);
            this.rtxt_data.Name = "rtxt_data";
            this.rtxt_data.Size = new System.Drawing.Size(776, 400);
            this.rtxt_data.TabIndex = 0;
            this.rtxt_data.Text = "";
            // 
            // txt_name
            // 
            this.txt_name.Location = new System.Drawing.Point(12, 12);
            this.txt_name.Name = "txt_name";
            this.txt_name.Size = new System.Drawing.Size(695, 20);
            this.txt_name.TabIndex = 1;
            this.txt_name.Text = "const unsigned char Font[96][] = ";
            // 
            // btn_rename
            // 
            this.btn_rename.Location = new System.Drawing.Point(713, 10);
            this.btn_rename.Name = "btn_rename";
            this.btn_rename.Size = new System.Drawing.Size(75, 23);
            this.btn_rename.TabIndex = 2;
            this.btn_rename.Text = "Rename";
            this.btn_rename.UseVisualStyleBackColor = true;
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btn_rename);
            this.Controls.Add(this.txt_name);
            this.Controls.Add(this.rtxt_data);
            this.Name = "Form2";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox rtxt_data;
        private System.Windows.Forms.TextBox txt_name;
        private System.Windows.Forms.Button btn_rename;
    }
}