#ifndef IMPL_GRAY_H
#define IMPL_GRAY_H

#include "prefix.h"
#include "math.h"

inline basic_image sh_gy_general(basic_image const& old_img)
{
	if (old_img.is_empty()) return basic_image();

	// make gray image for showing
	basic_image new_img(old_img.width(), old_img.height());
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

inline basic_image sh_gy_stretch(basic_image const& old_img)
{
	if (old_img.is_empty()) return basic_image();
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
	basic_image new_img(old_img.width(), old_img.height());
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

inline basic_image sh_gy_histogram(basic_image const& old_img)
{
	if (old_img.is_empty()) return basic_image();
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
	basic_image new_img(old_img.width(), old_img.height());
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
inline basic_image sh_gy_adaptive(basic_image const& old_img)
{
	if (old_img.is_empty()) return basic_image();

	// pre-handle
	basic_image tmp_img = sh_gy_stretch(old_img);
	tmp_img = sh_gy_histogram(tmp_img);

	// make gray image for showing
	basic_image new_img(tmp_img.width(), tmp_img.height());
	int px, py;
	for (px = 0; px < (int)tmp_img.width(); ++px)
	{
		for (py = 0; py < (int)tmp_img.height(); ++py)
		{
			int gray = tmp_img.at(px, py).gray();
			new_img.at(px, py).red(gray);
			new_img.at(px, py).green(gray);
			new_img.at(px, py).blue(gray);
		}
	}
	return new_img;
}

#endif // IMPL_GRAY_H
