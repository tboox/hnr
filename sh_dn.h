#ifndef SH_DN_H
#define SH_DN_H

// denoising
#include "prefix.h"

// \note only for binary image denoising
inline image_type sh_dn_median_denoising(image_type const& old_img, int n = 3)
{
	if (old_img.is_empty()) return old_img;

	stack_buffer<int> buf(n * n);
	int size = buf.size();

	int mid = n >> 1;
	image_type new_img(old_img);
	for (int px = 0; px < (int)old_img.width() - n; ++px)
	{
		for (int py = 0; py < (int)old_img.height() - n; ++py)
		{
			// gray image denoising
			for (int k = 0; k < size; ++k)
				buf[k] = old_img.at(px + k % n, py + k / n).gray();

			std_sort(buf.begin(), buf.end());
			if (!(size % 2)) new_img.at(px + mid, py + mid).gray(buf[size >> 1]);
			else new_img.at(px + mid, py + mid).gray((buf[size >> 1] + buf[(size + 1) >> 1]) / 2);

			// convert to binary image
			if (new_img.at(px + mid, py + mid).gray() < 128) new_img.at(px + mid, py + mid).is_black(true);
			else new_img.at(px + mid, py + mid).is_black(false);
		}
	}

	return new_img;
}
// \note only for binary image denoising
inline image_type sh_dn_discrete_denoising(image_type const& old_img, int n = 3, int hreshold = 3)
{
	int mid = n >> 1;
	image_type new_img(old_img);
	for (int px = 0; px < (int)old_img.width() - n; ++px)
	{
		for (int py = 0; py < (int)old_img.height() - n; ++py)
		{
			if (old_img.at(px + mid, py + mid).is_black())
			{
				int sum = 0;
				for (int k = 0; k < n * n; ++k)
				{
					sum += old_img.at(px + k % n, py + k / n).is_black()? 1 : 0;
				}

				if (sum < hreshold)	// exclude self
					new_img.at(px + mid, py + mid).is_black(false);
			}
		}
	}
	return new_img;
}
#endif // SH_DN_H
