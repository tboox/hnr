#ifndef SAMPLE_HELPER_H
#define SAMPLE_HELPER_H

#include "prefix.h"
#include "math.h"

inline void nearest_neighbor_zoom(image_type const& bmp_img, image_type& new_img)
{
	double fh = (double)new_img.height() / bmp_img.height();
	double fw = (double)new_img.width() / bmp_img.width();
	int part_w = int(fw + 1);
	int part_h = int(fh + 1);

	int px, py;
	// clear
	for (px = 0; px < new_img.width(); ++px)
		for (py = 0; py < new_img.height(); ++py)
			new_img.at(px, py).is_black(false);

	// interpolation
	for (px = 0; px < bmp_img.width(); ++px)
	{
		for (py = 0; py < bmp_img.height(); ++py)
		{
			for (int k = 0; k < part_w * part_h; ++k)
			{
				int new_y = (int)(py * fh + k / part_w);
				new_y = new_y < new_img.height()? new_y : (new_img.height() - 1);

				int new_x = (int)(px * fw + k % part_w);
				new_x = new_x < new_img.width()? new_x : (new_img.width() - 1);

				// fill nearest neighbor pixel
				new_img.at(new_x, new_y) = bmp_img.at(px, py);
			}
		}
	}
}
inline void bilinear_zoom(image_type const& bmp_img, image_type& new_img)
{
	double fh = (double)new_img.height() / bmp_img.height();
	double fw = (double)new_img.width() / bmp_img.width();

	int part_w = int(fw + 1);
	int part_h = int(fh + 1);

	int px, py;
	// clear
	for (px = 0; px < new_img.width(); ++px)
		for (py = 0; py < new_img.height(); ++py)
			new_img.at(px, py).is_black(false);

	// interpolation
	for (px = 0; px < bmp_img.width() - 1; ++px)
	{
		for (py = 0; py < bmp_img.height() - 1; ++py)
		{
			int f00 = bmp_img.at(px, py).gray();
			int f01 = bmp_img.at(px + 1, py).gray();
			int f10 = bmp_img.at(px, py + 1).gray();
			int f11 = bmp_img.at(px + 1, py + 1).gray();

			for (int k = 0; k < part_w * part_h; ++k)
			{
				int new_y = int(py * fh + k / part_w);
				new_y = new_y < new_img.height()? new_y : (new_img.height() - 1);

				int new_x = int(px * fw + k % part_w);
				new_x = new_x < new_img.width()? new_x : (new_img.width() - 1);

				// fill
				double x = (double)(k / part_h) / part_w;	// (0, 1)
				double y = (double)(k % part_w) / part_h;	// (0, 1)

				int gray = int((f10 - f00) * x + (f01 - f00) * y + (f11 + f00 - f10 - f01) * x * y + f00);
				new_img.at(new_x, new_y).gray(gray);
			}
		}
	}
}
inline void mean_filter_smooth(image_type& bmp_img, int n = 3)
{
	EXTL_ASSERT((n % 2));	// must be odd
	int mid = n >> 1;
	for (int px = 0; px < bmp_img.width() - n; ++px)
	{
		for (int py = 0; py < bmp_img.height() - n; ++py)
		{
			int avg = 0;
			for (int k = 0; k < n * n; ++k)
			{
				avg += bmp_img.at(px + k / n, py + k % n).gray();
			}
			avg /= n * n;
			bmp_img.at(px + mid, py + mid).gray(avg);
		}
	}
}
inline void xxxx_edge_detect(image_type& bmp_img, int hreshold)
{
	int grad;
	image_type tmp(bmp_img);
	for (int px = 1; px < bmp_img.width(); ++px)
	{
		for (int py = 1; py < bmp_img.height(); ++py)
		{
			// horizonal gradient
			grad = abs(bmp_img.at(px, py).gray() - bmp_img.at(px - 1, py).gray());
			tmp.at(px - 1, py).is_black(grad > hreshold);

			// vertical gradient
			grad = abs(bmp_img.at(px, py).gray() - bmp_img.at(px, py - 1).gray());
			tmp.at(px, py - 1).is_black(grad > hreshold? true : tmp.at(px, py - 1).is_black());	// merge
		}
	}
	bmp_img = tmp;
}
inline void edge_detect_impl(double* o1, int n, image_type& bmp_img, int hreshold)
{
	int mid = n >> 1;
	image_type tmp(bmp_img);
	for (int px = 0; px < bmp_img.width() - n; ++px)
	{
		for (int py = 0; py < bmp_img.height() - n; ++py)
		{
			double g1 = 0;
			for (int k = 0; k < n * n; ++k)
			{
				g1 += tmp.at(px + k % n, py + k / n).gray() * o1[k];
			}

			double g = fabs(g1);
			if (g / (n * n) > hreshold) bmp_img.at(px + mid, py + mid).is_black(true);
			else bmp_img.at(px + mid, py + mid).is_black(false);
		}
	}
}
inline void edge_detect_impl(double* o1, double* o2, int n, image_type& bmp_img, int hreshold)
{
	int mid = n >> 1;
	image_type tmp(bmp_img);
	for (int px = 0; px < bmp_img.width() - n; ++px)
	{
		for (int py = 0; py < bmp_img.height() - n; ++py)
		{
			double g1 = 0;
			double g2 = 0;
			for (int k = 0; k < n * n; ++k)
			{
				g1 += tmp.at(px + k / n, py + k % n).gray() * o1[k];
				g2 += tmp.at(px + k / n, py + k % n).gray() * o2[k];
			}

			double g = (fabs(g1) + fabs(g2)) / 2;
			//double g = sqrt(g1 * g1 + g2 * g2) / 2;
			if (g / (n * n) > hreshold) bmp_img.at(px + mid, py + mid).is_black(true);
			else bmp_img.at(px + mid, py + mid).is_black(false);
		}
	}
}
inline void edge_detect_impl(double* o1, double* o2, double* o3, int n, image_type& bmp_img, int hreshold)
{
	int mid = n >> 1;
	image_type tmp(bmp_img);
	for (int px = 0; px < bmp_img.width() - n; ++px)
	{
		for (int py = 0; py < bmp_img.height() - n; ++py)
		{
			double g1 = 0;
			double g2 = 0;
			double g3 = 0;
			for (int k = 0; k < n * n; ++k)
			{
				g1 += tmp.at(px + k / n, py + k % n).gray() * o1[k];
				g2 += tmp.at(px + k / n, py + k % n).gray() * o2[k];
				g3 += tmp.at(px + k / n, py + k % n).gray() * o3[k];
			}

			double g = (fabs(g1) + fabs(g2) + fabs(g3)) / 3;
			if (g / (n * n) > hreshold) bmp_img.at(px + mid, py + mid).is_black(true);
			else bmp_img.at(px + mid, py + mid).is_black(false);
		}
	}
}
inline void edge_detect_impl(double* o1, double* o2, double* o3, double* o4, int n, image_type& bmp_img, int hreshold)
{
	int mid = n >> 1;
	image_type tmp(bmp_img);
	for (int px = 0; px < bmp_img.width() - n; ++px)
	{
		for (int py = 0; py < bmp_img.height() - n; ++py)
		{
			double g1 = 0;
			double g2 = 0;
			double g3 = 0;
			double g4 = 0;
			for (int k = 0; k < n * n; ++k)
			{
				g1 += tmp.at(px + k / n, py + k % n).gray() * o1[k];
				g2 += tmp.at(px + k / n, py + k % n).gray() * o2[k];
				g3 += tmp.at(px + k / n, py + k % n).gray() * o3[k];
				g4 += tmp.at(px + k / n, py + k % n).gray() * o4[k];
			}

			double g = (fabs(g1) + fabs(g2) + fabs(g3) + fabs(g4)) / 4;
			if (g / (n * n) > hreshold) bmp_img.at(px + mid, py + mid).is_black(true);
			else bmp_img.at(px + mid, py + mid).is_black(false);
		}
	}
}
inline void edge_detect_impl(double* o1, double* o2, double* o3, double* o4, double* o5, double* o6, double* o7, double* o8, int n, image_type& bmp_img, int hreshold)
{
	int mid = n >> 1;
	image_type tmp(bmp_img);
	for (int px = 0; px < bmp_img.width() - n; ++px)
	{
		for (int py = 0; py < bmp_img.height() - n; ++py)
		{
			double g1 = 0;
			double g2 = 0;
			double g3 = 0;
			double g4 = 0;
			double g5 = 0;
			double g6 = 0;
			double g7 = 0;
			double g8 = 0;
			for (int k = 0; k < n * n; ++k)
			{
				g1 += tmp.at(px + k / n, py + k % n).gray() * o1[k];
				g2 += tmp.at(px + k / n, py + k % n).gray() * o2[k];
				g3 += tmp.at(px + k / n, py + k % n).gray() * o3[k];
				g4 += tmp.at(px + k / n, py + k % n).gray() * o4[k];
				g5 += tmp.at(px + k / n, py + k % n).gray() * o5[k];
				g6 += tmp.at(px + k / n, py + k % n).gray() * o6[k];
				g7 += tmp.at(px + k / n, py + k % n).gray() * o7[k];
				g8 += tmp.at(px + k / n, py + k % n).gray() * o8[k];
			}

			double g = (fabs(g1) + fabs(g2) + fabs(g3) + fabs(g4) + fabs(g5) + fabs(g6) + fabs(g7) + fabs(g8)) / 8;
			if (g / (n * n) > hreshold) bmp_img.at(px + mid, py + mid).is_black(true);
			else bmp_img.at(px + mid, py + mid).is_black(false);
		}
	}
}
inline void roberts_edge_detect(image_type& bmp_img, int hreshold = 3)
{
	double rx[4] =	{	1, 0
					,	0, -1
					};

	double ry[4] =	{	0, 1
					,	-1, 0
					};
	edge_detect_impl(rx, ry, 2, bmp_img, hreshold);
}
inline void sobel_2_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double s1[9] =	{	-1, -2, -1
					,	0, 0, 0
					,	1, 2, 1
					};

	double s2[9] =	{	-1, 0, 1
					,	-2, 0, 2
					,	-1, 0, 1
					};

	edge_detect_impl(s1, s2, 3, bmp_img, hreshold);
}
inline void sobel_4_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double s1[9] =	{	-1, -2, -1
					,	0, 0, 0
					,	1, 2, 1
					};

	double s2[9] =	{	-1, 0, 1
					,	-2, 0, 2
					,	-1, 0, 1
					};

	double s3[9] =	{	0, -1, -2
					,	1, 0, -1
					,	2, 1, 0
					};

	double s4[9] =	{	0, 1, 2
					,	-1, 0, 1
					,	-2, -1, 0
					};

	edge_detect_impl(s1, s2, s3, s4, 3, bmp_img, hreshold);
}
inline void prewitt_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double px[9] =	{	-1, -1, -1
					,	0, 0, 0
					,	1, 1, 1
					};

	double py[9] =	{	-1, 0, 1
					,	-1, 0, 1
					,	-1, 0, 1
					};

	edge_detect_impl(px, py, 3, bmp_img, hreshold);
}
inline void prewitt_7_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	 double hp[49] ={	0,   0,	0,	0,	0,	0,	0,
						0,   0,	0,	0,	0,	0,	0,
						-1,	-1,	-1,	-1,	-1,	-1,	-1,
						0,   0,	0,	0,	0,	0,	0,
						1,   1,	1,	1,	1,	1,	1,
						0,   0,	0,	0,	0,	0,	0,
						0,   0,	0,	0,	0,	0,	0,
					};
	 double vp[49] ={	0,	0,	-1,	0,	1,	0,	0,
						0,	0,	-1,	0,	1,	0,	0,
						0,	0,	-1,	0,	1,	0,	0,
						0,	0,	-1,	0,	1,	0,	0,
						0,	0,	-1,	0,	1,	0,	0,
						0,	0,	-1,	0,	1,	0,	0,
						0,	0,	-1,	0,	1,	0,	0,
					};
	edge_detect_impl(hp, vp, 7, bmp_img, hreshold);

}
inline void kirsch_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	5, 5, 5
					,	-3, 0, -3
					,	-3, -3, -3
					};
	double k2[9] =	{	-3, 5, 5
					,	-3, 0, 5
					,	-3, -3, -3
					};

	double k3[9] =	{	-3, -3, 5
					,	-3, 0, 5
					,	-3, -3, 5
					};

	double k4[9] =	{	-3, -3, -3
					,	-3, 0, 5
					,	-3, 5, 5
					};

	double k5[9] =	{	-3, -3, -3
					,	-3, 0, -3
					,	5, 5, 5
					};

	double k6[9] =	{	-3, -3, -3
					,	5, 0, -3
					,	5, 5, -3
					};

	double k7[9] =	{	5, -3, -3
					,	5, 0, -3
					,	5, -3, -3
					};

	double k8[9] =	{	5, 5, -3
					,	5, 0, -3
					,	-3, -3, -3
					};

	edge_detect_impl(k1, k2, k3, k4, k5, k6, k7, k8, 3, bmp_img, hreshold);
}
// horizontal
inline void kirsch_edge_detect_h(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	5, 5, 5
					,	-3, 0, -3
					,	-3, -3, -3
					};

	double k2[9] =	{	-3, -3, -3
					,	-3, 0, -3
					,	5, 5, 5
					};

	edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
// vertical
inline void kirsch_edge_detect_v(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	-3, -3, 5
					,	-3, 0, 5
					,	-3, -3, 5
					};

	double k2[9] =	{	5, -3, -3
					,	5, 0, -3
					,	5, -3, -3
					};

	edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
// right-diagonal
inline void kirsch_edge_detect_r(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	-3, 5, 5
					,	-3, 0, 5
					,	-3, -3, -3
					};

	double k2[9] =	{	-3, -3, -3
					,	5, 0, -3
					,	5, 5, -3
					};

	edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
// left-diagonal
inline void kirsch_edge_detect_l(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	5, 5, -3
					,	5, 0, -3
					,	-3, -3, -3
					};

	double k2[9] =	{	-3, -3, -3
					,	-3, 0, 5
					,	-3, 5, 5
					};

	edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
inline void isotropic_sobel_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double sx[9] =	{	-1, -1.414213, -1
					,	0, 0, 0
					,	1, 1.414213, 1
					};

	double sy[9] =	{	-1, 0, 1
					,	-1.414213, 0, 1.414213
					,	-1, 0, 1
					};

	edge_detect_impl(sx, sy, 3, bmp_img, hreshold);
}
inline void gauss_laplacian_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	 double op[25] ={	-2,	-4, -4,	-4,	-2,
						-4,	0,   8,	0,	-4,
						-4,	8,	24,	8,	-4,
						-4,	0,   8,	0,	-4,
						-2,	-4, -4,	-4,	-2
					};
	edge_detect_impl(op, 5, bmp_img, hreshold);

}
inline double marr_operator(int x, int y, double dr)
{
	double xy2 = double(x * x + y * y);
	double a = (xy2 - 2 * dr * dr) / (2 * 3.1415926 * dr * dr * dr * dr * dr * dr);
	double b = exp(-xy2 / (2 * dr * dr));
	return (a * b);
}

inline void marr_edge_detect(image_type& bmp_img, int hreshold = 5, int n = 5, double dr = 0.6)
{
	int marr_n = n >> 1;
	scoped_buffer<double> buf((2 * marr_n + 1) * (2 * marr_n + 1));

	for (int y = 0; y < n; ++y)
	{
		for (int x = 0; x < n; ++x)
		{
			buf[y * n + x] = marr_operator(x - marr_n, y - marr_n, dr);
		}
	}
	edge_detect_impl(buf.data(), n, bmp_img, hreshold);
}

inline void make_binarized_img(image_type& bmp_img, int hreshold)
{
	for (int px = 0; px < bmp_img.width(); ++px)
	{
		for (int py = 0; py < bmp_img.height(); ++py)
		{
			bmp_img.at(px, py).is_black(bmp_img.at(px, py).gray() < hreshold);
		}
	}
}

inline void overall_tilt_correction(image_type& bmp_img)
{
	int py, px;

	// calcualte left average height
	int left_h = 0;
	int left_n = 0;
	for (py = 0; py < bmp_img.height(); ++py)
	{
		for (px = 0; px < bmp_img.width() >> 1; ++px)
		{
			if (bmp_img.at(px, py).is_black())
			{
				left_h += py;
				++left_n;
			}
		}
	}
	left_h /= left_n;

	// calcualte right average height
	int right_h = 0;
	int right_n = 0;
	for (py = 0; py < bmp_img.height(); ++py)
	{
		for (px = bmp_img.width() >> 1; px < bmp_img.width(); ++px)
		{
			if (bmp_img.at(px, py).is_black())
			{
				right_h += py;
				++right_n;
			}
		}
	}
	right_h /= right_n;

	// calculate slope
	double slope = double(left_h - right_h) / (bmp_img.width() / 2);

	// clear
	image_type tmp(bmp_img);
	for (py = 0; py < bmp_img.height(); ++py)
		for (px = 0; px < bmp_img.width(); ++px)
			bmp_img.at(px, py).is_black(false);

	// correction
	for (py = 0; py < tmp.height(); ++py)
	{
		for (px = 0; px < tmp.width(); ++px)
		{
			if (tmp.at(px, py).is_black())
			{
				int new_y = int(py + (px - ((double)tmp.width() / 2)) * slope);
				if (new_y >= 0 && new_y < tmp.height())
				{
					bmp_img.at(px, new_y).is_black(true);
				}
			}
		}
	}
}

// rh: the hreshold of row pixel size
// hh: the hreshold of digital height
inline void split_row(image_type const& bmp_img, scoped_buffer<image_type>& row_imgs, int hh = 10)
{
	// simple binarized image
	image_type tmp(bmp_img);
	mean_filter_smooth(tmp);
	//sobel_4_edge_detect(tmp, 5);
	kirsch_edge_detect(tmp, 5);	// bold samples and binarized image for stats
	overall_tilt_correction(tmp);

	// correct raw image
	image_type raw_data(bmp_img);
	make_binarized_img(raw_data, 200);
	overall_tilt_correction(raw_data);

	// stats the number of pixels every rows
	int py, px;
	scoped_buffer<int> stats(tmp.height());
	for (py = 0; py < tmp.height(); ++py)
	{
		stats[py] = 0;
		for (px = 0; px < tmp.width(); ++px)
		{
			if (tmp.at(px, py).is_black())
				++stats[py];
		}
	}

	// stats minmum value
	int min_n = stats[0];
	for (py = 0; py < tmp.height(); ++py)
		min_n = stats[py] < min_n? stats[py] : min_n;

	// split rows
	basic_pair<int, int> sp;
	scoped_buffer<basic_pair<int, int> > sps;

	// the adaptive hreshold of row pixel size
	for (int rh = 5; rh < 100; ++rh)
	{
		sps.clear();

		int start_n = 0, end_n = 0;
		for (py = 0; py < tmp.height(); ++py)
		{
			if (stats[py] > min_n + rh)
			{
				// save start row
				if (++start_n == 1)
					sp.first(py);

				end_n = 0;
			}
			else
			{
				// save end row
				if (++end_n == 1 && start_n > hh)
				{
					sp.second(py);
					sps.push_back(sp);

					// draw seperator
					/*for (px = 0; px < tmp.width(); ++px)
					{
						tmp.at(px, sp.first()).is_black(true);
						tmp.at(px, sp.second()).is_black(true);
					}*/
				}
				start_n = 0;
			}
		}

		if (sps.size() == 5)
		{
			//EXTL_TRACE(_T("split row:%d"), rh);
			break;
		}
	}

	for (py = 0; py < (int)sps.size(); ++py)
	{
		// save images after spliting
		image_type row_img(raw_data.width(), sps[py].second() - sps[py].first());
		EXTL_ASSERT(sps[py].second() > sps[py].first());
		for (int k = sps[py].first(); k < sps[py].second(); ++k)
		{
			for (px = 0; px < raw_data.width(); ++px)
			{
				row_img.at(px, k - sps[py].first()).is_black(raw_data.at(px, k).is_black());
			}
		}
		row_imgs.push_back(row_img);
	}
}

inline void split_col(scoped_buffer<image_type>& row_imgs, scoped_buffer<image_type>& rowcol_imgs, int wh = 3)
{
	for (int col_i = 0; col_i < (int)row_imgs.size(); ++col_i)
	{
		// correct row_imgs
		overall_tilt_correction(row_imgs[col_i]);

		// split pre-handle
		image_type tmp(row_imgs[col_i]);
		mean_filter_smooth(tmp);
		kirsch_edge_detect(tmp, 5);	// bold samples and binarized image for stats
		overall_tilt_correction(tmp);

		// stats the number of pixels every columns
		int py, px;
		scoped_buffer<int> stats(tmp.width());
		for (px = 0; px < tmp.width(); ++px)
		{
			stats[px] = 0;
			for (py = 0; py < tmp.height(); ++py)
			{
				if (tmp.at(px, py).is_black())
					++stats[px];
			}
		}

		// stats minmum value
		int min_n = stats[0];
		for (px = 0; px < tmp.width(); ++px)
			min_n = stats[px] < min_n? stats[px] : min_n;

		// split columns
		basic_pair<int, int> sp;
		scoped_buffer<basic_pair<int, int> > sps;

		// the adaptive hreshold of column pixel size
		for (int ch = 1; ch < 50; ++ch)
		{
			sps.clear();

			int start_n = 0, end_n = 0;
			for (px = 0; px < tmp.width(); ++px)
			{
				if (stats[px] > min_n + ch)
				{
					// save start row
					if (++start_n == 1)
						sp.first(px);

					end_n = 0;
				}
				else
				{
					// save end row
					if (++end_n == 1 && start_n > wh)
					{
						sp.second(px);
						sps.push_back(sp);

						// draw seperator
						/*for (py = 0; py < tmp.height(); ++py)
						{
							tmp.at(py, sp.first()).is_black(true);
							tmp.at(py, sp.second()).is_black(true);
						}*/

					}
					start_n = 0;
				}
			}

			if (sps.size() == 10)
			{
				//EXTL_TRACE(_T("split col:%d"), ch);
				break;
			}
		}

		for (py = 0; py < (int)sps.size(); ++py)
		{
			// save images after spliting
			image_type img(sps[py].second() - sps[py].first(), row_imgs[col_i].height());
			EXTL_ASSERT(sps[py].second() > sps[py].first());
			for (int pi = 0; pi < row_imgs[col_i].height(); ++pi)
			{
				for (int pj = sps[py].first(); pj < sps[py].second(); ++pj)
				{
					img.at(pj - sps[py].first(), pi).is_black(row_imgs[col_i].at(pj, pi).is_black());
				}
			}
			rowcol_imgs.push_back(img);
		}
		//show_img(tmp);
	}
}
// calculate the real position of image included pixels
inline void calc_real_pos(image_type const& bmp_img, basic_rect<int>& pos)
{
	int margin = 3;

	pos.clear();

	// stats the number of pixels every rows
	int py, px;
	scoped_buffer<int> hstats(bmp_img.height());
	for (py = 0; py < bmp_img.height(); ++py)
	{
		hstats[py] = 0;
		for (px = 0; px < bmp_img.width(); ++px)
		{
			if (bmp_img.at(px, py).is_black())
				++hstats[py];
		}
	}

	// split by height
	for (py = 0; py < bmp_img.height(); ++py)
	{
		if (hstats[py] > 0)
		{
			pos.top(py);
			break;
		}
	}
	if (py == bmp_img.height()) pos.top(bmp_img.height() - 1);
	if (pos.top() - margin >= 0) pos.top(pos.top() - margin);

	for (py = bmp_img.height(); py > 0; --py)
	{
		if (hstats[py - 1] > 0)
		{
			pos.bottom(py - 1);
			break;
		}
	}
	if (py == 0) pos.bottom(0);
	if (pos.bottom() + margin < bmp_img.height()) pos.bottom(pos.bottom() + margin);
	EXTL_ASSERT(pos.bottom() > pos.top());

	// stats the number of pixels every columns
	scoped_buffer<int> wstats(bmp_img.width());
	for (px = 0; px < bmp_img.width(); ++px)
	{
		wstats[px] = 0;
		for (py = 0; py < bmp_img.height(); ++py)
		{
			if (bmp_img.at(px, py).is_black())
				++wstats[px];
		}
	}

	// split by width
	for (px = 0; px < bmp_img.width(); ++px)
	{
		if (wstats[px] > 0)
		{
			pos.left(px);
			break;
		}
	}
	if (px == bmp_img.width()) pos.left(bmp_img.width() - 1);
	if (pos.left() - margin >= 0) pos.left(pos.left() - margin);

	for (px = bmp_img.width(); px > 0; --px)
	{
		if (wstats[px - 1] > 0)
		{
			pos.right(px - 1);
			break;
		}
	}
	if (px == 0) pos.right(0);
	if (pos.right() + margin < bmp_img.width()) pos.right(pos.right() + margin);
	EXTL_ASSERT(pos.right() > pos.left());
}

inline void horizontal_side_slip_deskew_img(image_type const& bmp_img, image_type& new_img)
{
	int py, px;
	double angle = EXTL_PI / 4;

	image_type mid_tmp(bmp_img.width() + 10, bmp_img.height() + 10);

	for (py = 0; py < mid_tmp.height(); ++py)
	{
		for (px = 0; px < mid_tmp.width(); ++px)
		{
			if (py < 5 || px < 5 || py >= mid_tmp.height() - 5 || px >= mid_tmp.width() - 5)
				mid_tmp.at(px, py).is_black(false);
			else mid_tmp.at(px, py).is_black(bmp_img.at(px - 5, py - 5).is_black());
		}
	}

	while (angle > EXTL_PI / 180)
	{
		// calculate the real position of image included pixels
		basic_rect<int> mid_pos;
		calc_real_pos(mid_tmp, mid_pos);

		// left transform;
		image_type left_tmp(mid_tmp.width(), mid_tmp.height());
		for (py = 0; py < left_tmp.height(); ++py)
			for (px = 0; px < left_tmp.width(); ++px)
				left_tmp.at(px, py).is_black(false);

		for (py = 0; py < left_tmp.height(); ++py)
		{
			for (px = 0; px < left_tmp.width(); ++px)
			{
				if (mid_tmp.at(px, py).is_black())
				{
					double slope = tan(EXTL_PI / 2 + angle);
					int new_x = int(px - (py - ((double)left_tmp.height() / 2)) / slope);
					if (new_x >= 0 && new_x < left_tmp.width())
						left_tmp.at(new_x, py).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> left_pos;
		calc_real_pos(left_tmp, left_pos);

		// right transform;
		image_type right_tmp(mid_tmp.width(), mid_tmp.height());
		for (py = 0; py < right_tmp.height(); ++py)
			for (px = 0; px < right_tmp.width(); ++px)
				right_tmp.at(px, py).is_black(false);

		for (py = 0; py < right_tmp.height(); ++py)
		{
			for (px = 0; px < right_tmp.width(); ++px)
			{
				if (mid_tmp.at(px, py).is_black())
				{
					double slope = tan(EXTL_PI / 2 - angle);
					int new_x = int(px - (py - ((double)right_tmp.height() / 2)) / slope);
					if (new_x >= 0 && new_x < right_tmp.width())
						right_tmp.at(new_x, py).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> right_pos;
		calc_real_pos(right_tmp, right_pos);

		// select better image
		if (right_pos.width() < left_pos.width())
		{
			if (right_pos.width() < mid_pos.width())
				mid_tmp = right_tmp;
		}
		else
		{
			if (left_pos.width() < mid_pos.width())
				mid_tmp = left_tmp;
		}

		angle /= 2;
	}

	// update
	basic_rect<int> mid_pos;
	calc_real_pos(mid_tmp, mid_pos);
	image_type tmp(mid_pos.width(), mid_pos.height());
	for (py = mid_pos.top(); py <= mid_pos.bottom(); ++py)
		for (px = mid_pos.left(); px <= mid_pos.right(); ++px)
			tmp.at(px - mid_pos.left(), py - mid_pos.top()).is_black(mid_tmp.at(px, py).is_black());
	new_img = tmp;
}
inline void vertical_side_slip_deskew_img(image_type const& bmp_img, image_type& new_img)
{
	int py, px;
	double angle = EXTL_PI / 8;

	image_type mid_tmp(bmp_img.height() + 10, bmp_img.width() + 10);
	for (py = 0; py < mid_tmp.height(); ++py)
	{
		for (px = 0; px < mid_tmp.width(); ++px)
		{
			if (py < 5 || px < 5 || py >= mid_tmp.height() - 5 || px >= mid_tmp.width() - 5)
				mid_tmp.at(px, py).is_black(false);
			else mid_tmp.at(px, py).is_black(bmp_img.at(py - 5, px - 5).is_black());
		}
	}

	while (angle > EXTL_PI / 180)
	{
		// calculate the real position of image included pixels
		basic_rect<int> mid_pos;
		calc_real_pos(mid_tmp, mid_pos);

		// top transform;
		image_type top_tmp(mid_tmp.height(), mid_tmp.width());
		for (py = 0; py < top_tmp.height(); ++py)
			for (px = 0; px < top_tmp.width(); ++px)
				top_tmp.at(px, py).is_black(false);

		for (py = 0; py < top_tmp.height(); ++py)
		{
			for (px = 0; px < top_tmp.width(); ++px)
			{
				if (mid_tmp.at(px, py).is_black())
				{
					double slope = tan(-angle);
					int new_i = int(py + (px - ((double)top_tmp.width() / 2)) * slope);
					if (new_i >= 0 && new_i < top_tmp.height())
						top_tmp.at(new_i, px).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> top_pos;
		calc_real_pos(top_tmp, top_pos);

		// bottom transform;
		image_type bottom_tmp(mid_tmp.height(), mid_tmp.width());
		for (py = 0; py < bottom_tmp.height(); ++py)
			for (px = 0; px < bottom_tmp.width(); ++px)
				bottom_tmp.at(px, py).is_black(false);

		for (py = 0; py < bottom_tmp.height(); ++py)
		{
			for (px = 0; px < bottom_tmp.width(); ++px)
			{
				if (mid_tmp.at(px, py).is_black())
				{
					double slope = tan(angle);
					int new_i = int(py + (px - ((double)bottom_tmp.width() / 2)) * slope);
					if (new_i >= 0 && new_i < bottom_tmp.height())
						bottom_tmp.at(new_i, px).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> bottom_pos;
		calc_real_pos(bottom_tmp, bottom_pos);

		// select better image
		if (bottom_pos.height() < top_pos.height())
		{
			if (bottom_pos.height() < mid_pos.height())
				mid_tmp = bottom_tmp;
		}
		else
		{
			if (top_pos.height() < mid_pos.height())
				mid_tmp = top_tmp;
		}

		angle /= 2;
	}

	// update
	basic_rect<int> mid_pos;
	calc_real_pos(mid_tmp, mid_pos);
	image_type tmp(mid_pos.height(), mid_pos.width());
	for (py = mid_pos.top(); py <= mid_pos.bottom(); ++py)
		for (px = mid_pos.left(); px <= mid_pos.right(); ++px)
			tmp.at(py - mid_pos.top(), px - mid_pos.left()).is_black(mid_tmp.at(px, py).is_black());
	new_img = tmp;
}
inline void split_digital(scoped_buffer<image_type>& rowcol_imgs, scoped_buffer<image_type>& digital_imgs)
{
	for (int i = 0; i < (int)rowcol_imgs.size(); ++i)
	{
		// calculate the real position of image included pixels
		basic_rect<int> pos;
		calc_real_pos(rowcol_imgs[i], pos);

		// save splited image
		image_type img(pos.width(), pos.height());
		for (int py = pos.top(); py <= pos.bottom(); ++py)
		{
			for (int px = pos.left(); px <= pos.right(); ++px)
			{
				img.at(px - pos.left(), py - pos.top()).is_black(rowcol_imgs[i].at(px, py).is_black());
			}
		}
		digital_imgs.push_back(img);
	}
}

inline void part_deskew(scoped_buffer<image_type>& digital_imgs, scoped_buffer<image_type>& deskewed_imgs)
{
	// deskew
	for (int i = 0; i < (int)digital_imgs.size(); ++i)
	{
		image_type new_img(digital_imgs[i].width(), digital_imgs[i].height());
		horizontal_side_slip_deskew_img(digital_imgs[i], new_img);

		deskewed_imgs.push_back(new_img);
	}
}
// thinning in-place for connectivity
inline void thinning(image_type& bmp_img, int max_n = 10)
{
	double k1[9] =	{	0, 0, 0
					,	2, 1, 2
					,	1, 1, 1
					};
	double k2[9] =	{	1, 2, 0
					,	1, 1, 0
					,	1, 2, 0
					};

	double k3[9] =	{	1, 1, 1
					,	2, 1, 2
					,	0, 0, 0
					};

	double k4[9] =	{	0, 2, 1
					,	0, 1, 1
					,	0, 2, 1
					};

	double k5[9] =	{	1, 1, 2
					,	1, 1, 0
					,	2, 0, 0
					};

	double k6[9] =	{	2, 1, 1
					,	0, 1, 1
					,	0, 0, 2
					};

	double k7[9] =	{	0, 0, 2
					,	0, 1, 1
					,	2, 1, 1
					};

	double k8[9] =	{	2, 0, 0
					,	1, 1, 0
					,	1, 1, 2
					};

	double k9[9] =	{	2, 1, 2
					,	1, 1, 0
					,	2, 0, 0
					};

	double k10[9] =	{	2, 1, 2
					,	0, 1, 1
					,	0, 0, 2
					};

	double k11[9] =	{	0, 0, 2
					,	0, 1, 1
					,	2, 1, 2
					};

	double k12[9] =	{	2, 0, 0
					,	1, 1, 0
					,	2, 1, 2
					};

	int kn = 3;
	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_k1, is_matched_k2, is_matched_k3, is_matched_k4;
		bool is_matched_k5, is_matched_k6, is_matched_k7, is_matched_k8;
		bool is_matched_k9, is_matched_k10, is_matched_k11, is_matched_k12;
		for (int py = 0; py < bmp_img.height() - kn; ++py)
		{
			for (int px = 0; px < bmp_img.width() - kn; ++px)
			{
				int k;

				// k1
				is_matched_k1 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k1[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k1[k])
					{
						is_matched_k1 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k1[k])
					{
						is_matched_k1 = false;
						break;
					}
				}
				if (is_matched_k1) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k2
				is_matched_k2 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k2[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k2[k])
					{
						is_matched_k2 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k2[k])
					{
						is_matched_k2 = false;
						break;
					}
				}
				if (is_matched_k2) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k3
				is_matched_k3 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k3[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k3[k])
					{
						is_matched_k3 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k3[k])
					{
						is_matched_k3 = false;
						break;
					}
				}
				if (is_matched_k3) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k4
				is_matched_k4 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k4[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k4[k])
					{
						is_matched_k4 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k4[k])
					{
						is_matched_k4 = false;
						break;
					}
				}
				if (is_matched_k4) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k5
				is_matched_k5 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k5[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k5[k])
					{
						is_matched_k5 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k5[k])
					{
						is_matched_k5 = false;
						break;
					}
				}
				if (is_matched_k5) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k6
				is_matched_k6 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k6[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k6[k])
					{
						is_matched_k6 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k6[k])
					{
						is_matched_k6 = false;
						break;
					}
				}
				if (is_matched_k6) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k7
				is_matched_k7 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k7[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k7[k])
					{
						is_matched_k7 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k7[k])
					{
						is_matched_k7 = false;
						break;
					}
				}
				if (is_matched_k7) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k8
				is_matched_k8 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k8[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k8[k])
					{
						is_matched_k8 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k8[k])
					{
						is_matched_k8 = false;
						break;
					}
				}
				if (is_matched_k8) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k9
				is_matched_k9 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k9[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k9[k])
					{
						is_matched_k9 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k9[k])
					{
						is_matched_k9 = false;
						break;
					}
				}
				if (is_matched_k9) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k10
				is_matched_k10 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k10[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k10[k])
					{
						is_matched_k10 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k10[k])
					{
						is_matched_k10 = false;
						break;
					}
				}
				if (is_matched_k10) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k11
				is_matched_k11 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k11[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k11[k])
					{
						is_matched_k11 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k11[k])
					{
						is_matched_k11 = false;
						break;
					}
				}
				if (is_matched_k11) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k12
				is_matched_k12 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k12[k]) continue;
					if (bmp_img.at(px + k % kn, py + k / kn).is_black() && 1 != k12[k])
					{
						is_matched_k12 = false;
						break;
					}

					if (!bmp_img.at(px + k % kn, py + k / kn).is_black() && 0 != k12[k])
					{
						is_matched_k12 = false;
						break;
					}
				}
				if (is_matched_k12) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				if (	is_matched_k1
					||	is_matched_k2
					||	is_matched_k3
					||	is_matched_k4
					||	is_matched_k5
					||	is_matched_k6
					||	is_matched_k7
					||	is_matched_k8
					||	is_matched_k9
					||	is_matched_k10
					||	is_matched_k11
					||	is_matched_k12
					)
				{
					matched_n++;
				}
			}
		}

		if (matched_n <= 0)
		{
			break;
		}
	}

}

// pruning
inline void pruning(image_type& bmp_img, int max_n = 2)
{


	double k1[9] =	{	1, 0, 0
					,	0, 1, 0
					,	0, 0, 0
					};

	double k2[9] =	{	0, 0, 1
					,	0, 1, 0
					,	0, 0, 0
					};

	double k3[9] =	{	0, 0, 0
					,	0, 1, 0
					,	0, 0, 1
					};

	double k4[9] =	{	0, 0, 0
					,	0, 1, 0
					,	1, 0, 0
					};

	double k5[9] =	{	0, 0, 0
					,	1, 1, 0
					,	0, 0, 0
					};

	double k6[9] =	{	0, 1, 0
					,	0, 1, 0
					,	0, 0, 0
					};

	double k7[9] =	{	0, 0, 0
					,	0, 1, 1
					,	0, 0, 0
					};

	double k8[9] =	{	0, 0, 0
					,	0, 1, 0
					,	0, 1, 0
					};

	int kn = 3;
	image_type tmp(bmp_img);
	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_k1, is_matched_k2, is_matched_k3, is_matched_k4;
		bool is_matched_k5, is_matched_k6, is_matched_k7, is_matched_k8;
		for (int py = 0; py < tmp.height() - kn; ++py)
		{
			for (int px = 0; px < tmp.width() - kn; ++px)
			{
				int k;

				// k1
				is_matched_k1 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k1[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k1[k])
					{
						is_matched_k1 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k1[k])
					{
						is_matched_k1 = false;
						break;
					}
				}
				if (is_matched_k1) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k2
				is_matched_k2 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k2[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k2[k])
					{
						is_matched_k2 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k2[k])
					{
						is_matched_k2 = false;
						break;
					}
				}
				if (is_matched_k2) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k3
				is_matched_k3 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k3[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k3[k])
					{
						is_matched_k3 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k3[k])
					{
						is_matched_k3 = false;
						break;
					}
				}
				if (is_matched_k3) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k4
				is_matched_k4 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k4[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k4[k])
					{
						is_matched_k4 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k4[k])
					{
						is_matched_k4 = false;
						break;
					}
				}
				if (is_matched_k4) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k5
				is_matched_k5 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k5[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k5[k])
					{
						is_matched_k5 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k5[k])
					{
						is_matched_k5 = false;
						break;
					}
				}
				if (is_matched_k5) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k6
				is_matched_k6 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k6[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k6[k])
					{
						is_matched_k6 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k6[k])
					{
						is_matched_k6 = false;
						break;
					}
				}
				if (is_matched_k6) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k7
				is_matched_k7 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k7[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k7[k])
					{
						is_matched_k7 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k7[k])
					{
						is_matched_k7 = false;
						break;
					}
				}
				if (is_matched_k7) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);

				// k8
				is_matched_k8 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k8[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k8[k])
					{
						is_matched_k8 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k8[k])
					{
						is_matched_k8 = false;
						break;
					}
				}
				if (is_matched_k8) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(false);


				if (	is_matched_k1
					||	is_matched_k2
					||	is_matched_k3
					||	is_matched_k4
					||	is_matched_k5
					||	is_matched_k6
					||	is_matched_k7
					||	is_matched_k8
					)
				{
					matched_n++;
				}
			}
		}

		if (matched_n <= 0)
		{
			break;
		}
		else tmp = bmp_img;
	}
}
inline void roughening(image_type& bmp_img, int max_n = 1)
{
	double k1[9] =	{	0, 0, 0
					,	2, 0, 2
					,	1, 1, 1
					};
	double k2[9] =	{	1, 2, 0
					,	1, 0, 0
					,	1, 2, 0
					};

	double k3[9] =	{	1, 1, 1
					,	2, 0, 2
					,	0, 0, 0
					};

	double k4[9] =	{	0, 2, 1
					,	0, 0, 1
					,	0, 2, 1
					};

	double k5[9] =	{	1, 1, 2
					,	1, 0, 0
					,	2, 0, 0
					};

	double k6[9] =	{	2, 1, 1
					,	0, 0, 1
					,	0, 0, 2
					};

	double k7[9] =	{	0, 0, 2
					,	0, 0, 1
					,	2, 1, 1
					};

	double k8[9] =	{	2, 0, 0
					,	1, 0, 0
					,	1, 1, 2
					};

	double k9[9] =	{	2, 1, 2
					,	1, 0, 0
					,	2, 0, 0
					};

	double k10[9] =	{	2, 1, 2
					,	0, 0, 1
					,	0, 0, 2
					};

	double k11[9] =	{	0, 0, 2
					,	0, 0, 1
					,	2, 1, 2
					};

	double k12[9] =	{	2, 0, 0
					,	1, 0, 0
					,	2, 1, 2
					};

	int kn = 3;

	// note: it's different from thinning to need to backup every time
	image_type tmp(bmp_img);

	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_k1, is_matched_k2, is_matched_k3, is_matched_k4;
		bool is_matched_k5, is_matched_k6, is_matched_k7, is_matched_k8;
		bool is_matched_k9, is_matched_k10, is_matched_k11, is_matched_k12;
		for (int py = 0; py < tmp.height() - kn; ++py)
		{
			for (int px = 0; px < tmp.width() - kn; ++px)
			{
				int k;

				// k1
				is_matched_k1 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k1[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k1[k])
					{
						is_matched_k1 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k1[k])
					{
						is_matched_k1 = false;
						break;
					}
				}
				if (is_matched_k1) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k2
				is_matched_k2 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k2[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k2[k])
					{
						is_matched_k2 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k2[k])
					{
						is_matched_k2 = false;
						break;
					}
				}
				if (is_matched_k2) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k3
				is_matched_k3 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k3[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k3[k])
					{
						is_matched_k3 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k3[k])
					{
						is_matched_k3 = false;
						break;
					}
				}
				if (is_matched_k3) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k4
				is_matched_k4 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k4[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k4[k])
					{
						is_matched_k4 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k4[k])
					{
						is_matched_k4 = false;
						break;
					}
				}
				if (is_matched_k4) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k5
				is_matched_k5 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k5[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k5[k])
					{
						is_matched_k5 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k5[k])
					{
						is_matched_k5 = false;
						break;
					}
				}
				if (is_matched_k5) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k6
				is_matched_k6 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k6[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k6[k])
					{
						is_matched_k6 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k6[k])
					{
						is_matched_k6 = false;
						break;
					}
				}
				if (is_matched_k6) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k7
				is_matched_k7 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k7[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k7[k])
					{
						is_matched_k7 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k7[k])
					{
						is_matched_k7 = false;
						break;
					}
				}
				if (is_matched_k7) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k8
				is_matched_k8 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k8[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k8[k])
					{
						is_matched_k8 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k8[k])
					{
						is_matched_k8 = false;
						break;
					}
				}
				if (is_matched_k8) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k9
				is_matched_k9 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k9[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k9[k])
					{
						is_matched_k9 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k9[k])
					{
						is_matched_k9 = false;
						break;
					}
				}
				if (is_matched_k9) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k10
				is_matched_k10 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k10[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k10[k])
					{
						is_matched_k10 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k10[k])
					{
						is_matched_k10 = false;
						break;
					}
				}
				if (is_matched_k10) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k11
				is_matched_k11 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k11[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k11[k])
					{
						is_matched_k11 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k11[k])
					{
						is_matched_k11 = false;
						break;
					}
				}
				if (is_matched_k11) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);

				// k12
				is_matched_k12 = true;
				for (k = 0; k < kn * kn; ++k)
				{
					if (2 == k12[k]) continue;
					if (tmp.at(px + k / kn, py + k % kn).is_black() && 1 != k12[k])
					{
						is_matched_k12 = false;
						break;
					}

					if (!tmp.at(px + k / kn, py + k % kn).is_black() && 0 != k12[k])
					{
						is_matched_k12 = false;
						break;
					}
				}
				if (is_matched_k12) bmp_img.at(px + (kn >> 1), py + (kn >> 1)).is_black(true);
				if (	is_matched_k1
					||	is_matched_k2
					||	is_matched_k3
					||	is_matched_k4
					||	is_matched_k5
					||	is_matched_k6
					||	is_matched_k7
					||	is_matched_k8
					||	is_matched_k9
					||	is_matched_k10
					||	is_matched_k11
					||	is_matched_k12
					)
				{
					matched_n++;
				}
			}

		}

		if (matched_n <= 0)
		{
			break;
		}
		else tmp = bmp_img;
	}

}

inline void normalize(scoped_buffer<image_type>& deskewed_imgs, scoped_buffer<image_type>& normalized_imgs, int w = IMAGE_W, int h = IMAGE_H)
{
	// normalize
	for (int py = 0; py < (int)deskewed_imgs.size(); ++py)
	{
		image_type new_img(w, h);

		nearest_neighbor_zoom(deskewed_imgs[py], new_img);

		//roughening(new_img);
		//thinning(new_img);
		//pruning(new_img);
		normalized_imgs.push_back(new_img);
	}
}


#endif // SAMPLE_HELPER_H
