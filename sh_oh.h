#ifndef SH_OH_H
#define SH_OH_H

// other handle
#include "prefix.h"
#include "sh_zm.h"
#include "sh_dk.h"
#include "sh_rl.h"
#include "sh_tn.h"
#include "sh_fx.h"

// mean smooth filter
inline image_type sh_oh_mean_smooth(image_type const& old_img, int tn = 3)
{
	if (old_img.is_empty()) return old_img;

	image_type new_img(old_img);
	for (int px = 0; px < (int)old_img.width() - tn; ++px)
	{
		for (int py = 0; py < (int)old_img.height() - tn; ++py)
		{
			int avg = 0;
			for (int k = 0; k < tn * tn; ++k)
				avg += old_img.at(px + k % tn, py + k / tn).gray();
			avg /= tn * tn;
			new_img.at(px + (tn >> 1), py + (tn >> 1)).gray(avg);
		}
	}
	return new_img;
}

// mean smooth filter for binary image
inline image_type sh_oh_binary_mean_smooth(image_type const& old_img, int tn = 2)
{
	if (old_img.is_empty()) return old_img;

	int w = (int)old_img.width();
	int h = (int)old_img.height();

	int n = 0;
	int px, py;
	for (px = 0; px < w; ++px)
		for (py = 0; py < h; ++py)
			n += old_img.at(px, py).is_black()? 1 : 0;

	// not smooth it if image is too rough
	if ((double(n) / double(w * h)) > 0.6) return old_img;

	image_type new_img(old_img);
	for (px = 0; px < w - tn; ++px)
	{
		for (py = 0; py < h - tn; ++py)
		{
			int avg = 0;
			for (int k = 0; k < tn * tn; ++k)
				avg += old_img.at(px + k % tn, py + k / tn).gray();
			avg /= tn * tn;
			new_img.at(px + (tn >> 1), py + (tn >> 1)).is_black(avg < 128);
		}
	}
	return new_img;
}
// trim margin
inline image_type sh_oh_trim(image_type const& old_img)
{
	basic_rect<int> r = sh_dk_digital_region(old_img);

	// save trimed image
	image_type new_img(r.width(), r.height());
	for (int py = r.top(); py <= r.bottom(); ++py)
		for (int px = r.left(); px <= r.right(); ++px)
			new_img.at(px - r.left(), py - r.top()).gray(old_img.at(px, py).gray());
	return new_img;
}

inline void sh_oh_trim_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row)
{
	// normalize
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_oh_trim(pimgs_info_row[i][j]->image);
}

// fill margin by factor = w / h
inline image_type sh_oh_fill_margin(image_type const& old_img, double factor)
{
	int w = old_img.width();
	int h = old_img.height();
	double f = double(w) / double(h);

	// fill
	if (f > factor)	// fill height
	{
		int need_h = int(w / factor);
		int margin_h = (need_h - h) >> 1;

		image_type new_img(w, need_h);
		for (int py = 0; py < new_img.height(); ++py)
		{
			for (int px = 0; px < new_img.width(); ++px)
			{
				if (py < margin_h || py >= new_img.height() - margin_h)
					new_img.at(px, py).is_black(false);
				else new_img.at(px, py).is_black(old_img.at(px, py - margin_h).is_black());
			}
		}
		return new_img;
	}
	else if (f < factor)// fill width
	{
		int need_w = int(h * factor);
		int margin_w = (need_w - w) >> 1;

		image_type new_img(need_w, h);
		for (int py = 0; py < new_img.height(); ++py)
		{
			for (int px = 0; px < new_img.width(); ++px)
			{
				if (px < margin_w || px >= new_img.width() - margin_w)
					new_img.at(px, py).is_black(false);
				else new_img.at(px, py).is_black(old_img.at(px - margin_w, py).is_black());
			}
		}
		return new_img;
	}
	return old_img;
}
// fill margin for 1 by factor = w / h
inline image_type sh_oh_fill_margin_for_1(image_type const& old_img, double factor)
{
	int w = old_img.width();
	int h = old_img.height();
	double f = double(w) / double(h);

	if (f < factor)	// fill width
	{
		int need_w = int(h * factor);
		int margin_lw = (need_w - w) >> 1;
		int margin_rw = (need_w - w) - margin_lw;

		int px, py;
		image_type new_img(need_w, h);
		for (py = 0; py < new_img.height(); ++py)
		{
			for (px = 0; px < new_img.width(); ++px)
			{
				if (px < margin_lw || px >= new_img.width() - margin_rw)
					new_img.at(px, py).is_black(false);
				else new_img.at(px, py).is_black(old_img.at(px - margin_lw, py).is_black());
			}
		}
		return new_img;
	}
	return old_img;
}

inline void sh_oh_fill_margin_for_1_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row, int w = IMAGE_W, int h = IMAGE_H)
{
	// fill margin for 1
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_oh_fill_margin_for_1(pimgs_info_row[i][j]->image, double(w) / double(h));
}
inline void sh_oh_fill_margin_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row, int w = IMAGE_W, int h = IMAGE_H)
{
	// fill margin
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_oh_fill_margin(pimgs_info_row[i][j]->image, double(w) / double(h));
}
inline void sh_oh_normalize_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row, int w = IMAGE_W, int h = IMAGE_H)
{
	// normalize
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_zm_bilinear_zoom(pimgs_info_row[i][j]->image, w, h, true);
}
inline void sh_oh_normalize2_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row, int w = IMAGE_W, int h = IMAGE_H)
{
	// normalize
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
		{
			image_type& pimg = pimgs_info_row[i][j]->image;
			if (pimg.width() < 16 || pimg.height() < 32)
			{
				pimg = sh_zm_nearest_neighbor_zoom(pimg, 16, 32);
				//pimg = sh_fx_roughening(pimg);
				pimg = sh_oh_binary_mean_smooth(pimg);
				pimg = sh_zm_nearest_neighbor_zoom(pimg, w, h);
			}
			else pimg = sh_zm_nearest_neighbor_zoom(pimg, w, h);
		}
}
inline void sh_oh_binary_smooth_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row)
{
	// binary smooth
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			//pimgs_info_row[i][j]->image = sh_oh_mean_smooth(pimgs_info_row[i][j]->image, 2, true);
			pimgs_info_row[i][j]->image = sh_oh_binary_mean_smooth(pimgs_info_row[i][j]->image);
}

inline void sh_oh_fixes_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row)
{
	// deskew
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_fx_fixes(pimgs_info_row[i][j]->image);
}
inline void sh_oh_deskew_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row)
{
	// deskew
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_dk_horizontal_side_slip_deskew(pimgs_info_row[i][j]->image);
}
inline void sh_oh_thinning_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row)
{
	// thinning
	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		for (int j = 0; j < (int)pimgs_info_row[i].size(); ++j)
			pimgs_info_row[i][j]->image = sh_tn_thinning(pimgs_info_row[i][j]->image);
}

inline image_type sh_oh_merge_from_pimgs_info_row(pimages_info_row_type const& pimgs_info_row, int margin = 20)
{
	int i, j;
	int px, py;

	// get width & height
	int max_w = 0, max_h = 0;
	for (i = 0; i < (int)pimgs_info_row.size(); ++i)
	{
		int w = 0;
		int h = 0;
		for (j = 0; j < (int)pimgs_info_row[i].size(); ++j)
		{
			w += pimgs_info_row[i][j]->image.width();
			w += margin;
			h = pimgs_info_row[i][j]->image.height() > h? pimgs_info_row[i][j]->image.height() : h;
		}

		max_w = w > max_w? w : max_w;
		max_h += h + margin;
	}

	if (max_w == 0 || max_h == 0) return image_type();

	// clear new image
	image_type new_img(max_w, max_h);
	for (px = 0; px < (int)new_img.width(); ++px)
		for (py = 0; py < (int)new_img.height(); ++py)
			new_img.at(px, py).is_black(false);

	int base_y = 0;
	for (i = 0; i < (int)pimgs_info_row.size(); ++i)
	{
		int h = 0;
		int base_x = 0;
		for (j = 0; j < (int)pimgs_info_row[i].size(); ++j)
		{
			image_type& img = pimgs_info_row[i][j]->image;
			for (px = 0; px < (int)img.width(); ++px)
			{
				for (py = 0; py < (int)img.height(); ++py)
				{
					if (img.at(px, py).is_black())
						new_img.at(base_x + px, base_y + py) = img.at(px, py);
					//else new_img.at(base_x + px, base_y + py).gray(200);
					//if (py == 0 || px == 0 || px == (int)img.width() - 1 || py == (int)img.height() - 1)
					//	new_img.at(base_x + px, base_y + py).gray(200);
				}
			}

			base_x += img.width();
			base_x += margin;
			h = img.height() > h? img.height() : h;
		}
		base_y += h + margin;
	}

	return new_img;
}
#endif // SH_OH_H
