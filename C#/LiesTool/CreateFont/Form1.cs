using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Text;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace CreateFont
{
    public partial class Form1 : Form
    {
        private ImageManager Image;
        private Form2 data_form = new Form2();
        private Point ImageOffset = new Point(0, 0);
        private Point PanelOffset = new Point(0, 0);
        public Form1()
        {
            InitializeComponent();
            Image = new ImageManager(pic_screen, 128, 64);

            txt_Font.Text = fontDialog1.Font.Name + ", " + fontDialog1.Font.Size.ToString("0.00") +
                "     Bold: " + fontDialog1.Font.Bold + ", Italic: " + fontDialog1.Font.Italic;
            cb_mode.SelectedIndex = 0;
            cb_dataType.SelectedIndex = 0;
            tmr_mouse.Enabled = true;
        }
        private void btn_import_Click(object sender, EventArgs e)
        {
            if (open_file.ShowDialog() == DialogResult.OK)
            {
                txt_img_path.Text = open_file.FileName;
                not_update_tb = true;
                num_dark_ValueChanged(null, null);
            }
        }

        private void btn_create_Click(object sender, EventArgs e)
        {
            string sdata = "{\n";
            int[] type = { 8, 16, 32, 24, 16, 0 };
            string[] shex = { "X2", "X4", "X8" };
            Func<int, int, int>[] loop_change =
            {
                (int value, int delta) => {return value + delta; },
                (int value, int delta) => {return value - delta; },
            };
            Func<int, int, bool>[] loop_compare =
            {
                (int value1, int value2) => { return value1 < value2; },
                (int value1, int value2) => { return value1 > value2; },
            };
            int[][] loop_data = new int[8][]
            {
                new int[]{ 0, Image.PxHeight, 0, Image.PxWidth},
                new int[]{ 0, Image.PxHeight, Image.PxWidth - 1, -1},
                new int[]{ Image.PxHeight - 1, -1, 0, Image.PxWidth},
                new int[]{ Image.PxHeight - 1, -1, Image.PxWidth - 1, -1},

                new int[]{ 0, Image.PxWidth, 0, Image.PxHeight},
                new int[]{ 0, Image.PxWidth, Image.PxHeight - 1, -1},
                new int[]{ Image.PxWidth - 1, -1, 0, Image.PxHeight},
                new int[]{ Image.PxWidth - 1, -1, Image.PxHeight - 1, -1},
            };
            int[] lack_break = new int[] { Image.PxHeight, Image.PxWidth };
            int mode = cb_mode.SelectedIndex;
            int mode_mod4 = cb_mode.SelectedIndex % 4;
            int data_type = cb_dataType.SelectedIndex;
            for (int r = loop_data[mode][0]; loop_compare[mode_mod4 / 2](r, loop_data[mode][1]); r = loop_change[mode_mod4 / 2](r, type[data_type]))
            {
                List<uint> data = new List<uint>();
                for (int c = loop_data[mode][2]; loop_compare[mode_mod4 % 2](c, loop_data[mode][3]); c = loop_change[mode_mod4 % 2](c, 1))
                {
                    uint value = 0;
                    for (int i = 0; i < type[data_type]; i++)
                    {
                        int r_index = loop_change[mode_mod4 / 2](r, i);
                        if (r_index < 0 || r_index >= lack_break[mode / 4])
                        {
                            if (rad_LSB.Checked)
                                value >>= type[data_type] - i;
                            else
                                value <<= type[data_type] - i;
                            break;
                        }
                        bool is_set;
                        if (mode < 4)
                            is_set = Image.Data[r_index][c];
                        else
                            is_set = Image.Data[c][r_index];
                        if (rad_LSB.Checked)
                        {
                            value >>= 1;
                            if (is_set)
                                value |= 0x80000000;
                        }
                        else
                        {
                            value <<= 1;
                            if (is_set)
                                value |= 0x00000001;
                        }
                    }
                    if (rad_LSB.Checked)
                        data.Add(value >> type[data_type + 3]);
                    else
                        data.Add(value);
                }
                int last_empty = data.Count - 1;
                if (ckb_removeEmpty.Checked)
                {
                    for (; last_empty > -1; last_empty--)
                    {
                        if (data[last_empty] != 0)
                            break;
                    }
                }
                for (int i = 0; i <= last_empty; i++)
                    sdata += "0x" + data[i].ToString(shex[data_type]) + ", ";
                sdata += "\n";
            }
            sdata += "\n}";
            data_form.UpdateData(sdata);
        }
        private void pic_screen_MouseDown(object sender, MouseEventArgs e)
        {
            if (Image.MouseDown(e.Button, e.Location))
                pic_screen.Refresh();
        }
        private void pic_screen_MouseUp(object sender, MouseEventArgs e)
        {
            Image.MouseDown(MouseButtons.None, e.Location);
        }
        private void tmr_mouse_Tick(object sender, EventArgs e)
        {
            if (Image.SelectDraw(pic_screen.PointToClient(Cursor.Position)))
                pic_screen.Refresh();
        }
        bool not_update_tb = false;
        private void tb_dark_Scroll(object sender, EventArgs e)
        {
            not_update_tb = true;
            num_dark.Value = tb_dark.Value;
        }
        private bool CheckTextValue(ref Point Ref, string Text, Func<Point, int[]> ExtendCheck = null)
        {
            MatchCollection mc = Regex.Matches(Text, @"-?\d+");
            if (mc.Count == 2)
            {
                int x_value = int.Parse(mc[0].Value);
                int y_value = int.Parse(mc[1].Value);
                if (x_value != Ref.X || y_value != Ref.Y)
                {
                    if (ExtendCheck != null)
                    {
                        int[] newPoint = ExtendCheck(new Point(x_value, y_value));
                        if (newPoint == null)
                            return false;
                        Ref = new Point(newPoint[0], newPoint[1]);
                    }
                    else
                        Ref = new Point(x_value, y_value);
                    return true;
                }
            }
            return false;
        }
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Enter)
            {
                if (txt_ImgLocation.Focused)
                {
                    if (CheckTextValue(ref ImageOffset, txt_ImgLocation.Text))
                    {
                        not_update_tb = true;
                        num_dark_ValueChanged(null, null);
                    }
                    txt_ImgLocation.Text = ImageOffset.X + ", " + ImageOffset.Y;
                    return true;
                }
                else if (txt_PnLocation.Focused)
                {
                    if (CheckTextValue(ref PanelOffset, txt_PnLocation.Text))
                    {

                    }
                    txt_PnLocation.Text = PanelOffset.X + ", " + PanelOffset.Y;
                    return true;
                }
                else if (txt_PnSize.Focused)
                {
                    Point newSize = new Point(Image.PxWidth, Image.PxHeight);
                    if (CheckTextValue(ref newSize, txt_PnSize.Text, (Point newS) =>
                    {
                        if (newS.X < 8 || newS.X > 128 || newS.Y < 8 || newS.Y > 64)
                            return null;
                        newS.X = 8 * (newS.X / 8);
                        newS.Y = 8 * (newS.Y / 8);
                        return new int[] { newS.X, newS.Y };
                    }))
                        Image.Create(pic_screen, newSize.X, newSize.Y);
                    txt_PnSize.Text = newSize.X + ", " + newSize.Y;
                    return true;
                }
                else if (txt_FontData.Focused)
                {
                    btn_CreateFont_Click(null, null);
                    return true;
                }
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        private void num_dark_ValueChanged(object sender, EventArgs e)
        {
            if (not_update_tb)
                not_update_tb = false;
            else
                tb_dark.Value = (int)num_dark.Value;
            if (Image.Import(txt_img_path.Text, (float)tb_dark.Value / 100, ImageOffset))
                pic_screen.Refresh();
        }
        private void btn_ImageOffset_Click(object sender, EventArgs e)
        {
            Dictionary<object, Func<int, int, Point>> offset_function = new Dictionary<object, Func<int, int, Point>>()
            {
                { btn_ImgUp, (int X, int Y) => { return new Point(X, Y - (int)num_ImgYOffset.Value); } },
                { btn_ImgDown, (int X, int Y) => { return new Point(X, Y + (int)num_ImgYOffset.Value); } },
                { btn_ImgLeft, (int X, int Y) => { return new Point(X - (int)num_ImgXOffset.Value, Y); } },
                { btn_ImgRight, (int X, int Y) => { return new Point(X + (int)num_ImgXOffset.Value, Y); } },
            };
            not_update_tb = true;
            ImageOffset = offset_function[sender](ImageOffset.X, ImageOffset.Y);
            txt_ImgLocation.Text = ImageOffset.X + ", " + ImageOffset.Y;
            num_dark_ValueChanged(null, null);
        }
        private void btn_PanelOffset_Click(object sender, EventArgs e)
        {
            Dictionary<object, Func<int, int, Point>> offset_function = new Dictionary<object, Func<int, int, Point>>()
            {
                { btn_PnUp, (int X, int Y) => { return new Point(X, Y - (int)num_PnYOffset.Value); } },
                { btn_PnDown, (int X, int Y) => { return new Point(X, Y + (int)num_PnYOffset.Value); } },
                { btn_PnLeft, (int X, int Y) => { return new Point(X - (int)num_PnXOffset.Value, Y); } },
                { btn_PnRight, (int X, int Y) => { return new Point(X + (int)num_PnXOffset.Value, Y); } },
            };
            PanelOffset = offset_function[sender](PanelOffset.X, PanelOffset.Y);
            txt_PnLocation.Text = PanelOffset.X + ", " + PanelOffset.Y;
        }
        private void btn_chooseFont_Click(object sender, EventArgs e)
        {
            if (fontDialog1.ShowDialog() == DialogResult.OK)
            {
                txt_Font.Text = fontDialog1.Font.Name + ", " + fontDialog1.Font.Size.ToString("0.00") +
                    "     Bold: " + fontDialog1.Font.Bold + ", Italic: " + fontDialog1.Font.Italic;
            }
        }
        private void btn_CreateFont_Click(object sender, EventArgs e)
        {
            if (sender != null)
                ((Button)sender).ImageIndex = (((Button)sender).ImageIndex + 1) % (sender == btn_TextDirection ? 8 : 4);
            //Point[] init_location = new Point[]
            //{
            //    new Point(0, 0),
            //    new Point(0, Image.PxHeight - 1),
            //    new Point(Image.PxWidth - 1, 0),
            //    new Point(Image.PxWidth - 1, Image.PxHeight - 1),

            //    new Point(0, 0),
            //    new Point(Image.PxWidth - 1, 0),
            //    new Point(0, Image.PxHeight - 1),
            //    new Point(Image.PxWidth - 1, Image.PxHeight - 1),
            //};
            //Func<Point, SizeF, Point>[] change_location = new Func<Point, SizeF, Point>[]
            //{
            //    (Point now_location, SizeF textSize) => { now_location.X += (int)Math.Round(textSize.Width) + 1; return now_location; },
            //    (Point now_location, SizeF textSize) => { now_location.X -= (int)Math.Round(textSize.Width) + 1; return now_location; },
            //    (Point now_location, SizeF textSize) => { now_location.Y += (int)Math.Round(textSize.Height) + 1; return now_location; },
            //    (Point now_location, SizeF textSize) => { now_location.Y -= (int)Math.Round(textSize.Height) + 1; return now_location; },
            //};
            //Func<Point, SizeF, Point>[] pre_location = new Func<Point, SizeF, Point>[]
            //{
            //    (Point now_location, SizeF textSize) => { now_location.X += (int)Math.Round(textSize.Width) + 1; return now_location; },
            //    (Point now_location, SizeF textSize) => { now_location.X -= (int)Math.Round(textSize.Width) + 1; return now_location; },
            //    (Point now_location, SizeF textSize) => { now_location.Y += (int)Math.Round(textSize.Height) + 1; return now_location; },
            //    (Point now_location, SizeF textSize) => { now_location.Y -= (int)Math.Round(textSize.Height) + 1; return now_location; },
            //};
            DirectBitmap img = new DirectBitmap(Image.PxWidth, Image.PxHeight);
            Graphics grs = Graphics.FromImage(img.Bitmap);
            grs.Clear(Color.White);
            //grs.TranslateTransform(img.Width / 2, img.Height / 2);
            //grs.RotateTransform(90 * btn_TextRotation.ImageIndex);
            grs.TextRenderingHint = TextRenderingHint.SingleBitPerPixelGridFit;

            grs.DrawString(txt_FontData.Text, fontDialog1.Font, Brushes.Black, -7, -11);

            //Point location = init_location[btn_TextDirection.ImageIndex];
            //foreach (char c in txt_FontData.Text)
            //{
            //    if (c == ' ')
            //        continue;
            //    SizeF sizef = grs.MeasureString(c + "", fontDialog1.Font);
            //    grs.DrawString(c + "", fontDialog1.Font, Brushes.Black, location);
            //    location = change_location[btn_TextDirection.ImageIndex / 2](location, sizef);
            //}


            for (int i = 0; i < Image.PxHeight; i++)
            {
                for (int j = 0; j < Image.PxWidth; j++)
                    Image.Data[i][j] = false;
            }
            for (int i = 0; i < Image.PxWidth; i++)
            {
                for (int j = 0; j < Image.PxHeight; j++)
                {
                    if (img.GetPixel(i, j).R < 128)
                        Image.Data[j][i] = true;
                }
            }
            Image.Paint();
            pic_screen.Refresh();
        }
        private void btn_PnClear_Click(object sender, EventArgs e)
        {
            Image.CLear();
            pic_screen.Refresh();
        }

        private void btn_PnReverse_Click(object sender, EventArgs e)
        {
            Image.Reverse();
            pic_screen.Refresh();
        }

        private void btn_ImgExport_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                Image.Export(saveFileDialog1.FileName);
        }
    }
    class ImageManager
    {
        private static Color ClearColor = Color.Black;
        private static Brush ClearBrush = Brushes.Black;
        private static Brush FillBrush = Brushes.White;
        private static Pen NormalPen = Pens.Gray;
        private static Pen RegionPen = Pens.LightGray;
        private static Pen SelectPen = Pens.Red;

        public bool[][] Data;
        public int PxWidth = 128, PxHeight = 64;

        private MouseButtons MsDown = MouseButtons.None;
        private Bitmap Bmp;
        private Graphics Grs;
        
        private Point PxSelect = new Point(-1, -1);
        private Point PxDraw = new Point(-1, -1);

        public ImageManager(PictureBox PicLinker, int PxWidth, int PxHeight)
        {
            Create(PicLinker, PxWidth, PxHeight);            
        }
        public void CLear()
        {
            for (int i = 0; i < PxHeight; i++)
            {
                for (int j = 0; j < PxWidth; j++)
                    Data[i][j] = false;
            }
            Paint();
        }
        public void Reverse()
        {
            for (int i = 0; i < PxHeight; i++)
            {
                for (int j = 0; j < PxWidth; j++)
                    Data[i][j] = !Data[i][j];
            }
            Paint();
        }
        public void Create(PictureBox PicLinker, int PxWidth, int PxHeight)
        {
            this.PxWidth = PxWidth;
            this.PxHeight = PxHeight;
            Data = new bool[PxHeight][];
            for (int i = 0; i < PxHeight; i++)
                Data[i] = new bool[PxWidth];
            if (Bmp != null)
                Bmp.Dispose();
            Bmp = new Bitmap(PxWidth * 8 + 1, PxHeight * 8 + 1);
            if (Grs != null)
                Grs.Dispose();
            Grs = Graphics.FromImage(Bmp);
            Paint();
            PicLinker.Image = Bmp;
        }
        public void Paint()
        {
            Grs.Clear(ClearColor);
            for (int i = 0; i < PxHeight; i++)
            {
                for (int j = 0; j < PxWidth; j++)
                {
                    if (Data[i][j])
                        Grs.FillRectangle(FillBrush, j * 8, i * 8, 8, 8);
                }
            }
            for (int i = 0; i <= PxHeight; i++)
                Grs.DrawLine(i % 8 == 0 ? RegionPen : NormalPen, 0, i * 8, Bmp.Width - 1, i * 8);
            for (int i = 0; i <= PxWidth; i++)
                Grs.DrawLine(i % 8 == 0 ? RegionPen : NormalPen, i * 8, 0, i * 8, Bmp.Height - 1);
        }
        public bool MouseDown(MouseButtons MouseDown, Point DownLocation)
        {
            MsDown = MouseDown;
            PxDraw = new Point(-1, -1);
            if (MouseDown == MouseButtons.None ||  DownLocation.X % 8 == 0 || DownLocation.Y % 8 == 0)
                return false;
            int x_index = DownLocation.X / 8;
            int y_index = DownLocation.Y / 8;
            PxDraw = new Point(x_index, y_index);
            Data[y_index][x_index] = MouseDown == MouseButtons.Left;
            Grs.FillRectangle(MouseDown == MouseButtons.Left ? FillBrush : ClearBrush, x_index * 8 + 1, y_index * 8 + 1, 7, 7);
            return true;
        }
        public bool SelectDraw(Point MouseLocation)
        {
            if (MouseLocation.X % 8 == 0 || MouseLocation.Y % 8 == 0 || MouseLocation.X < 1 || MouseLocation.X >= Bmp.Width || MouseLocation.Y < 1 || MouseLocation.Y >= Bmp.Height)
                return false;
            int x_index = MouseLocation.X / 8;
            int y_index = MouseLocation.Y / 8;
            bool ret = false;
            if (x_index != PxSelect.X || y_index != PxSelect.Y)
            {
                Grs.DrawRectangle(NormalPen, PxSelect.X * 8, PxSelect.Y * 8, 8, 8);
                if (PxSelect.X % 8 == 0)
                    Grs.DrawLine(RegionPen, PxSelect.X * 8, 0, PxSelect.X * 8, Bmp.Height - 1);
                if (PxSelect.X % 8 == 7)
                    Grs.DrawLine(RegionPen, (PxSelect.X + 1) * 8, 0, (PxSelect.X + 1) * 8, Bmp.Height - 1);
                if (PxSelect.Y % 8 == 0)
                    Grs.DrawLine(RegionPen, 0, PxSelect.Y * 8, Bmp.Width - 1, PxSelect.Y * 8);
                if (PxSelect.Y % 8 == 7)
                    Grs.DrawLine(RegionPen, 0, (PxSelect.Y + 1) * 8, Bmp.Width - 1, (PxSelect.Y + 1) * 8);
                PxSelect = new Point(x_index, y_index);
                Grs.DrawRectangle(SelectPen, PxSelect.X * 8, PxSelect.Y * 8, 8, 8);
                ret = true;
            }
            if (MsDown != MouseButtons.None)
            {
                if (x_index != PxDraw.X || y_index != PxDraw.Y)
                {
                    PxDraw = new Point(x_index, y_index);
                    Data[y_index][x_index] = MsDown == MouseButtons.Left;
                    Grs.FillRectangle(MsDown == MouseButtons.Left ? FillBrush : ClearBrush, x_index * 8 + 1, y_index * 8 + 1, 7, 7);
                    ret = true;
                }
            }
            return ret;
        }
        public bool Import(string ImagePath, float DarkValue, Point ImageOffset)
        {
            if (File.Exists(ImagePath))
            {
                Bitmap SourceImage;
                try { SourceImage = (Bitmap)Bitmap.FromFile(ImagePath); }
                catch { return false; };
                DirectBitmap img = new DirectBitmap(SourceImage.Width, SourceImage.Height);
                using (Graphics gr = Graphics.FromImage(img.Bitmap))
                {
                    var gray_matrix = new float[][] {
                        new float[] { 0.299f, 0.299f, 0.299f, 0, 0 },
                        new float[] { 0.587f, 0.587f, 0.587f, 0, 0 },
                        new float[] { 0.114f, 0.114f, 0.114f, 0, 0 },
                        new float[] { 0,      0,      0,      1, 0 },
                        new float[] { 0,      0,      0,      0, 1 }
                    };
                    var ia = new ImageAttributes();
                    ia.SetColorMatrix(new ColorMatrix(gray_matrix));
                    ia.SetThreshold(DarkValue);
                    var rc = new Rectangle(0, 0, SourceImage.Width, SourceImage.Height);
                    gr.DrawImage(SourceImage, rc, 0, 0, SourceImage.Width, SourceImage.Height, GraphicsUnit.Pixel, ia);
                    gr.Dispose();
                }
                SourceImage.Dispose();
                for (int i = 0; i < PxHeight; i++)
                {
                    for (int j = 0; j < PxWidth; j++)
                        Data[i][j] = false;
                }
                for (int i = 0, c = ImageOffset.X; i < PxWidth && c < img.Width; i++, c++)
                {
                    for (int j = 0, r = ImageOffset.Y; j < PxHeight && r < img.Height; j++, r++)
                    {
                        if (c >= 0 && r >= 0)
                        {
                            if (img.GetPixel(c, r).R < 128)
                                Data[j][i] = true;
                        }
                    }
                }
                img.Dispose();
                Paint();
                return true;
            }
            return false;
        }
        public void Export(string ImagePath)
        {
            Bitmap bmp = new Bitmap(PxWidth, PxHeight);
            for (int i = 0; i < PxWidth; i++)
            {
                for (int j = 0; j < PxHeight; j++)
                    bmp.SetPixel(i, j, Data[j][i] ? Color.Black : Color.White);
            }
            bmp.Save(ImagePath);
        }
    }
    public class DirectBitmap : IDisposable
    {
        public Bitmap Bitmap { get; private set; }
        public Int32[] Bits { get; private set; }
        public bool Disposed { get; private set; }
        public int Height { get; private set; }
        public int Width { get; private set; }

        protected GCHandle BitsHandle { get; private set; }

        public DirectBitmap(int width, int height)
        {
            Width = width;
            Height = height;
            Bits = new Int32[width * height];
            BitsHandle = GCHandle.Alloc(Bits, GCHandleType.Pinned);
            Bitmap = new Bitmap(width, height, width * 4, PixelFormat.Format32bppPArgb, BitsHandle.AddrOfPinnedObject());
        }
        
        public void SetPixel(int x, int y, Color colour)
        {
            int index = x + (y * Width);
            int col = colour.ToArgb();

            Bits[index] = col;
        }

        public Color GetPixel(int x, int y)
        {
            int index = x + (y * Width);
            int col = Bits[index];
            Color result = Color.FromArgb(col);

            return result;
        }

        public void Dispose()
        {
            if (Disposed) return;
            Disposed = true;
            Bitmap.Dispose();
            BitsHandle.Free();
        }
    }
}
