#ifndef SH_DK_H
#define SH_DK_H

#include "prefix.h"

// gets the digital region in the image
inline basic_rect<int> sh_dk_digital_region(image_type const& old_img, int margin = 1)
{
	basic_rect<int> region;

	// stats the number of pixels at every rows
	int py, px;
	scoped_buffer<int> hstats(old_img.height());
	for (py = 0; py < old_img.height(); ++py)
	{
		hstats[py] = 0;
		for (px = 0; px < old_img.width(); ++px)
			if (old_img.at(px, py).is_black()) ++hstats[py];
	}

	// split by height
	for (py = 0; py < old_img.height(); ++py)
	{
		if (hstats[py] > 0)
		{
			region.top(py);
			break;
		}
	}
	if (py == old_img.height()) region.top(old_img.height() - 1);
	if (region.top() - margin >= 0) region.top(region.top() - margin);

	for (py = old_img.height(); py > 0; --py)
	{
		if (hstats[py - 1] > 0)
		{
			region.bottom(py - 1);
			break;
		}
	}
	if (py == 0) region.bottom(0);
	if (region.bottom() + margin < old_img.height()) region.bottom(region.bottom() + margin);
	EXTL_ASSERT(region.bottom() > region.top());

	// stats the number of pixels at every columns
	scoped_buffer<int> wstats(old_img.width());
	for (px = 0; px < old_img.width(); ++px)
	{
		wstats[px] = 0;
		for (py = 0; py < old_img.height(); ++py)
			if (old_img.at(px, py).is_black()) ++wstats[px];
	}

	// split by width
	for (px = 0; px < old_img.width(); ++px)
	{
		if (wstats[px] > 0)
		{
			region.left(px);
			break;
		}
	}
	if (px == old_img.width()) region.left(old_img.width() - 1);
	if (region.left() - margin >= 0) region.left(region.left() - margin);

	for (px = old_img.width(); px > 0; --px)
	{
		if (wstats[px - 1] > 0)
		{
			region.right(px - 1);
			break;
		}
	}
	if (px == 0) region.right(0);
	if (region.right() + margin < old_img.width()) region.right(region.right() + margin);
	EXTL_ASSERT(region.right() > region.left());

	return region;
}
// horizontal_side_slip_deskew
/*inline image_type __sh_dk_horizontal_side_slip_deskew(image_type const& old_img)
{
	int py, px;
	double angle = EXTL_PI / 4;

	image_type mid_tmp(old_img.width() + 10, old_img.height() + 10);
	for (py = 0; py < mid_tmp.height(); ++py)
	{
		for (px = 0; px < mid_tmp.width(); ++px)
		{
			if (py < 5 || px < 5 || py >= mid_tmp.height() - 5 || px >= mid_tmp.width() - 5)
				mid_tmp.at(px, py).is_black(false);
			else mid_tmp.at(px, py).is_black(old_img.at(px - 5, py - 5).is_black());
		}
	}

	while (angle > EXTL_PI / 180)
	{
		// calculate the real position of image included pixels
		basic_rect<int> mid_pos = sh_dk_digital_region(mid_tmp);

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
					int new_x = xtl_round45(px - (py - ((double)left_tmp.height() / 2.0)) / slope);
					if (new_x >= 0 && new_x < left_tmp.width())
						left_tmp.at(new_x, py).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> left_pos = sh_dk_digital_region(left_tmp);

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
					int new_x = xtl_round45(px - (py - ((double)right_tmp.height() / 2.0)) / slope);
					if (new_x >= 0 && new_x < right_tmp.width())
						right_tmp.at(new_x, py).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> right_pos = sh_dk_digital_region(right_tmp);

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
	basic_rect<int> mid_pos = sh_dk_digital_region(mid_tmp);
	image_type new_img(mid_pos.width(), mid_pos.height());
	for (py = mid_pos.top(); py <= mid_pos.bottom(); ++py)
		for (px = mid_pos.left(); px <= mid_pos.right(); ++px)
			new_img.at(px - mid_pos.left(), py - mid_pos.top()).is_black(mid_tmp.at(px, py).is_black());
	return new_img;
}*/
// horizontal_side_slip_deskew
inline image_type sh_dk_horizontal_side_slip_deskew(image_type const& old_img)
{
	int py, px;
	double angle = EXTL_PI / 4;

	image_type mid_tmp(old_img.width() + 10, old_img.height() + 10);
	for (py = 0; py < mid_tmp.height(); ++py)
	{
		for (px = 0; px < mid_tmp.width(); ++px)
		{
			if (py < 5 || px < 5 || py >= mid_tmp.height() - 5 || px >= mid_tmp.width() - 5)
				mid_tmp.at(px, py).is_black(false);
			else mid_tmp.at(px, py).is_black(old_img.at(px - 5, py - 5).is_black());
		}
	}

	// calculate the real position of image included pixels
	basic_rect<int> mid_pos = sh_dk_digital_region(mid_tmp);

	double best_angle = 0;
	int min_w = mid_pos.width();
	while (angle > EXTL_PI / 180)
	{
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
					double slope = tan(EXTL_PI / 2 + best_angle + angle);
					int new_x = xtl_round45(px - (py - ((double)left_tmp.height() / 2.0)) / slope);
					if (new_x >= 0 && new_x < left_tmp.width())
						left_tmp.at(new_x, py).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> left_pos = sh_dk_digital_region(left_tmp);

		// right transform
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
					double slope = tan(EXTL_PI / 2 + best_angle - angle);
					int new_x = xtl_round45(px - (py - ((double)right_tmp.height() / 2.0)) / slope);
					if (new_x >= 0 && new_x < right_tmp.width())
						right_tmp.at(new_x, py).is_black(true);
				}
			}
		}

		// calculate the real position of image included pixels
		basic_rect<int> right_pos = sh_dk_digital_region(right_tmp);

		// select better image
		if (right_pos.width() < left_pos.width())
		{
			if (right_pos.width() < min_w)
			{
				min_w = right_pos.width();
				best_angle -= angle;
			}
		}
		else
		{
			if (left_pos.width() < min_w)
			{
				min_w = left_pos.width();
				best_angle += angle;
			}
		}
		angle /= 2;
	}

	// best transform
	image_type best_tmp(mid_tmp.width(), mid_tmp.height());
	for (py = 0; py < best_tmp.height(); ++py)
		for (px = 0; px < best_tmp.width(); ++px)
			best_tmp.at(px, py).is_black(false);

	for (py = 0; py < best_tmp.height(); ++py)
	{
		for (px = 0; px < best_tmp.width(); ++px)
		{
			if (mid_tmp.at(px, py).is_black())
			{
				double slope = tan(EXTL_PI / 2 + best_angle);
				int new_x = xtl_round45(px - (py - ((double)best_tmp.height() / 2.0)) / slope);
				if (new_x >= 0 && new_x < best_tmp.width())
					best_tmp.at(new_x, py).is_black(true);
			}
		}
	}

	// update
	basic_rect<int> best_pos = sh_dk_digital_region(best_tmp);
	image_type new_img(best_pos.width(), best_pos.height());
	for (py = best_pos.top(); py <= best_pos.bottom(); ++py)
		for (px = best_pos.left(); px <= best_pos.right(); ++px)
			new_img.at(px - best_pos.left(), py - best_pos.top()).is_black(best_tmp.at(px, py).is_black());
	return new_img;
}

#endif // SH_DK_H
