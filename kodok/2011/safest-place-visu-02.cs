using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SafestPlace_visu
{
	public partial class FormVisu : Form
	{
		private class SubSpace : IComparable<SubSpace>
		{
			/// <summary>
			/// Inclusive rectangle which defines this sub-region.
			/// </summary>
			public Rectangle Rect;

			/// <summary>
			/// Maximum solution for either point in this sub-region.
			/// </summary>
			public int UpperBound;

			public SubSpace(Rectangle rectangle, int upperBound)
			{
				this.Rect = rectangle;
				this.UpperBound = upperBound;
			}

			public int Area()
			{
				return (Rect.Width) * (Rect.Height);
			}

			#region IComparable<SubSpace> Members

			public int CompareTo(SubSpace other)
			{
				if (UpperBound > other.UpperBound)
					return -1;
				else if (UpperBound < other.UpperBound)
					return 1;
				else if (Area() < other.Area())
					return -1;
				else if (Area() > other.Area())
					return 1;
				else if (Rect.Location.X.CompareTo(other.Rect.Location.X) != 0)
					return Rect.Location.X.CompareTo(other.Rect.Location.X);
				else
					return Rect.Location.Y.CompareTo(other.Rect.Location.Y);

			}

			#endregion
		}

		private const int bombDisplayRadius = 5;

		private int maxMinDist = 0;
		private int draggedBomb = -1;
		private List<Point> bombs = new List<Point>();

		private List<SubSpace> usedRects = new List<SubSpace>();

		private bool perPixel = false;

		private int distSquared(Point a, Point b)
		{
			return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
		}

		private int findUpperBound(Rectangle rect)
		{
			int minMaxDist = int.MaxValue;

			Point[] points = new Point[] { rect.Location, rect.Location + new Size(rect.Width, 0), rect.Location + new Size(0, rect.Height), rect.Location + rect.Size };
			foreach (Point p in bombs)
			{
				int maxDistFromBomb = 0;
				foreach (Point q in points)
				{
					if (distSquared(p, q) > maxDistFromBomb)
						maxDistFromBomb = distSquared(p, q);
				}

				if (maxDistFromBomb < minMaxDist)
					minMaxDist = maxDistFromBomb;
			}

			return minMaxDist;
		}

		private Rectangle[] divide(Rectangle rect)
		{
			Rectangle tl = new Rectangle(rect.Location, new Size(rect.Width / 2, rect.Height / 2));
			Rectangle tr = new Rectangle(rect.Location + new Size(rect.Width / 2, 0), new Size(rect.Width - rect.Width / 2, rect.Height / 2));
			Rectangle bl = new Rectangle(rect.Location + new Size(0, rect.Height / 2), new Size(rect.Width / 2, rect.Height - rect.Height / 2));
			Rectangle br = new Rectangle(rect.Location + new Size(rect.Width / 2, rect.Height / 2), new Size(rect.Width - rect.Width / 2, rect.Height - rect.Height / 2));
			return new Rectangle[] { tl, tr, bl, br };
		}

		public FormVisu()
		{
			InitializeComponent();
		}

		private void calculate()
		{
			int bestSoFar = 0;
			usedRects.Clear();

			if (bombs.Count == 0)
			{
				maxMinDist = 0;
				picField.Invalidate();
				return;
			}

			SortedDictionary<SubSpace, object> activeRects = new SortedDictionary<SubSpace, object>();
			activeRects.Add(new SubSpace(new Rectangle(0, 0, picField.Width, picField.Height), int.MaxValue), null);
			while (activeRects.Count > 0)
			{
				SortedDictionary<SubSpace, object>.Enumerator e = activeRects.GetEnumerator();
				e.MoveNext();
				SubSpace s = e.Current.Key;
				activeRects.Remove(s);

				usedRects.Add(s);

				if (s.UpperBound < bestSoFar)
					continue;

				if (s.Area() == 1)
				{
					int distSqr = findUpperBound(s.Rect);
					if (distSqr > bestSoFar)
						bestSoFar = distSqr;
				}
				else
				{
					foreach (Rectangle r in divide(s.Rect))
					{
						SubSpace ss = new SubSpace(r, findUpperBound(r));
						if (ss.Area() != 0)
							activeRects.Add(ss, null);
					}
				}
			}

			maxMinDist = bestSoFar;
			picField.Invalidate();
		}

		private void picField_MouseDown(object sender, MouseEventArgs e)
		{
			for (int i = 0; i < bombs.Count; ++i)
			{
				if (distSquared(bombs[i], e.Location) < (bombDisplayRadius * bombDisplayRadius))
				{
					if ((e.Button & MouseButtons.Right) != 0)
					{
						bombs.RemoveAt(i);
						return;
					}
					else if ((e.Button & MouseButtons.Left) != 0)
					{
						draggedBomb = i;
						return;
					}
				}
			}

			if ((e.Button & MouseButtons.Left) != 0)
			{
				draggedBomb = bombs.Count;
				bombs.Add(e.Location);
			}

			calculate();
		}

		private void picField_MouseMove(object sender, MouseEventArgs e)
		{
			if (draggedBomb != -1)
			{
				bombs[draggedBomb] = e.Location;
				calculate();
			}
		}

		private void picField_MouseUp(object sender, MouseEventArgs e)
		{
			draggedBomb = -1;
			calculate();
		}

		private Color getColor(double goodness)
		{
			Color[] colors = new Color[] { Color.LightGreen, Color.Yellow, Color.OrangeRed };

			goodness *= goodness;
			int index = (int)(goodness / 0.5);
			if (index >= 2) return Color.Red;
			else if (index < 0) return Color.LightGreen;
			else
			{
				double w2 = (goodness - index * 0.5) * 2;
				double w1 = 1 - w2;
				return Color.FromArgb((int)(colors[index].R * w1 + colors[index + 1].R * w2), (int)(colors[index].G * w1 + colors[index + 1].G * w2), (int)(colors[index].B * w1 + colors[index + 1].B * w2));
			}
		}

		private void picField_Paint(object sender, PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			g.Clear(Color.Gray);

			if (maxMinDist > 0)
			{
				if (perPixel)
				{
					Bitmap b = new Bitmap(picField.Width, picField.Height);
					for (int y = 0; y < picField.Height; ++y)
					{
						for (int x = 0; x < picField.Width; ++x)
						{
							Point p = new Point(x, y);
							int minDistSqr = int.MaxValue;
							foreach (Point q in bombs)
							{
								if (distSquared(p, q) < minDistSqr) minDistSqr = distSquared(p, q);
							}
							double goodness = minDistSqr / (double)maxMinDist;
							b.SetPixel(x, y, getColor(goodness));
						}
					}
					g.DrawImage(b, 0, 0);
				}

				using (Pen p = new Pen(Color.Black))
				{
					foreach (SubSpace s in usedRects)
					{
						double goodness = s.UpperBound / (double)maxMinDist;
						using (Brush b = new SolidBrush(getColor(goodness)))
						{
							if (!perPixel) g.FillRectangle(b, s.Rect);
							g.DrawRectangle(p, s.Rect);
						}
					}
				}
			}

			for (int i = 0; i < bombs.Count; ++i)
			{
				using (Pen p = new Pen(Color.Black,1))
				using (Brush b = new SolidBrush(draggedBomb == i ? Color.Gold : Color.LightGray))
				{
					Size halfSize = new Size(bombDisplayRadius, bombDisplayRadius);
					g.FillEllipse(b, new Rectangle(bombs[i] - halfSize, halfSize + halfSize));
					g.DrawEllipse(p, new Rectangle(bombs[i] - halfSize, halfSize + halfSize));
				}
			}
		}

		private void btnClear_Click(object sender, EventArgs e)
		{
			bombs.Clear();
			calculate();
		}
		private void togglePerPixel_CheckedChanged(object sender, EventArgs e)
		{
			perPixel = togglePerPixel.Checked;
			picField.Invalidate();
		}

		private void btnRegu1_Click(object sender, EventArgs e)
		{
			bombs.Clear();

			int N = 6;

			int W = ((picField.Width - 1) / N);
			int H = ((picField.Height - 1) / N);
			for (int y = 0; y <= N; ++y)
			{
				for (int x = 0; x <= N; ++x)
				{
					int rx = W * x;
					int ry = H * y;
					bombs.Add(new Point(rx, ry));
				}
			}
			calculate();
		}

		private void btnRegu2_Click(object sender, EventArgs e)
		{
			bombs.Clear();

			int M = 4;

			double dr = ((picField.Width/2)*3) / (M*2);
			double spacing = 50;

			Point mid = new Point(picField.Width / 2, picField.Height / 2);
			bombs.Add(mid);

			for (int i=1; i<=4; ++i)
			{
				double r = i * dr;
				double c = Math.PI * 2 * r;
				double incr = c / ((int)(c / spacing));
				for (double a = 0; a < c; a += incr)
				{
					double dx = Math.Cos(2 * Math.PI * (a / c)) * r;
					double dy = Math.Sin(2 * Math.PI * (a / c)) * r;
					bombs.Add(mid + new Size((int)dx, (int)dy));
				}
			}
			calculate();
		}
	}
}
