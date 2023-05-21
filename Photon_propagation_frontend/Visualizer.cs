using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Photon_propagation_frontend
{
    internal class Visualizer
    {
        const int image_wight = 1920;
        const int image_height = 1080;
        static private Int32 block_widht;
        static private Int32 block_height;

        static public Image GetImage(double[,] Matrix) 
        {
            Normalizematrix(Matrix);

            block_widht = (image_wight / 2 + Matrix.GetLength(0) - 1) / Matrix.GetLength(0);
            block_height = (image_height + Matrix.GetLength(1) - 1) / Matrix.GetLength(1);

            Bitmap bitmap = new Bitmap(image_wight, image_height);


            int mid_block = image_wight / (2 * block_widht);
            for (int i = 0; i < Math.Min(Matrix.GetLength(0), mid_block); i++)
            {
                for (int j = 0; j < Math.Min(Matrix.GetLength(1), image_height / block_height); j++)
                {
                    Color color = GetColor(Matrix[i, j]);

                    SetBlockColor(bitmap, mid_block + i, j, color);
                    SetBlockColor(bitmap, mid_block - i - 1, j, color);
                }
            }

            return bitmap;
        }
        
        static void Normalizematrix(double[,] Matrix)
        {
            double Max = 0.0;
            for (int i = 0; i < Matrix.GetLength(0); i++)
            {
                for (int j = 0; j < Matrix.GetLength(1); j++)
                {
                    Matrix[i, j] = Math.Log(Math.Log(Matrix[i, j] + 1) + 1);
                    Max = Math.Max(Max, Matrix[i, j]);
                }
            }

            for (int i = 0; i < Matrix.GetLength(0); i++)
            {
                for (int j = 0; j < Matrix.GetLength(1); j++)
                {
                    Matrix[i, j] /= Max;
                }
            }
        }

        private static readonly Color[] colors = { Color.Black, Color.Blue,
                Color.Cyan, Color.Green, Color.YellowGreen, Color.Yellow,
                Color.Orange, Color.Red};

        private static Color GetColor(double v)
        {
            double r, g ,b;

            

            if (v < 1.0)
            {
                int size = colors.Length - 1;
                v *= size;
                int color_id = (int)v;

                r = colors[color_id + 1].R * (v - color_id) + colors[color_id].R * (color_id + 1 - v);
                g = colors[color_id + 1].G * (v - color_id) + colors[color_id].G * (color_id + 1 - v);
                b = colors[color_id + 1].B * (v - color_id) + colors[color_id].B * (color_id + 1 - v);
                return Color.FromArgb(Clamp(r), Clamp(g), Clamp(b));
            }
            else
            {
                return colors.Last();
            }
        }

        private static void SetBlockColor(Bitmap bitmap, int i, int j, Color color)
        {
            for (int l = block_widht * i; l < block_widht * (i + 1); l++)
            {
                for (int k = block_height * j; k < block_height * (j + 1); k++)
                {
                    bitmap.SetPixel(l, k, color);
                }
            }
        }

        private static int Clamp(int Val)
        {
            Val = Math.Max(Val, 0);
            Val = Math.Min(Val, 255);

            return Val;
        }

        private static int Clamp(double Val)
        {
            return Clamp(Convert.ToInt32(Val));
        }
    }
}
