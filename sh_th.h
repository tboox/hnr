#ifndef SH_TH_H
#define SH_TH_H

// threshold
#include "prefix.h"

// search a threshold from the given gray histogram using basic method
// and return -1 if we don't find threshold.
// \note only for gray image background of which is white
inline int sh_th_search_basic_threshold(int gh[256])
{
	double threshold = -1.0;

	// calculate global average of gray
	double n = 0, sum = 0;
	for (int i = 0; i < 256; ++i)
	{
		n += gh[i];
		sum += i * gh[i];
	}
	if (0 == n) return xtl_round45(threshold);

	// initial threshold
	threshold = sum / n;

	// search threshold
	double dt = 255;
	while (fabs(dt) > 1e-10)
	{
		// calculate the average of gray: u1 & u2
		double n1 = 0, sum1 = 0;
		for (int i = 0; double(i) < threshold; ++i)
		{
			n1 += gh[i];
			sum1 += i * gh[i];
		}
		double n2 = n - n1;
		if (0 == n1 || 0 == n2) break;
		double sum2 = sum - sum1;

		// u1: the average of gray which is less than threshold
		double u1 = sum1 / n1;
		// u2: the average of gray which is greater c than threshold
		double u2 = sum2 / n2;

		//dt = ((u1 + u2) / 2) - threshold;
		dt = 0.3 * u1 + 0.7 * u2 - threshold;	// seems to be better
		threshold += dt;
	}

	return xtl_round45(threshold);
}

// split image using global basic threshold
// \note only for gray image background of which is white
inline image_type sh_th_global_basic_threshold(image_type const& old_img)
{
	if (old_img.is_empty()) return old_img;

	// stats the gray histogram
	int gh[256] = {0};
	int px, py;
	for (px = 0; px < (int)old_img.width(); ++px)
		for (py = 0; py < (int)old_img.height(); ++py)
			++gh[old_img.at(px, py).gray()];

	// search hreshold
	int t = sh_th_search_basic_threshold(gh);

	// splits image using the global threshold
	image_type new_img(old_img.width(), old_img.height());
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			if (-1 != t && old_img.at(px, py).gray() < t)
				new_img.at(px, py).is_black(true);
			else new_img.at(px, py).is_black(false);
		}
	}

	return new_img;
}

// split image using partial basic threshold
// \note only for gray image background of which is white
inline image_type sh_th_partial_basic_threshold(image_type const& old_img, int part_n = 50)
{
	if (old_img.is_empty()) return old_img;

	// the image is too small
	if (old_img.width() < part_n || old_img.height() < part_n)
		part_n = xtl_min(old_img.width(), old_img.height()) / 2;

	// traverse per-column
	int i, px, py;
	int pixel_n = part_n * part_n;
	int part_n_2 = part_n >> 1;
	image_type new_img(old_img.width(), old_img.height());
	for (py = -part_n_2; py < (int)old_img.height() - part_n_2; ++py)
	{
		// stats the gray of partial block at the start position of per-line
		int gh[256] = {0};
		for (i = 0; i < pixel_n; ++i)
		{
			if ((py + i / part_n) >= 0 && (py + i / part_n) < old_img.height())
			{
				EXTL_ASSERT(old_img.at(i % part_n_2, py + i / part_n).gray() < 256);
				++gh[old_img.at(i % part_n_2, py + i / part_n).gray()];
			}
		}

		// stats partial histogram
		for (px = -part_n_2; px < (int)old_img.width() - part_n_2; ++px)
		{
			// search partial threshold
			int t = sh_th_search_basic_threshold(gh);

			// split using threshold
			if (-1 != t && old_img.at(px + part_n_2 , py + part_n_2).gray() < t)
				new_img.at(px + part_n_2 , py + part_n_2).is_black(true);
			else new_img.at(px + part_n_2 , py + part_n_2).is_black(false);

			// update gray histogram
			for (i = 0; i < part_n; ++i)
			{
				if ((py + i) >= 0 && (py + i) < old_img.height())
				{
					// remove previous partial column
					if (px >= 0)
						--gh[old_img.at(px, py + i).gray()];

					// add next partial column
					if (px + part_n < old_img.width())
						++gh[old_img.at(px + part_n, py + i).gray()];
				}
			}
		}
	}
	return new_img;
}
// search a threshold from the given gray histogram using otsu method
// and return -1 if we don't find threshold.
// \note only for gray image background of which is white
inline int sh_th_search_otsu_threshold(int gh[256])
{
	// stats the number of gray
	int i, n = 0, sum = 0;
	for (i = 0; i < 256; ++i)
	{
		n += gh[i];
		sum += i * gh[i];
	}

	double bc;					// the between-class variance
	double bc_max = -1.0;		// the maximum between-class variance
	double threshold = -1;		// initial threshold
	double n1 = 0, n2 = 0;		// counters
	double sum1 = 0, sum2 = 0;	// counters
	double u1 = 0, u2 = 0;		// the gray average
	for (int t = 0; t < 256; ++t)
	{
		n1 += gh[t];			// left counter
		if (0 == n1) continue;
		n2 = n - n1;			// right counter
		if (0 == n2) break;

		sum1 += t * gh[t];
		sum2 = sum - sum1;

		u1 = sum1 / n1;			// left average
		u2 = sum2 / n2;			// right average

		// between-class variance
		//bc = n1 * n2 * (u1 - u2) * (u1 - u2) / n;
		bc = n1 * n2 * (u1 - u2) * (u1 - u2);
		//bc = n1 * n2 * (u2 - u1);

		if (bc > bc_max)
		{
			bc_max = bc;
			//threshold = t + 1;
			threshold = (u1 + 3 * u2) / 4;
		}
	}
	return xtl_round45(threshold);
}

// global otsu adaptive threhold split
// note: only for gray image and foreground is black & background is white
inline image_type sh_th_global_otsu_threshold(image_type const& old_img)
{
	if (old_img.is_empty()) return old_img;

	// stats the gray histogram
	int gh[256] = {0};
	int px, py;
	for (px = 0; px < (int)old_img.width(); ++px)
		for (py = 0; py < (int)old_img.height(); ++py)
			++gh[old_img.at(px, py).gray()];

	// search hreshold
	int t = sh_th_search_otsu_threshold(gh);

	// splits image using the global threshold
	image_type new_img(old_img.width(), old_img.height());
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		for (py = 0; py < (int)old_img.height(); ++py)
		{
			if (-1 != t && old_img.at(px, py).gray() < t)
				new_img.at(px, py).is_black(true);
			else new_img.at(px, py).is_black(false);
		}
	}

	return new_img;
}
// partial otsu adaptive threhold split
// note: only for gray image and foreground is black & background is white
inline image_type sh_th_partial_otsu_threshold(image_type const& old_img, int part_n = 50)
{
	if (old_img.is_empty()) return old_img;

	// the image is too small
	if (old_img.width() < part_n || old_img.height() < part_n)
		part_n = xtl_min(old_img.width(), old_img.height()) / 2;

	// traverse per-column
	int i, px, py;
	int pixel_n = part_n * part_n;
	int part_n_2 = part_n >> 1;
	image_type new_img(old_img.width(), old_img.height());
	for (py = -part_n_2; py < (int)old_img.height() - part_n_2; ++py)
	{
		// stats the gray of partial block at the start position of per-line
		int gh[256] = {0};
		for (i = 0; i < pixel_n; ++i)
		{
			if ((py + i / part_n) >= 0 && (py + i / part_n) < old_img.height())
			{
				EXTL_ASSERT(old_img.at(i % part_n_2, py + i / part_n).gray() < 256);
				++gh[old_img.at(i % part_n_2, py + i / part_n).gray()];
			}
		}

		// stats partial histogram
		for (px = -part_n_2; px < (int)old_img.width() - part_n_2; ++px)
		{
			// search threshold
			int t = sh_th_search_otsu_threshold(gh);

			// split using threshold
			if (-1 != t && old_img.at(px + part_n_2 , py + part_n_2).gray() < t)
				new_img.at(px + part_n_2 , py + part_n_2).is_black(true);
			else new_img.at(px + part_n_2 , py + part_n_2).is_black(false);

			// update gray histogram
			for (i = 0; i < part_n; ++i)
			{
				if ((py + i) >= 0 && (py + i) < old_img.height())
				{
					// remove previous partial column
					if (px >= 0)
						--gh[old_img.at(px, py + i).gray()];

					// add next partial column
					if (px + part_n < old_img.width())
						++gh[old_img.at(px + part_n, py + i).gray()];
				}
			}
		}
	}
	return new_img;
}

#endif // SH_TH_H
