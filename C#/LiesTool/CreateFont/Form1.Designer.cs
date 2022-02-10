
namespace CreateFont
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btn_ImgImport = new System.Windows.Forms.Button();
            this.txt_img_path = new System.Windows.Forms.TextBox();
            this.tb_dark = new System.Windows.Forms.TrackBar();
            this.num_dark = new System.Windows.Forms.NumericUpDown();
            this.pic_screen = new System.Windows.Forms.PictureBox();
            this.btn_ImgUp = new System.Windows.Forms.Button();
            this.btn_ImgRight = new System.Windows.Forms.Button();
            this.btn_ImgLeft = new System.Windows.Forms.Button();
            this.btn_ImgDown = new System.Windows.Forms.Button();
            this.txt_ImgLocation = new System.Windows.Forms.TextBox();
            this.btn_create = new System.Windows.Forms.Button();
            this.open_file = new System.Windows.Forms.OpenFileDialog();
            this.tmr_mouse = new System.Windows.Forms.Timer(this.components);
            this.btn_ImgExport = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cb_dataType = new System.Windows.Forms.ComboBox();
            this.cb_mode = new System.Windows.Forms.ComboBox();
            this.rad_LSB = new System.Windows.Forms.RadioButton();
            this.rad_MSB = new System.Windows.Forms.RadioButton();
            this.ckb_removeEmpty = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.num_ImgXOffset = new System.Windows.Forms.NumericUpDown();
            this.num_ImgYOffset = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txt_Font = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.btn_chooseFont = new System.Windows.Forms.Button();
            this.txt_FontData = new System.Windows.Forms.TextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.num_PnYOffset = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.num_PnXOffset = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.txt_PnLocation = new System.Windows.Forms.TextBox();
            this.btn_PnDown = new System.Windows.Forms.Button();
            this.btn_PnLeft = new System.Windows.Forms.Button();
            this.btn_PnRight = new System.Windows.Forms.Button();
            this.btn_PnUp = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.btn_PnReverse = new System.Windows.Forms.Button();
            this.btn_PnClear = new System.Windows.Forms.Button();
            this.fontDialog1 = new System.Windows.Forms.FontDialog();
            this.txt_PnSize = new System.Windows.Forms.TextBox();
            this.btn_TextDirection = new System.Windows.Forms.Button();
            this.btn_TextRotation = new System.Windows.Forms.Button();
            this.imageList2 = new System.Windows.Forms.ImageList(this.components);
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.tb_dark)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_dark)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_screen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_ImgXOffset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_ImgYOffset)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_PnYOffset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_PnXOffset)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_ImgImport
            // 
            this.btn_ImgImport.Location = new System.Drawing.Point(4, 15);
            this.btn_ImgImport.Name = "btn_ImgImport";
            this.btn_ImgImport.Size = new System.Drawing.Size(75, 28);
            this.btn_ImgImport.TabIndex = 0;
            this.btn_ImgImport.Text = "Import >>";
            this.btn_ImgImport.UseVisualStyleBackColor = true;
            this.btn_ImgImport.Click += new System.EventHandler(this.btn_import_Click);
            // 
            // txt_img_path
            // 
            this.txt_img_path.Location = new System.Drawing.Point(85, 16);
            this.txt_img_path.Name = "txt_img_path";
            this.txt_img_path.ReadOnly = true;
            this.txt_img_path.Size = new System.Drawing.Size(459, 20);
            this.txt_img_path.TabIndex = 1;
            // 
            // tb_dark
            // 
            this.tb_dark.Location = new System.Drawing.Point(172, 42);
            this.tb_dark.Maximum = 100;
            this.tb_dark.Name = "tb_dark";
            this.tb_dark.Size = new System.Drawing.Size(371, 45);
            this.tb_dark.TabIndex = 2;
            this.tb_dark.Value = 50;
            this.tb_dark.Scroll += new System.EventHandler(this.tb_dark_Scroll);
            // 
            // num_dark
            // 
            this.num_dark.Location = new System.Drawing.Point(124, 48);
            this.num_dark.Name = "num_dark";
            this.num_dark.Size = new System.Drawing.Size(43, 20);
            this.num_dark.TabIndex = 3;
            this.num_dark.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_dark.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.num_dark.ValueChanged += new System.EventHandler(this.num_dark_ValueChanged);
            // 
            // pic_screen
            // 
            this.pic_screen.Location = new System.Drawing.Point(5, 177);
            this.pic_screen.Name = "pic_screen";
            this.pic_screen.Size = new System.Drawing.Size(1025, 513);
            this.pic_screen.TabIndex = 4;
            this.pic_screen.TabStop = false;
            this.pic_screen.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pic_screen_MouseDown);
            this.pic_screen.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pic_screen_MouseUp);
            // 
            // btn_ImgUp
            // 
            this.btn_ImgUp.Location = new System.Drawing.Point(137, 14);
            this.btn_ImgUp.Name = "btn_ImgUp";
            this.btn_ImgUp.Size = new System.Drawing.Size(52, 22);
            this.btn_ImgUp.TabIndex = 5;
            this.btn_ImgUp.Text = "^";
            this.btn_ImgUp.UseVisualStyleBackColor = true;
            this.btn_ImgUp.Click += new System.EventHandler(this.btn_ImageOffset_Click);
            // 
            // btn_ImgRight
            // 
            this.btn_ImgRight.Location = new System.Drawing.Point(186, 31);
            this.btn_ImgRight.Name = "btn_ImgRight";
            this.btn_ImgRight.Size = new System.Drawing.Size(22, 22);
            this.btn_ImgRight.TabIndex = 6;
            this.btn_ImgRight.Text = ">";
            this.btn_ImgRight.UseVisualStyleBackColor = true;
            this.btn_ImgRight.Click += new System.EventHandler(this.btn_ImageOffset_Click);
            // 
            // btn_ImgLeft
            // 
            this.btn_ImgLeft.Location = new System.Drawing.Point(118, 31);
            this.btn_ImgLeft.Name = "btn_ImgLeft";
            this.btn_ImgLeft.Size = new System.Drawing.Size(22, 22);
            this.btn_ImgLeft.TabIndex = 7;
            this.btn_ImgLeft.Text = "<";
            this.btn_ImgLeft.UseVisualStyleBackColor = true;
            this.btn_ImgLeft.Click += new System.EventHandler(this.btn_ImageOffset_Click);
            // 
            // btn_ImgDown
            // 
            this.btn_ImgDown.Location = new System.Drawing.Point(137, 50);
            this.btn_ImgDown.Name = "btn_ImgDown";
            this.btn_ImgDown.Size = new System.Drawing.Size(52, 22);
            this.btn_ImgDown.TabIndex = 8;
            this.btn_ImgDown.Text = "v";
            this.btn_ImgDown.UseVisualStyleBackColor = true;
            this.btn_ImgDown.Click += new System.EventHandler(this.btn_ImageOffset_Click);
            // 
            // txt_ImgLocation
            // 
            this.txt_ImgLocation.Location = new System.Drawing.Point(138, 32);
            this.txt_ImgLocation.Name = "txt_ImgLocation";
            this.txt_ImgLocation.Size = new System.Drawing.Size(50, 20);
            this.txt_ImgLocation.TabIndex = 9;
            this.txt_ImgLocation.Text = "0,0";
            this.txt_ImgLocation.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btn_create
            // 
            this.btn_create.Location = new System.Drawing.Point(933, 36);
            this.btn_create.Name = "btn_create";
            this.btn_create.Size = new System.Drawing.Size(91, 47);
            this.btn_create.TabIndex = 10;
            this.btn_create.Text = "Create  Copy";
            this.btn_create.UseVisualStyleBackColor = true;
            this.btn_create.Click += new System.EventHandler(this.btn_create_Click);
            // 
            // open_file
            // 
            this.open_file.Filter = "*.png|*.png|*.jpeg|*.jpeg";
            // 
            // tmr_mouse
            // 
            this.tmr_mouse.Interval = 10;
            this.tmr_mouse.Tick += new System.EventHandler(this.tmr_mouse_Tick);
            // 
            // btn_ImgExport
            // 
            this.btn_ImgExport.Location = new System.Drawing.Point(4, 47);
            this.btn_ImgExport.Name = "btn_ImgExport";
            this.btn_ImgExport.Size = new System.Drawing.Size(75, 28);
            this.btn_ImgExport.TabIndex = 12;
            this.btn_ImgExport.Text = "<< Export";
            this.btn_ImgExport.UseVisualStyleBackColor = true;
            this.btn_ImgExport.Click += new System.EventHandler(this.btn_ImgExport_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(85, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 13);
            this.label1.TabIndex = 13;
            this.label1.Text = "Dark:";
            // 
            // cb_dataType
            // 
            this.cb_dataType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cb_dataType.FormattingEnabled = true;
            this.cb_dataType.Items.AddRange(new object[] {
            "8 bit",
            "16 bit",
            "32 bit"});
            this.cb_dataType.Location = new System.Drawing.Point(801, 62);
            this.cb_dataType.Name = "cb_dataType";
            this.cb_dataType.Size = new System.Drawing.Size(121, 21);
            this.cb_dataType.TabIndex = 17;
            // 
            // cb_mode
            // 
            this.cb_mode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cb_mode.FormattingEnabled = true;
            this.cb_mode.Items.AddRange(new object[] {
            "V: TL->BR",
            "V: TR->BL",
            "V: BL->TR",
            "V: BR->TL",
            "H: TL->BR",
            "H: TR->BL",
            "H: BL->TR",
            "H: BR->TL"});
            this.cb_mode.Location = new System.Drawing.Point(801, 38);
            this.cb_mode.Name = "cb_mode";
            this.cb_mode.Size = new System.Drawing.Size(121, 21);
            this.cb_mode.TabIndex = 16;
            // 
            // rad_LSB
            // 
            this.rad_LSB.AutoSize = true;
            this.rad_LSB.Location = new System.Drawing.Point(877, 12);
            this.rad_LSB.Name = "rad_LSB";
            this.rad_LSB.Size = new System.Drawing.Size(45, 17);
            this.rad_LSB.TabIndex = 15;
            this.rad_LSB.Text = "LSB";
            this.rad_LSB.UseVisualStyleBackColor = true;
            // 
            // rad_MSB
            // 
            this.rad_MSB.AutoSize = true;
            this.rad_MSB.Checked = true;
            this.rad_MSB.Location = new System.Drawing.Point(801, 12);
            this.rad_MSB.Name = "rad_MSB";
            this.rad_MSB.Size = new System.Drawing.Size(48, 17);
            this.rad_MSB.TabIndex = 14;
            this.rad_MSB.TabStop = true;
            this.rad_MSB.Text = "MSB";
            this.rad_MSB.UseVisualStyleBackColor = true;
            // 
            // ckb_removeEmpty
            // 
            this.ckb_removeEmpty.AutoSize = true;
            this.ckb_removeEmpty.Location = new System.Drawing.Point(929, 13);
            this.ckb_removeEmpty.Name = "ckb_removeEmpty";
            this.ckb_removeEmpty.Size = new System.Drawing.Size(98, 17);
            this.ckb_removeEmpty.TabIndex = 18;
            this.ckb_removeEmpty.Text = "Remove Empty";
            this.ckb_removeEmpty.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 13);
            this.label2.TabIndex = 19;
            this.label2.Text = "Delta X:";
            // 
            // num_ImgXOffset
            // 
            this.num_ImgXOffset.Location = new System.Drawing.Point(57, 22);
            this.num_ImgXOffset.Name = "num_ImgXOffset";
            this.num_ImgXOffset.Size = new System.Drawing.Size(43, 20);
            this.num_ImgXOffset.TabIndex = 20;
            this.num_ImgXOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_ImgXOffset.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // num_ImgYOffset
            // 
            this.num_ImgYOffset.Location = new System.Drawing.Point(57, 46);
            this.num_ImgYOffset.Name = "num_ImgYOffset";
            this.num_ImgYOffset.Size = new System.Drawing.Size(43, 20);
            this.num_ImgYOffset.TabIndex = 22;
            this.num_ImgYOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_ImgYOffset.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 13);
            this.label3.TabIndex = 21;
            this.label3.Text = "Delta Y:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.btn_ImgExport);
            this.groupBox1.Controls.Add(this.num_dark);
            this.groupBox1.Controls.Add(this.txt_img_path);
            this.groupBox1.Controls.Add(this.btn_ImgImport);
            this.groupBox1.Controls.Add(this.tb_dark);
            this.groupBox1.Location = new System.Drawing.Point(8, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(549, 81);
            this.groupBox1.TabIndex = 23;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Image";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.num_ImgYOffset);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.num_ImgXOffset);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.txt_ImgLocation);
            this.groupBox2.Controls.Add(this.btn_ImgDown);
            this.groupBox2.Controls.Add(this.btn_ImgLeft);
            this.groupBox2.Controls.Add(this.btn_ImgRight);
            this.groupBox2.Controls.Add(this.btn_ImgUp);
            this.groupBox2.Location = new System.Drawing.Point(563, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(221, 81);
            this.groupBox2.TabIndex = 24;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Offset";
            // 
            // txt_Font
            // 
            this.txt_Font.Location = new System.Drawing.Point(86, 19);
            this.txt_Font.Name = "txt_Font";
            this.txt_Font.ReadOnly = true;
            this.txt_Font.Size = new System.Drawing.Size(458, 20);
            this.txt_Font.TabIndex = 25;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btn_TextRotation);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.btn_TextDirection);
            this.groupBox3.Controls.Add(this.btn_chooseFont);
            this.groupBox3.Controls.Add(this.txt_FontData);
            this.groupBox3.Controls.Add(this.txt_Font);
            this.groupBox3.Location = new System.Drawing.Point(8, 90);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(549, 81);
            this.groupBox3.TabIndex = 26;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Font";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(26, 52);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(31, 13);
            this.label4.TabIndex = 37;
            this.label4.Text = "Text:";
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "t_l_r.png");
            this.imageList1.Images.SetKeyName(1, "b_l_r.png");
            this.imageList1.Images.SetKeyName(2, "t_r_l.png");
            this.imageList1.Images.SetKeyName(3, "b_r_l.png");
            this.imageList1.Images.SetKeyName(4, "l_t_b.png");
            this.imageList1.Images.SetKeyName(5, "r_t_b.png");
            this.imageList1.Images.SetKeyName(6, "l_b_t.png");
            this.imageList1.Images.SetKeyName(7, "r_b_t.png");
            // 
            // btn_chooseFont
            // 
            this.btn_chooseFont.Location = new System.Drawing.Point(4, 15);
            this.btn_chooseFont.Name = "btn_chooseFont";
            this.btn_chooseFont.Size = new System.Drawing.Size(75, 28);
            this.btn_chooseFont.TabIndex = 27;
            this.btn_chooseFont.Text = "Choose";
            this.btn_chooseFont.UseVisualStyleBackColor = true;
            this.btn_chooseFont.Click += new System.EventHandler(this.btn_chooseFont_Click);
            // 
            // txt_FontData
            // 
            this.txt_FontData.Location = new System.Drawing.Point(86, 49);
            this.txt_FontData.MaxLength = 255;
            this.txt_FontData.Name = "txt_FontData";
            this.txt_FontData.Size = new System.Drawing.Size(393, 20);
            this.txt_FontData.TabIndex = 26;
            this.txt_FontData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.txt_PnSize);
            this.groupBox4.Controls.Add(this.num_PnYOffset);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.num_PnXOffset);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.txt_PnLocation);
            this.groupBox4.Controls.Add(this.btn_PnDown);
            this.groupBox4.Controls.Add(this.btn_PnLeft);
            this.groupBox4.Controls.Add(this.btn_PnRight);
            this.groupBox4.Controls.Add(this.btn_PnUp);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Controls.Add(this.btn_PnReverse);
            this.groupBox4.Controls.Add(this.btn_PnClear);
            this.groupBox4.Location = new System.Drawing.Point(563, 90);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(467, 81);
            this.groupBox4.TabIndex = 27;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Panel control";
            // 
            // num_PnYOffset
            // 
            this.num_PnYOffset.Location = new System.Drawing.Point(58, 47);
            this.num_PnYOffset.Name = "num_PnYOffset";
            this.num_PnYOffset.Size = new System.Drawing.Size(43, 20);
            this.num_PnYOffset.TabIndex = 35;
            this.num_PnYOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_PnYOffset.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 50);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(45, 13);
            this.label7.TabIndex = 34;
            this.label7.Text = "Delta Y:";
            // 
            // num_PnXOffset
            // 
            this.num_PnXOffset.Location = new System.Drawing.Point(58, 23);
            this.num_PnXOffset.Name = "num_PnXOffset";
            this.num_PnXOffset.Size = new System.Drawing.Size(43, 20);
            this.num_PnXOffset.TabIndex = 33;
            this.num_PnXOffset.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.num_PnXOffset.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 26);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(45, 13);
            this.label8.TabIndex = 32;
            this.label8.Text = "Delta X:";
            // 
            // txt_PnLocation
            // 
            this.txt_PnLocation.Location = new System.Drawing.Point(139, 33);
            this.txt_PnLocation.Name = "txt_PnLocation";
            this.txt_PnLocation.Size = new System.Drawing.Size(50, 20);
            this.txt_PnLocation.TabIndex = 31;
            this.txt_PnLocation.Text = "0,0";
            this.txt_PnLocation.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btn_PnDown
            // 
            this.btn_PnDown.Location = new System.Drawing.Point(138, 51);
            this.btn_PnDown.Name = "btn_PnDown";
            this.btn_PnDown.Size = new System.Drawing.Size(52, 22);
            this.btn_PnDown.TabIndex = 30;
            this.btn_PnDown.Text = "v";
            this.btn_PnDown.UseVisualStyleBackColor = true;
            this.btn_PnDown.Click += new System.EventHandler(this.btn_PanelOffset_Click);
            // 
            // btn_PnLeft
            // 
            this.btn_PnLeft.Location = new System.Drawing.Point(119, 32);
            this.btn_PnLeft.Name = "btn_PnLeft";
            this.btn_PnLeft.Size = new System.Drawing.Size(22, 22);
            this.btn_PnLeft.TabIndex = 29;
            this.btn_PnLeft.Text = "<";
            this.btn_PnLeft.UseVisualStyleBackColor = true;
            this.btn_PnLeft.Click += new System.EventHandler(this.btn_PanelOffset_Click);
            // 
            // btn_PnRight
            // 
            this.btn_PnRight.Location = new System.Drawing.Point(187, 32);
            this.btn_PnRight.Name = "btn_PnRight";
            this.btn_PnRight.Size = new System.Drawing.Size(22, 22);
            this.btn_PnRight.TabIndex = 28;
            this.btn_PnRight.Text = ">";
            this.btn_PnRight.UseVisualStyleBackColor = true;
            this.btn_PnRight.Click += new System.EventHandler(this.btn_PanelOffset_Click);
            // 
            // btn_PnUp
            // 
            this.btn_PnUp.Location = new System.Drawing.Point(138, 15);
            this.btn_PnUp.Name = "btn_PnUp";
            this.btn_PnUp.Size = new System.Drawing.Size(52, 22);
            this.btn_PnUp.TabIndex = 27;
            this.btn_PnUp.Text = "^";
            this.btn_PnUp.UseVisualStyleBackColor = true;
            this.btn_PnUp.Click += new System.EventHandler(this.btn_PanelOffset_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(238, 54);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(124, 13);
            this.label6.TabIndex = 26;
            this.label6.Text = "(Divisible 8, max 128x64)";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(239, 32);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(30, 13);
            this.label5.TabIndex = 25;
            this.label5.Text = "Size:";
            // 
            // btn_PnReverse
            // 
            this.btn_PnReverse.Location = new System.Drawing.Point(372, 50);
            this.btn_PnReverse.Name = "btn_PnReverse";
            this.btn_PnReverse.Size = new System.Drawing.Size(89, 26);
            this.btn_PnReverse.TabIndex = 24;
            this.btn_PnReverse.Text = "Reverse";
            this.btn_PnReverse.UseVisualStyleBackColor = true;
            this.btn_PnReverse.Click += new System.EventHandler(this.btn_PnReverse_Click);
            // 
            // btn_PnClear
            // 
            this.btn_PnClear.Location = new System.Drawing.Point(373, 19);
            this.btn_PnClear.Name = "btn_PnClear";
            this.btn_PnClear.Size = new System.Drawing.Size(89, 26);
            this.btn_PnClear.TabIndex = 23;
            this.btn_PnClear.Text = "Clear";
            this.btn_PnClear.UseVisualStyleBackColor = true;
            this.btn_PnClear.Click += new System.EventHandler(this.btn_PnClear_Click);
            // 
            // txt_PnSize
            // 
            this.txt_PnSize.Location = new System.Drawing.Point(275, 29);
            this.txt_PnSize.Name = "txt_PnSize";
            this.txt_PnSize.Size = new System.Drawing.Size(84, 20);
            this.txt_PnSize.TabIndex = 36;
            this.txt_PnSize.Text = "128,64";
            this.txt_PnSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btn_TextDirection
            // 
            this.btn_TextDirection.ImageIndex = 0;
            this.btn_TextDirection.ImageList = this.imageList1;
            this.btn_TextDirection.Location = new System.Drawing.Point(485, 43);
            this.btn_TextDirection.Name = "btn_TextDirection";
            this.btn_TextDirection.Size = new System.Drawing.Size(30, 30);
            this.btn_TextDirection.TabIndex = 30;
            this.btn_TextDirection.UseVisualStyleBackColor = true;
            this.btn_TextDirection.Click += new System.EventHandler(this.btn_CreateFont_Click);
            // 
            // btn_TextRotation
            // 
            this.btn_TextRotation.ImageIndex = 0;
            this.btn_TextRotation.ImageList = this.imageList2;
            this.btn_TextRotation.Location = new System.Drawing.Point(514, 43);
            this.btn_TextRotation.Name = "btn_TextRotation";
            this.btn_TextRotation.Size = new System.Drawing.Size(30, 30);
            this.btn_TextRotation.TabIndex = 38;
            this.btn_TextRotation.UseVisualStyleBackColor = true;
            this.btn_TextRotation.Click += new System.EventHandler(this.btn_CreateFont_Click);
            // 
            // imageList2
            // 
            this.imageList2.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList2.ImageStream")));
            this.imageList2.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList2.Images.SetKeyName(0, "text_0.png");
            this.imageList2.Images.SetKeyName(1, "text_90.png");
            this.imageList2.Images.SetKeyName(2, "text_180.png");
            this.imageList2.Images.SetKeyName(3, "text_270.png");
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "*.png|*.png|*.jpeg|*.jpeg";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1034, 696);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.ckb_removeEmpty);
            this.Controls.Add(this.cb_dataType);
            this.Controls.Add(this.cb_mode);
            this.Controls.Add(this.rad_LSB);
            this.Controls.Add(this.rad_MSB);
            this.Controls.Add(this.btn_create);
            this.Controls.Add(this.pic_screen);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.tb_dark)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_dark)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_screen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_ImgXOffset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_ImgYOffset)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_PnYOffset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_PnXOffset)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_ImgImport;
        private System.Windows.Forms.TextBox txt_img_path;
        private System.Windows.Forms.TrackBar tb_dark;
        private System.Windows.Forms.NumericUpDown num_dark;
        private System.Windows.Forms.PictureBox pic_screen;
        private System.Windows.Forms.Button btn_ImgUp;
        private System.Windows.Forms.Button btn_ImgRight;
        private System.Windows.Forms.Button btn_ImgLeft;
        private System.Windows.Forms.Button btn_ImgDown;
        private System.Windows.Forms.TextBox txt_ImgLocation;
        private System.Windows.Forms.Button btn_create;
        private System.Windows.Forms.OpenFileDialog open_file;
        private System.Windows.Forms.Timer tmr_mouse;
        private System.Windows.Forms.Button btn_ImgExport;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cb_dataType;
        private System.Windows.Forms.ComboBox cb_mode;
        private System.Windows.Forms.RadioButton rad_LSB;
        private System.Windows.Forms.RadioButton rad_MSB;
        private System.Windows.Forms.CheckBox ckb_removeEmpty;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown num_ImgXOffset;
        private System.Windows.Forms.NumericUpDown num_ImgYOffset;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txt_Font;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btn_chooseFont;
        private System.Windows.Forms.TextBox txt_FontData;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.NumericUpDown num_PnYOffset;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown num_PnXOffset;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txt_PnLocation;
        private System.Windows.Forms.Button btn_PnDown;
        private System.Windows.Forms.Button btn_PnLeft;
        private System.Windows.Forms.Button btn_PnRight;
        private System.Windows.Forms.Button btn_PnUp;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btn_PnReverse;
        private System.Windows.Forms.Button btn_PnClear;
        private System.Windows.Forms.FontDialog fontDialog1;
        private System.Windows.Forms.TextBox txt_PnSize;
        private System.Windows.Forms.Button btn_TextRotation;
        private System.Windows.Forms.ImageList imageList2;
        private System.Windows.Forms.Button btn_TextDirection;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
    }
}

