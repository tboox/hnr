#ifndef SH_TN_H
#define SH_TN_H

#include "prefix.h"
#include "sh_hp.h"
#include "sh_fx.h"

inline image_type sh_tn_thinning_1(image_type const& old_img, int max_n = 200)
{
	double k1[9] =	{	1, 0, -1
					,	1, 2, -1
					,	1, 0, -1
					};

	double k2[9] =	{	1, 1, 1
					,	0, 2, 0
					,	-1, -1, -1
					};

	double k3[9] =	{	-1, 0, 1
					,	-1, 2, 1
					,	-1, 0, 1
					};

	double k4[9] =	{	-1, -1, -1
					,	0, 2, 0
					,	1, 1, 1
					};

	double k5[9] =	{	1, 1, 0
					,	1, 2, -1
					,	0, -1, -1
					};

	double k6[9] =	{	0, 1, 1
					,	-1, 2, 1
					,	-1, -1, 0
					};

	double k7[9] =	{	-1, -1, 0
					,	-1, 2, 1
					,	0, 1, 1
					};

	double k8[9] =	{	0, -1, -1
					,	1, 2, -1
					,	1, 1, 0
					};

	double k9[9] =	{	0, 1, 0
					,	1, 2, -1
					,	0, -1, -1
					};

	double k10[9] =	{	0, 1, 0
					,	-1, 2, 1
					,	-1, -1, 0
					};

	double k11[9] =	{	-1, -1, 0
					,	-1, 2, 1
					,	0, 1, 0
					};

	double k12[9] =	{	0, -1, -1
					,	1, 2, -1
					,	0, 1, 0
					};

	int kn = 3;
	image_type new_img(old_img);
	image_type tmp(new_img);
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
				is_matched_k1 = sh_hp_match(tmp, new_img, px, py, k1, 3, 3);
				is_matched_k2 = sh_hp_match(tmp, new_img, px, py, k2, 3, 3);
				is_matched_k3 = sh_hp_match(tmp, new_img, px, py, k3, 3, 3);
				is_matched_k4 = sh_hp_match(tmp, new_img, px, py, k4, 3, 3);
				is_matched_k5 = sh_hp_match(tmp, new_img, px, py, k5, 3, 3);
				is_matched_k6 = sh_hp_match(tmp, new_img, px, py, k6, 3, 3);
				is_matched_k7 = sh_hp_match(tmp, new_img, px, py, k7, 3, 3);
				is_matched_k8 = sh_hp_match(tmp, new_img, px, py, k8, 3, 3);
				is_matched_k9 = sh_hp_match(tmp, new_img, px, py, k9, 3, 3);
				is_matched_k10 = sh_hp_match(tmp, new_img, px, py, k10, 3, 3);
				is_matched_k11 = sh_hp_match(tmp, new_img, px, py, k11, 3, 3);
				is_matched_k12 = sh_hp_match(tmp, new_img, px, py, k12, 3, 3);

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

		if (matched_n <= 0) break;
		else tmp = new_img;
	}

	return new_img;
}
inline image_type sh_tn_thinning_4(image_type const& old_img, int max_n = 200)
{
	static e_byte_t erase_table[256] =
	{
		0,0,1,1,0,0,1,1,			1,1,0,1,1,1,0,1,
		1,1,0,0,1,1,1,1,			0,0,0,0,0,0,0,1,
		0,0,1,1,0,0,1,1,			1,1,0,1,1,1,0,1,
		1,1,0,0,1,1,1,1,			0,0,0,0,0,0,0,1,
		1,1,0,0,1,1,0,0,			0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,			0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,0,0,			1,1,0,1,1,1,0,1,
		0,0,0,0,0,0,0,0,			0,0,0,0,0,0,0,0,
		0,0,1,1,0,0,1,1,			1,1,0,1,1,1,0,1,
		1,1,0,0,1,1,1,1,			0,0,0,0,0,0,0,1,
		0,0,1,1,0,0,1,1,			1,1,0,1,1,1,0,1,
		1,1,0,0,1,1,1,1,			0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,0,0,			0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,1,1,			0,0,0,0,0,0,0,0,
		1,1,0,0,1,1,0,0,			1,1,0,1,1,1,0,0,
		1,1,0,0,1,1,1,0,			1,1,0,0,1,0,0,0
	};

	image_type new_img(old_img);
	bool is_horizontal = true;
	while (max_n--)
	{
		image_type tmp_img(new_img);
		int erase_n = 0;
		if (is_horizontal)
		{
			for (int py = 0; py < (int)tmp_img.height() - 3; ++py)
			{
				for (int px = 0; px < (int)tmp_img.width() - 3; ++px)
				{
					if (tmp_img.at(px + 1, py + 1).is_black())
					{
						e_byte_t p1 = !tmp_img.at(px + 0, py + 0).is_black();
						e_byte_t p2 = !tmp_img.at(px + 0, py + 1).is_black();
						e_byte_t p3 = !tmp_img.at(px + 0, py + 2).is_black();
						e_byte_t p4 = !tmp_img.at(px + 1, py + 0).is_black();
						e_byte_t p6 = !tmp_img.at(px + 1, py + 2).is_black();
						e_byte_t p7 = !tmp_img.at(px + 2, py + 0).is_black();
						e_byte_t p8 = !tmp_img.at(px + 2, py + 1).is_black();
						e_byte_t p9 = !tmp_img.at(px + 2, py + 2).is_black();

						e_byte_t index = p1 + (p2 << 1) + (p3 << 2) + (p4 << 3) + (p6 << 4) + (p7 << 5) + (p8 << 6) + (p9 << 7);
						EXTL_ASSERT(index < 256);
						if (!(!p4 && !p6) && erase_table[index])
						{
							new_img.at(px + 1, py + 1).is_black(false);
							++erase_n;
						}
					}
				}
			}
		}
		else
		{
			for (int px = 0; px < (int)tmp_img.width() - 3; ++px)
			{
				for (int py = 0; py < (int)tmp_img.height() - 3; ++py)
				{
					if (tmp_img.at(px + 1, py + 1).is_black())
					{
						e_byte_t p1 = !tmp_img.at(px + 0, py + 0).is_black();
						e_byte_t p2 = !tmp_img.at(px + 0, py + 1).is_black();
						e_byte_t p3 = !tmp_img.at(px + 0, py + 2).is_black();
						e_byte_t p4 = !tmp_img.at(px + 1, py + 0).is_black();
						e_byte_t p6 = !tmp_img.at(px + 1, py + 2).is_black();
						e_byte_t p7 = !tmp_img.at(px + 2, py + 0).is_black();
						e_byte_t p8 = !tmp_img.at(px + 2, py + 1).is_black();
						e_byte_t p9 = !tmp_img.at(px + 2, py + 2).is_black();

						e_byte_t index = p1 + (p2 << 1) + (p3 << 2) + (p4 << 3) + (p6 << 4) + (p7 << 5) + (p8 << 6) + (p9 << 7);
						EXTL_ASSERT(index < 256);
						if (!(!p2 && !p8) && erase_table[index])
						{
							new_img.at(px + 1, py + 1).is_black(false);
							++erase_n;
						}
					}
				}
			}
		}
		is_horizontal = !is_horizontal;
		if (erase_n == 0) break;
	}

	QMessageBox::warning(NULL, "", QObject::tr("%1").arg(max_n));
	return new_img;
}

inline image_type sh_tn_thinnin_6(image_type const& old_img, int max_n = 200)
{
	image_type new_img(old_img);
	while (max_n--)
	{
		bool is_modified = false;
		image_type tmp_img(new_img);
		for (int py = 0; py < (int)tmp_img.height() - 5; ++py)
		{
			for (int px = 0; px < (int)tmp_img.width() - 5; ++px)
			{
				bool con1 = false, con2 = false, con3 = false, con4 = false;
				int count = 0;
				if (tmp_img.at(px + 2, py + 2).is_black())
				{
					e_byte_t p01 = tmp_img.at(px + 0, py + 1).is_black();
					e_byte_t p02 = tmp_img.at(px + 0, py + 2).is_black();
					e_byte_t p03 = tmp_img.at(px + 0, py + 3).is_black();
					e_byte_t p10 = tmp_img.at(px + 1, py + 0).is_black();
					e_byte_t p11 = tmp_img.at(px + 1, py + 1).is_black();
					e_byte_t p12 = tmp_img.at(px + 1, py + 2).is_black();
					e_byte_t p13 = tmp_img.at(px + 1, py + 3).is_black();
					e_byte_t p20 = tmp_img.at(px + 2, py + 0).is_black();
					e_byte_t p21 = tmp_img.at(px + 2, py + 1).is_black();
					e_byte_t p22 = tmp_img.at(px + 2, py + 2).is_black();
					e_byte_t p23 = tmp_img.at(px + 2, py + 3).is_black();
					e_byte_t p30 = tmp_img.at(px + 3, py + 0).is_black();
					e_byte_t p31 = tmp_img.at(px + 3, py + 1).is_black();
					e_byte_t p32 = tmp_img.at(px + 3, py + 2).is_black();
					e_byte_t p33 = tmp_img.at(px + 3, py + 3).is_black();

					count = p11 + p12 + p13 + p21 + p23 + p31 + p32 + p33;
					if(count >= 2 && count <= 6) con1 = true;

					count = 0;
					if (p12 == 0 && p11 == 1) ++count;
					if (p11 == 0 && p21 == 1) ++count;
					if (p21 == 0 && p31 == 1) ++count;
					if (p31 == 0 && p32 == 1) ++count;
					if (p32 == 0 && p33 == 1) ++count;
					if (p33 == 0 && p23 == 1) ++count;
					if (p23 == 0 && p13 == 1) ++count;
					if (p13 == 0 && p12 == 1) ++count;
					if(count == 1) con2 = true;

					if (p12 * p21 * p23 == 0) con3 = true;
					else
					{
						count = 0;
						if (p02 == 0 && p01 == 1) ++count;
						if (p01 == 0 && p11 == 1) ++count;
						if (p11 == 0 && p21 == 1) ++count;
						if (p21 == 0 && p22 == 1) ++count;
						if (p22 == 0 && p23 == 1) ++count;
						if (p23 == 0 && p13 == 1) ++count;
						if (p13 == 0 && p03 == 1) ++count;
						if (p03 == 0 && p02 == 1) ++count;
						if(count != 1) con3 = true;
					}

					if (p12 * p21 * p32 == 0) con4 = true;
					else
					{
						count = 0;
						if (p11 == 0 && p10 == 1) ++count;
						if (p10 == 0 && p20 == 1) ++count;
						if (p20 == 0 && p30 == 1) ++count;
						if (p30 == 0 && p31 == 1) ++count;
						if (p31 == 0 && p32 == 1) ++count;
						if (p32 == 0 && p22 == 1) ++count;
						if (p22 == 0 && p12 == 1) ++count;
						if (p12 == 0 && p11 == 1) ++count;
						if(count != 1) con4 = true;
					}

					if (con1 && con2 &&
						con3 && con4)
					{
						new_img.at(px + 2, py + 2).is_black(false);
						is_modified = true;
					}
				}
			}
		}
		if (!is_modified) break;
	}

	QMessageBox::warning(NULL, "", QObject::tr("%1").arg(max_n));
	return new_img;
}
inline image_type sh_tn_thinning_pruning(image_type const& old_img, int max_n = 1)
{
	image_type new_img(old_img);
	while (max_n--)
	{
		image_type tmp_img(new_img);
		for (int py = 0; py < (int)tmp_img.height() - 3; ++py)
		{
			for (int px = 0; px < (int)tmp_img.width() - 3; ++px)
			{
				int count = 0;
				if (tmp_img.at(px + 1, py + 1).is_black())
				{
					e_byte_t p00 = tmp_img.at(px + 0, py + 0).is_black();
					e_byte_t p01 = tmp_img.at(px + 0, py + 1).is_black();
					e_byte_t p02 = tmp_img.at(px + 0, py + 2).is_black();
					e_byte_t p10 = tmp_img.at(px + 1, py + 0).is_black();
					e_byte_t p12 = tmp_img.at(px + 1, py + 2).is_black();
					e_byte_t p20 = tmp_img.at(px + 2, py + 0).is_black();
					e_byte_t p21 = tmp_img.at(px + 2, py + 1).is_black();
					e_byte_t p22 = tmp_img.at(px + 2, py + 2).is_black();

					if (p01 == 0 && p00 == 1) ++count;
					if (p00 == 0 && p10 == 1) ++count;
					if (p10 == 0 && p20 == 1) ++count;
					if (p20 == 0 && p21 == 1) ++count;
					if (p21 == 0 && p22 == 1) ++count;
					if (p22 == 0 && p12 == 1) ++count;
					if (p12 == 0 && p02 == 1) ++count;
					if (p02 == 0 && p01 == 1) ++count;
					if (count == 1)
					{
						new_img.at(px + 1, py + 1).is_black(false);
					}
				}
			}
		}
	}
	return new_img;
}
// zhang-suen thinning
inline image_type sh_tn_thinning_zhang_suen(image_type const& old_img, int max_n = 200)
{
	int w = (int)old_img.width();
	int h = (int)old_img.height();
	image_type new_img(old_img);
	while (max_n--)
	{
		bool is_modified = false;
		image_type tmp_img(new_img);
		for (int py = -1; py < h - 1; ++py)
		{
			for (int px = -1; px < w - 1; ++px)
			{
				bool con1 = false, con2 = false, con3 = false, con4 = false;
				int count = 0;
				if (tmp_img.at(px + 1, py + 1).is_black())
				{

					e_byte_t p00 = (px < 0 || py < 0)							? 0 : tmp_img.at(px + 0, py + 0).is_black();
					e_byte_t p01 = (px < 0)										? 0 : tmp_img.at(px + 0, py + 1).is_black();
					e_byte_t p02 = (px < 0 || (py + 2) > (h - 1))				? 0 : tmp_img.at(px + 0, py + 2).is_black();
					e_byte_t p10 = (py < 0)										? 0 : tmp_img.at(px + 1, py + 0).is_black();
					e_byte_t p12 = ((py + 2) > (h - 1))							? 0 : tmp_img.at(px + 1, py + 2).is_black();
					e_byte_t p20 = ((px + 2) > (w - 1) || py < 0)				? 0 : tmp_img.at(px + 2, py + 0).is_black();
					e_byte_t p21 = ((px + 2) > (w - 1))							? 0 : tmp_img.at(px + 2, py + 1).is_black();
					e_byte_t p22 = ((px + 2) > (w - 1) || (py + 2) > (h - 1))	? 0 : tmp_img.at(px + 2, py + 2).is_black();

					// not inner point & isolated point
					count = p00 + p01 + p02 + p10 + p12 + p21 + p22;
					if(count >= 2 && count <= 6) con1 = true;

					// the point can be removed if it is a boundary point
					// and it's connectivity is not increased when removing it
					count = 0;
					if (p01 == 0 && p00 == 1) ++count;
					if (p00 == 0 && p10 == 1) ++count;
					if (p10 == 0 && p20 == 1) ++count;
					if (p20 == 0 && p21 == 1) ++count;
					if (p21 == 0 && p22 == 1) ++count;
					if (p22 == 0 && p12 == 1) ++count;
					if (p12 == 0 && p02 == 1) ++count;
					if (p02 == 0 && p01 == 1) ++count;
					if(count == 1) con2 = true;

					if (max_n % 2)
					{
						if (p01 * p10 * p12 == 0) con3 = true;
						if (p01 * p10 * p21 == 0) con4 = true;
					}
					else
					{
						if (p21 * p10 * p12 == 0) con3 = true;
						if (p01 * p12 * p21 == 0) con4 = true;
					}
					if (con1 && con2 && con3 && con4)
					{
						new_img.at(px + 1, py + 1).is_black(false);
						is_modified = true;
					}
				}
			}
		}
		if (!is_modified) break;
	}
	//new_img = sh_tn_thinning_pruning(new_img);
	return new_img;
}
// holt
inline image_type sh_tn_holt(image_type const& old_img, int max_n = 2)
{
	// delete
	double k1[9] =	{	-1, 1, 0
					,	1, 2, 0
					,	0, 0, -1
					};

	double k2[9] =	{	0, 1, -1
					,	0, 2, 1
					,	-1, 0, 0
					};

	double k3[9] =	{	-1, 0, 0
					,	0, 2, 1
					,	0, 1, -1
					};

	double k4[9] =	{	0, 0, -1
					,	1, 2, 0
					,	-1, 1, 0
					};



	int kn = 3;
	image_type new_img(old_img);
	image_type tmp(new_img);
	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_k1, is_matched_k2, is_matched_k3, is_matched_k4;
		for (int py = 0; py < tmp.height() - kn; ++py)
		{
			for (int px = 0; px < tmp.width() - kn; ++px)
			{
				is_matched_k1 = sh_hp_match(tmp, new_img, px, py, k1, 3, 3);
				is_matched_k2 = sh_hp_match(tmp, new_img, px, py, k2, 3, 3);
				is_matched_k3 = sh_hp_match(tmp, new_img, px, py, k3, 3, 3);
				is_matched_k4 = sh_hp_match(tmp, new_img, px, py, k4, 3, 3);

				if (	is_matched_k1
					||	is_matched_k2
					||	is_matched_k3
					||	is_matched_k4
					)
				{
					matched_n++;
				}
			}
		}

		if (matched_n <= 0) break;
		else tmp = new_img;
	}
	return new_img;
}
#if 0
inline image_type sh_tn_acute_angle_emphasis(image_type const& old_img, int max_n = 100)
{
	// top
	double kt1[25] =	{	1, 1, -1, 1, 1
					,	1, 1, -1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kt2[25] =	{	1, -1, -1, 1, 1
					,	1, 1, -1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kt3[25] =	{	1, 1, -1, -1, 1
					,	1, 1, -1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kt4[25] =	{	1, -1, -1, 1, 1
					,	1, -1, -1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kt5[25] =	{	1, 1, -1, -1, 1
					,	1, 1, -1, -1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kt6[25] =	{	1, -1, -1, -1, 1
					,	1, 1, -1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	// bottom
	double kb1[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, -1, 1, 1
					,	1, 1, -1, 1, 1
					};

	double kb2[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, -1, 1, 1
					,	1, 1, -1, -1, 1
					};

	double kb3[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, -1, 1, 1
					,	1, -1, -1, 1, 1
					};

	double kb4[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 2, 1, 1
					,	1, 1, -1, -1, 1
					,	1, 1, -1, -1, 1
					};

	double kb5[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, 1, 1
						,	1, -1, -1, 1, 1
						,	1, -1, -1, 1, 1
						};

	double kb6[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, 1, 1
						,	1, 1, -1, 1, 1
						,	1, -1, -1, -1, 1
						};

	// left
	double kf1[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	-1, -1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kf2[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	-1,- 1, 2, 1, 1
					,	-1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kf3[25] =	{	1, 1, 1, 1, 1
					,	-1, 1, 1, 1, 1
					,	-1,- 1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kf4[25] =	{	1, 1, 1, 1, 1
					,	-1, -1, 1, 1, 1
					,	-1, -1, 2, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kf5[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	-1, -1, 2, 1, 1
					,	-1, -1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kf6[25] =	{	1, 1, 1, 1, 1
					,	-1, 1, 1, 1, 1
					,	-1, -1, 2, 1, 1
					,	-1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	// right
	double kr1[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 2, -1, -1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kr2[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, -1
					,	1, 1, 2, -1, -1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kr3[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					,	1, 1, 2, -1, -1
					,	1, 1, 1, 1, -1
					,	1, 1, 1, 1, 1
					};

	double kr4[25] =	{	1, 1, 1, 1, 1
					,	1, 1, 1, -1, -1
					,	1, 1, 2, -1, -1
					,	1, 1, 1, 1, 1
					,	1, 1, 1, 1, 1
					};

	double kr5[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, -1, -1
						,	1, 1, 1, -1, -1
						,	1, 1, 1, 1, 1
						};

	double kr6[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, -1
						,	1, 1, 2, -1, -1
						,	1, 1, 1, 1, -1
						,	1, 1, 1, 1, 1
						};

	// left-top
	double kft1[25] =	{	-1, 0, 1, 1, 1
						,	2, -1, 2, 1, 1
						,	1, 2, 2, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double kft2[25] =	{	-1, -1, 0, 1, 1
						,	-1, -1, -1, 1, 1
						,	0, -1, 2, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double kft3[25] =	{	-1, -1, -1, 0, 1
						,	-1, -1, -1, 1, 1
						,	-1, -1, 2, 1, 1
						,	0, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double kft4[25] =	{	-1, 1, 1, 1, 1
						,	-1, -1, 1, 1, 1
						,	0, -1, 2, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double kft5[25] =	{	-1, -1, 0, 1, 1
						,	1, -1, -1, 1, 1
						,	1, 1, 2, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	// right-top
	double krt1[25] =	{	1, 1, 1, 2, -1
						,	1, 1, 2, -1, 0
						,	1, 1, 2, 2, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double krt2[25] =	{	1, 1, 0, -1, -1
						,	1, 1, -1, -1, -1
						,	1, 1, 2, -1, 0
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double krt3[25] =	{	1, 0, -1, -1, -1
						,	1, 1, -1, -1, -1
						,	1, 1, 2, -1, -1
						,	1, 1, 1, 1, 0
						,	1, 1, 1, 1, 1
						};

	double krt4[25] =	{	1, 1, 0, -1, -1
						,	1, 1, -1, -1, 1
						,	1, 1, 2, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	double krt5[25] =	{	1, 1, 1, 1, -1
						,	1, 1, 1, -1, -1
						,	1, 1, 2, -1, 0
						,	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						};

	// left-bottom
	double kfb1[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 2, 2, 1, 1
						,	0, -1, 2, 1, 1
						,	-1, 2, 1, 1, 1
						};

	double kfb2[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	0, -1, 2, 1, 1
						,	-1, -1, -1, 1, 1
						,	-1, -1, 0, 1, 1
						};

	double kfb3[25] =	{	1, 1, 1, 1, 1
						,	0, 1, 1, 1, 1
						,	-1, -1, 2, 1, 1
						,	-1, -1, -1, 1, 1
						,	-1, -1, -1, 0, 1
						};

	double kfb4[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, 1, 1
						,	1, -1, -1, 1, 1
						,	-1, -1, 0, 1, 1
						};

	double kfb5[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	0, -1, 2, 1, 1
						,	-1, -1, 1, 1, 1
						,	-1, 1, 1, 1, 1
						};

	// right-bottom
	double krb1[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, 2, 1
						,	1, 1, 2, -1, 2
						,	1, 1, 1, 0, -1
						};

	double krb2[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, -1, 0
						,	1, 1, -1, -1, -1
						,	1, 1, 0, -1, -1
						};

	double krb3[25] =	{	1, 0, 1, 1, 1
						,	1, 1, 1, 1, 0
						,	1, 1, 2, -1, -1
						,	1, 1, -1, -1, -1
						,	1, 0, -1, -1, -1
						};

	double krb4[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, 1, 1
						,	1, 1, -1, -1, 1
						,	1, 1, 0, -1, -1
						};

	double krb5[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 1, 1, 1
						,	1, 1, 2, -1, 0
						,	1, 1, 1, -1, -1
						,	1, 1, 1, 1, -1
						};
	
	//test
	double kts1[25] =	{	1, 1, 0, -1, -1
						,	1, 1, -1, -1, -1
						,	1, -3, -1, -1, 0
						,	1, 2, -3, 1, 1
						,	1, 1, 1, 1, 1
						};

	double kts2[25] =	{	1, 1, 1, 1, 0
						,	1, 1, -3, -1, -1
						,	1, 2, -1, -1, -1
						,	1, 1, -3, -1, -1
						,	1, 1, 1, 1, 0
						};

	double kts3[25] =	{	1, 1, 1, 1, 1
						,	1, 2, -3, 1, 1
						,	1, -3, -1, -1, 0
						,	1, 1, -1, -1, -1
						,	1, 1, 0, -1, -1
						};

	double kts4[25] =	{	1, 1, 1, 1, 1
						,	1, 1, 2, 1, 1
						,	1, -3, -1, -3, 1
						,	1, -1, -1, -1, 1
						,	0, -1, -1, -1, 0
						};

	double kts5[25] =	{	1, 1, 1, 1, 1
						,	1, 1, -3, 2, 1
						,	0, -1, -1, -3, 1
						,	-1, -1, -1, 1, -1
						,	-1, -1, 0, 1, 1
						};

	double kts6[25] =	{	0, 1, 1, 1, 1
						,	-1, -1, -3, 1, 1
						,	-1, -1, -1, 2, 1
						,	-1, -1, -3, 1, 1
						,	0, 1, 1, 1, 1
						};

	double kts7[25] =	{	-1, -1, 0, 1, 1
						,	-1, -1, -1, 1, 1
						,	0, -1, -1, -3, 1
						,	1, 1, -3, 2, 1
						,	1, 1, 1, 1, 1
						};

	double kts8[25] =	{	0, -1, -1, -1, 0
						,	1, -1, -1, -1, 1
						,	1, -3, -1, -3, 1
						,	1, 1, 2, 1, 1
						,	1, 1, 1, 1, 1
						};

	double kts9[25] =	{	1, -1, -1, -1, -1
						,	1, -1, -1, -1, -1
						,	1, -1, -1, -1, -1
						,	1, 2, -3, -3, -3
						,	1, 1, 1, 0, 0
						};

	double kts10[25] =	{	1, 1, 1, 0, 0
						,	1, 2, -3, -3, -3
						,	1, -1, -1, -1, -1
						,	1, -1, -1, -1, -1
						,	1, -1, -1, -1, -1
						};

	int px = 0, py = 0;
	image_type new_img(old_img);
	image_type tmp_img(new_img);
	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_kt1, is_matched_kt2, is_matched_kt3, is_matched_kt4, is_matched_kt5, is_matched_kt6;
		bool is_matched_kb1, is_matched_kb2, is_matched_kb3, is_matched_kb4, is_matched_kb5, is_matched_kb6;
		bool is_matched_kf1, is_matched_kf2, is_matched_kf3, is_matched_kf4, is_matched_kf5, is_matched_kf6;
		bool is_matched_kr1, is_matched_kr2, is_matched_kr3, is_matched_kr4, is_matched_kr5, is_matched_kr6;

		bool is_matched_kft1, is_matched_kft2, is_matched_kft3, is_matched_kft4, is_matched_kft5;
		bool is_matched_krt1, is_matched_krt2, is_matched_krt3, is_matched_krt4, is_matched_krt5;
		bool is_matched_kfb1, is_matched_kfb2, is_matched_kfb3, is_matched_kfb4, is_matched_kfb5;
		bool is_matched_krb1, is_matched_krb2, is_matched_krb3, is_matched_krb4, is_matched_krb5;
		
		bool is_matched_kts1, is_matched_kts2, is_matched_kts3, is_matched_kts4;
		bool is_matched_kts5, is_matched_kts6, is_matched_kts7, is_matched_kts8;
		bool is_matched_kts9, is_matched_kts10, is_matched_kts11, is_matched_kts12;

		for (py = 0; py < tmp_img.height() - 5; ++py)
		{
			for (px = 0; px < tmp_img.width() - 5; ++px)
			{
				/*is_matched_kt1 = sh_hp_match(tmp_img, new_img, px, py, kt1, 5, 5);
				is_matched_kt2 = sh_hp_match(tmp_img, new_img, px, py, kt2, 5, 5);
				is_matched_kt3 = sh_hp_match(tmp_img, new_img, px, py, kt3, 5, 5);
				is_matched_kt4 = sh_hp_match(tmp_img, new_img, px, py, kt4, 5, 5);
				is_matched_kt5 = sh_hp_match(tmp_img, new_img, px, py, kt5, 5, 5);
				is_matched_kt6 = sh_hp_match(tmp_img, new_img, px, py, kt6, 5, 5);

				is_matched_kb1 = sh_hp_match(tmp_img, new_img, px, py, kb1, 5, 5);
				is_matched_kb2 = sh_hp_match(tmp_img, new_img, px, py, kb2, 5, 5);
				is_matched_kb3 = sh_hp_match(tmp_img, new_img, px, py, kb3, 5, 5);
				is_matched_kb4 = sh_hp_match(tmp_img, new_img, px, py, kb4, 5, 5);
				is_matched_kb5 = sh_hp_match(tmp_img, new_img, px, py, kb5, 5, 5);
				is_matched_kb6 = sh_hp_match(tmp_img, new_img, px, py, kb6, 5, 5);

				is_matched_kf1 = sh_hp_match(tmp_img, new_img, px, py, kf1, 5, 5);
				is_matched_kf2 = sh_hp_match(tmp_img, new_img, px, py, kf2, 5, 5);
				is_matched_kf3 = sh_hp_match(tmp_img, new_img, px, py, kf3, 5, 5);
				is_matched_kf4 = sh_hp_match(tmp_img, new_img, px, py, kf4, 5, 5);
				is_matched_kf5 = sh_hp_match(tmp_img, new_img, px, py, kf5, 5, 5);
				is_matched_kf6 = sh_hp_match(tmp_img, new_img, px, py, kf6, 5, 5);

				is_matched_kr1 = sh_hp_match(tmp_img, new_img, px, py, kr1, 5, 5);
				is_matched_kr2 = sh_hp_match(tmp_img, new_img, px, py, kr2, 5, 5);
				is_matched_kr3 = sh_hp_match(tmp_img, new_img, px, py, kr3, 5, 5);
				is_matched_kr4 = sh_hp_match(tmp_img, new_img, px, py, kr4, 5, 5);
				is_matched_kr5 = sh_hp_match(tmp_img, new_img, px, py, kr5, 5, 5);
				is_matched_kr6 = sh_hp_match(tmp_img, new_img, px, py, kr6, 5, 5);*/

				/*is_matched_kft1 = sh_hp_match(tmp_img, new_img, px, py, kft1, 5, 5);
				is_matched_kft2 = sh_hp_match(tmp_img, new_img, px, py, kft2, 5, 5);
				is_matched_kft3 = sh_hp_match(tmp_img, new_img, px, py, kft3, 5, 5);
				is_matched_kft4 = sh_hp_match(tmp_img, new_img, px, py, kft4, 5, 5);
				is_matched_kft5 = sh_hp_match(tmp_img, new_img, px, py, kft5, 5, 5);*/

				/*is_matched_krt1 = sh_hp_match(tmp_img, new_img, px, py, krt1, 5, 5);
				is_matched_krt2 = sh_hp_match(tmp_img, new_img, px, py, krt2, 5, 5);
				is_matched_krt3 = sh_hp_match(tmp_img, new_img, px, py, krt3, 5, 5);
				is_matched_krt4 = sh_hp_match(tmp_img, new_img, px, py, krt4, 5, 5);
				is_matched_krt5 = sh_hp_match(tmp_img, new_img, px, py, krt5, 5, 5);*/

				/*is_matched_kfb1 = sh_hp_match(tmp_img, new_img, px, py, kfb1, 5, 5);
				is_matched_kfb2 = sh_hp_match(tmp_img, new_img, px, py, kfb2, 5, 5);
				is_matched_kfb3 = sh_hp_match(tmp_img, new_img, px, py, kfb3, 5, 5);
				is_matched_kfb4 = sh_hp_match(tmp_img, new_img, px, py, kfb4, 5, 5);
				is_matched_kfb5 = sh_hp_match(tmp_img, new_img, px, py, kfb5, 5, 5);*/

				/*is_matched_krb1 = sh_hp_match(tmp_img, new_img, px, py, krb1, 5, 5);
				is_matched_krb2 = sh_hp_match(tmp_img, new_img, px, py, krb2, 5, 5);
				is_matched_krb3 = sh_hp_match(tmp_img, new_img, px, py, krb3, 5, 5);
				is_matched_krb4 = sh_hp_match(tmp_img, new_img, px, py, krb4, 5, 5);
				is_matched_krb5 = sh_hp_match(tmp_img, new_img, px, py, krb5, 5, 5);*/

				is_matched_kts1 = sh_hp_match(tmp_img, new_img, px, py, kts1, 5, 5);
				is_matched_kts2 = sh_hp_match(tmp_img, new_img, px, py, kts2, 5, 5);
				is_matched_kts3 = sh_hp_match(tmp_img, new_img, px, py, kts3, 5, 5);
				is_matched_kts4 = sh_hp_match(tmp_img, new_img, px, py, kts4, 5, 5);
				is_matched_kts5 = sh_hp_match(tmp_img, new_img, px, py, kts5, 5, 5);
				is_matched_kts6 = sh_hp_match(tmp_img, new_img, px, py, kts6, 5, 5);
				is_matched_kts7 = sh_hp_match(tmp_img, new_img, px, py, kts7, 5, 5);
				is_matched_kts8 = sh_hp_match(tmp_img, new_img, px, py, kts8, 5, 5);

				//is_matched_kts9 = sh_hp_match(tmp_img, new_img, px, py, kts9, 5, 5);
				//is_matched_kts10 = sh_hp_match(tmp_img, new_img, px, py, kts10, 5, 5);

				//is_matched_kts2 = sh_hp_match(tmp_img, new_img, px, py, kts2, 7, 7);

				if (	/*is_matched_kt1
					||	is_matched_kt2
					||	is_matched_kt3
					||	is_matched_kt4
					||	is_matched_kt5
					||	is_matched_kt6

					||	is_matched_kb1
					||	is_matched_kb2
					||	is_matched_kb3
					||	is_matched_kb4
					||	is_matched_kb5
					||	is_matched_kb6

					||	is_matched_kf1
					||	is_matched_kf2
					||	is_matched_kf3
					||	is_matched_kf4
					||	is_matched_kf5
					||	is_matched_kf6

					||	is_matched_kr1
					||	is_matched_kr2
					||	is_matched_kr3
					||	is_matched_kr4
					||	is_matched_kr5
					||	is_matched_kr6

					||	is_matched_kft1
					||	is_matched_kft2
					||	is_matched_kft3
					||	is_matched_kft4
					||	is_matched_kft5

					||	is_matched_krt1
					||	is_matched_krt2
					||	is_matched_krt3
					||	is_matched_krt4
					||	is_matched_krt5

					||	is_matched_kfb1
					||	is_matched_kfb2
					||	is_matched_kfb3
					||	is_matched_kfb4
					||	is_matched_kfb5

					||	is_matched_krb1
					||	is_matched_krb2
					||	is_matched_krb3
					||	is_matched_krb4
					||	is_matched_krb5
						
					||*/	is_matched_kts1
					||	is_matched_kts2
					||	is_matched_kts3
					||	is_matched_kts4
					||	is_matched_kts5
					||	is_matched_kts6
					||	is_matched_kts7
					||	is_matched_kts8

					//||	is_matched_kts9
					//||	is_matched_kts10
					)
				{
					matched_n++;
				}
			}
		}
		if (matched_n > 0) tmp_img = new_img;
		//else break;
	/*}
	max_n = 100;
	while (max_n--)
	{*/
		bool is_modified = false;
		for (py = 0; py < (int)tmp_img.height() - 3; ++py)
		{
			for (px = 0; px < (int)tmp_img.width() - 3; ++px)
			{
				bool con1 = false, con2 = false, con3 = false, con4 = false;
				int count = 0;
				if (tmp_img.at(px + 1, py + 1).is_black())
				{
					e_byte_t p00 = tmp_img.at(px + 0, py + 0).is_black();
					e_byte_t p01 = tmp_img.at(px + 0, py + 1).is_black();
					e_byte_t p02 = tmp_img.at(px + 0, py + 2).is_black();
					e_byte_t p10 = tmp_img.at(px + 1, py + 0).is_black();
					e_byte_t p12 = tmp_img.at(px + 1, py + 2).is_black();
					e_byte_t p20 = tmp_img.at(px + 2, py + 0).is_black();
					e_byte_t p21 = tmp_img.at(px + 2, py + 1).is_black();
					e_byte_t p22 = tmp_img.at(px + 2, py + 2).is_black();

					// not inner point & isolated point
					count = p00 + p01 + p02 + p10 + p12 + p21 + p22;
					if(count >= 2 && count <= 6) con1 = true;

					// the point can be removed if it is a boundary point
					// and it's connectivity is not increased when removing it
					count = 0;
					if (p01 == 0 && p00 == 1) ++count;
					if (p00 == 0 && p10 == 1) ++count;
					if (p10 == 0 && p20 == 1) ++count;
					if (p20 == 0 && p21 == 1) ++count;
					if (p21 == 0 && p22 == 1) ++count;
					if (p22 == 0 && p12 == 1) ++count;
					if (p12 == 0 && p02 == 1) ++count;
					if (p02 == 0 && p01 == 1) ++count;
					if(count == 1) con2 = true;

					//
					if (max_n % 2)
					{
						if (p01 * p10 * p12 == 0) con3 = true;
						if (p01 * p10 * p21 == 0) con4 = true;
					}
					else
					{
						if (p21 * p10 * p12 == 0) con3 = true;
						if (p01 * p12 * p21 == 0) con4 = true;
					}
					if (con1 && con2 && con3 && con4)
					{
						new_img.at(px + 1, py + 1).is_black(false);
						is_modified = true;
					}
				}
			}
		}
		if (!is_modified) break;
		tmp_img = new_img;
	}

	return new_img;
}

#endif

// thinning
inline image_type sh_tn_thinning(image_type const& old_img, int max_n = 200)
{
	image_type new_img(old_img);
	//new_img	= sh_fx_fixes(new_img);
	//new_img	= sh_tn_acute_angle_emphasis(new_img);
	new_img = sh_tn_thinning_zhang_suen(new_img);
	//new_img = sh_tn_holt(new_img);

	return new_img;
}

#endif // SH_TN_H
