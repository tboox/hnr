#ifndef SH_GY_H
#define SH_GY_H

// image gray
#include "prefix.h"
#include "math.h"
#include "sh_oh.h"

// make general gray image
inline image_type sh_gy_general(image_type const& old_img)
{
	if (old_img.is_empty()) return old_img;

	// make gray image for showing
	image_type new_img(old_img.width(), old_img.height());
	int px, py;
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			int gray = old_img.at(px, py).gray();
			new_img.at(px, py).red(gray);
			new_img.at(px, py).green(gray);
			new_img.at(px, py).blue(gray);
		}
	}
	return new_img;
}
// stretch gray image
inline image_type sh_gy_stretch(image_type const& old_img)
{
	if (old_img.is_empty()) return old_img;
	int px, py;

	// gets the lower and upper bounds of the old image
	int old_lower = 0;
	int old_upper = 0;
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			old_lower = old_img.at(px, py).gray() < old_lower? old_img.at(px, py).gray() : old_lower;
			old_upper = old_img.at(px, py).gray() > old_upper? old_img.at(px, py).gray() : old_upper;
		}
	}

	// adjusts gray
	int new_lower = 0;
	int new_upper = 255;
	image_type new_img(old_img.width(), old_img.height());
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			int new_gray = (new_upper - new_lower) * old_img.at(px, py).gray() / (old_upper - old_lower) + new_lower;
			if (new_gray < new_lower) new_gray = new_lower;
			if (new_gray > new_upper) new_gray = new_upper;

			new_img.at(px, py).gray(new_gray);
		}
	}

	return new_img;
}
// global histogram equalization
inline image_type sh_gy_histogram(image_type const& old_img, bool is_forced = true)
{
	if (old_img.is_empty()) return old_img;
	int px, py;

	// stats gray
	int gray_h[256] = {0};	// gray histogram
	int max_gray = old_img.at(0, 0).gray();
	int min_gray = old_img.at(0, 0).gray();

	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			max_gray = old_img.at(px, py).gray() > max_gray? old_img.at(px, py).gray() : max_gray;
			min_gray = old_img.at(px, py).gray() < min_gray? old_img.at(px, py).gray() : min_gray;

			EXTL_ASSERT(old_img.at(px, py).gray() < 256);
			++gray_h[old_img.at(px, py).gray()];
		}
	}

	// not handle it if contrast is too large
	// note: must be finished before sh_gy_stretch()
	if (!is_forced && ((max_gray - min_gray) > 200)) return old_img;

	// cumulative probability
	double c[256];
	int pixel_n = old_img.width() * old_img.height();
	double cum = 0;
	for (int i = 0; i < 256; ++i)
	{
		cum += double(gray_h[i]) / pixel_n;
		c[i] = cum;
	}

	// transform
	image_type new_img(old_img.width(), old_img.height());
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			int new_gray = int(c[old_img.at(px, py).gray()] * (max_gray - min_gray) + min_gray);
			if (new_gray < 0) new_gray = 0;
			if (new_gray > 255) new_gray = 255;

			new_img.at(px, py).gray(new_gray);
		}
	}

	return new_img;
}
// partial histogram equalization
inline image_type sh_gy_part_histogram(image_type const& old_img, int part_n = 100)
{
	if (old_img.is_empty()) return old_img;

	// the image is too small
	if (old_img.width() < part_n || old_img.height() < part_n)
		part_n = xtl_min(old_img.width(), old_img.height()) / 2;

	// traverse per-column
	int i;
	int pixel_n = part_n * part_n;
	int part_n_2 = part_n >> 1;
	image_type new_img(old_img.width(), old_img.height());
	for (int py = -part_n_2; py < (int)old_img.height() - part_n_2; ++py)
	{
		// stats the gray of partial block at the start position of per-line
		int gray_h[256] = {0};
		for (i = 0; i < pixel_n; ++i)
		{
			if ((py + i / part_n) >= 0 && (py + i / part_n) < old_img.height())
			{
				EXTL_ASSERT(old_img.at(i % part_n_2, py + i / part_n).gray() < 256);
				++gray_h[old_img.at(i % part_n_2, py + i / part_n).gray()];
			}
		}

		// stats partial histogram
		for (int px = -part_n_2; px < (int)old_img.width() - part_n_2; ++px)
		{
			// calcualtes real pixel count
			int part_w;
			if (px < 0) part_w = px + part_n;
			else if (px > old_img.width() - part_n) part_w = old_img.width() - px;
			else part_w = part_n;

			int part_h;
			if (py < 0) part_h = py + part_n;
			else if (py > old_img.height() - part_n) part_h = old_img.height() - py;
			else part_h = part_n;

			int rpixel_n = part_w * part_h;

			// cumulative probability and gets min_gray & max_gray
			double cp[256];
			double cum = 0;
			int min_gray = 256;
			int max_gray = -1;
			for (i = 0; i < 256; ++i)
			{
				cum += double(gray_h[i]) / rpixel_n;
				cp[i] = cum;

				if (gray_h[i] > 0)
				{
					min_gray = i < min_gray? i : min_gray;
					max_gray = i > max_gray? i : max_gray;
				}
			}
			EXTL_ASSERT(min_gray != 256 && max_gray != -1);

			// transform
			int new_gray = int(cp[old_img.at(px + part_n_2 , py + part_n_2).gray()] * (max_gray - min_gray) + min_gray);
			if (new_gray < 0) new_gray = 0;
			if (new_gray > 255) new_gray = 255;
			new_img.at(px + part_n_2 , py + part_n_2).gray(new_gray);

			// update gray_h
			for (i = 0; i < part_n; ++i)
			{
				if ((py + i) >= 0 && (py + i) < old_img.height())
				{
					// remove previous partial column
					if (px >= 0)
						--gray_h[old_img.at(px, py + i).gray()];

					// add next partial column
					if (px + part_n < old_img.width())
						++gray_h[old_img.at(px + part_n, py + i).gray()];
				}
			}
		}
	}
	return new_img;
}

#endif // SH_GY_H
