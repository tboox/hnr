#ifndef SH_ED_H
#define SH_ED_H

inline void sh_ed_xxxx_edge_detect(image_type& bmp_img, int hreshold)
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
inline void sh_ed_edge_detect_impl(double* o1, int n, image_type& bmp_img, int hreshold)
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
inline void sh_ed_edge_detect_impl(double* o1, double* o2, int n, image_type& bmp_img, int hreshold)
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
inline void sh_ed_edge_detect_impl(double* o1, double* o2, double* o3, int n, image_type& bmp_img, int hreshold)
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
inline void sh_ed_edge_detect_impl(double* o1, double* o2, double* o3, double* o4, int n, image_type& bmp_img, int hreshold)
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
inline void sh_ed_edge_detect_impl(double* o1, double* o2, double* o3, double* o4, double* o5, double* o6, double* o7, double* o8, int n, image_type& bmp_img, int hreshold)
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
inline void sh_ed_roberts_edge_detect(image_type& bmp_img, int hreshold = 3)
{
	double rx[4] =	{	1, 0
					,	0, -1
					};

	double ry[4] =	{	0, 1
					,	-1, 0
					};
	sh_ed_edge_detect_impl(rx, ry, 2, bmp_img, hreshold);
}
inline void sh_ed_sobel_2_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double s1[9] =	{	-1, -2, -1
					,	0, 0, 0
					,	1, 2, 1
					};

	double s2[9] =	{	-1, 0, 1
					,	-2, 0, 2
					,	-1, 0, 1
					};

	sh_ed_edge_detect_impl(s1, s2, 3, bmp_img, hreshold);
}
inline void sh_ed_sobel_4_edge_detect(image_type& bmp_img, int hreshold = 5)
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

	sh_ed_edge_detect_impl(s1, s2, s3, s4, 3, bmp_img, hreshold);
}
inline void sh_ed_prewitt_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double px[9] =	{	-1, -1, -1
					,	0, 0, 0
					,	1, 1, 1
					};

	double py[9] =	{	-1, 0, 1
					,	-1, 0, 1
					,	-1, 0, 1
					};

	sh_ed_edge_detect_impl(px, py, 3, bmp_img, hreshold);
}
inline void sh_ed_prewitt_7_edge_detect(image_type& bmp_img, int hreshold = 5)
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
	sh_ed_edge_detect_impl(hp, vp, 7, bmp_img, hreshold);

}
inline void sh_ed_kirsch_edge_detect(image_type& bmp_img, int hreshold = 5)
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

	sh_ed_edge_detect_impl(k1, k2, k3, k4, k5, k6, k7, k8, 3, bmp_img, hreshold);
}
// horizontal
inline void sh_ed_kirsch_edge_detect_h(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	5, 5, 5
					,	-3, 0, -3
					,	-3, -3, -3
					};

	double k2[9] =	{	-3, -3, -3
					,	-3, 0, -3
					,	5, 5, 5
					};

	sh_ed_edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
// vertical
inline void sh_ed_kirsch_edge_detect_v(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	-3, -3, 5
					,	-3, 0, 5
					,	-3, -3, 5
					};

	double k2[9] =	{	5, -3, -3
					,	5, 0, -3
					,	5, -3, -3
					};

	sh_ed_edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
// right-diagonal
inline void sh_ed_kirsch_edge_detect_r(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	-3, 5, 5
					,	-3, 0, 5
					,	-3, -3, -3
					};

	double k2[9] =	{	-3, -3, -3
					,	5, 0, -3
					,	5, 5, -3
					};

	sh_ed_edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
// left-diagonal
inline void sh_ed_kirsch_edge_detect_l(image_type& bmp_img, int hreshold = 5)
{
	double k1[9] =	{	5, 5, -3
					,	5, 0, -3
					,	-3, -3, -3
					};

	double k2[9] =	{	-3, -3, -3
					,	-3, 0, 5
					,	-3, 5, 5
					};

	sh_ed_edge_detect_impl(k1, k2, 3, bmp_img, hreshold);
}
inline void sh_ed_isotropic_sobel_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	double sx[9] =	{	-1, -1.414213, -1
					,	0, 0, 0
					,	1, 1.414213, 1
					};

	double sy[9] =	{	-1, 0, 1
					,	-1.414213, 0, 1.414213
					,	-1, 0, 1
					};

	sh_ed_edge_detect_impl(sx, sy, 3, bmp_img, hreshold);
}
inline void sh_ed_gauss_laplacian_edge_detect(image_type& bmp_img, int hreshold = 5)
{
	 double op[25] ={	-2,	-4, -4,	-4,	-2,
						-4,	0,   8,	0,	-4,
						-4,	8,	24,	8,	-4,
						-4,	0,   8,	0,	-4,
						-2,	-4, -4,	-4,	-2
					};
	sh_ed_edge_detect_impl(op, 5, bmp_img, hreshold);

}
inline double marr_operator(int x, int y, double dr)
{
	double xy2 = double(x * x + y * y);
	double a = (xy2 - 2 * dr * dr) / (2 * 3.1415926 * dr * dr * dr * dr * dr * dr);
	double b = exp(-xy2 / (2 * dr * dr));
	return (a * b);
}

inline void sh_ed_marr_edge_detect(image_type& bmp_img, int hreshold = 5, int n = 5, double dr = 0.6)
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
	sh_ed_edge_detect_impl(buf.data(), n, bmp_img, hreshold);
}

#endif // SH_ED_H
