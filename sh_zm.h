#ifndef SH_ZM_H
#define SH_ZM_H

#include "prefix.h"
#include "sh_sc.h"

// nearest_neighbor_zoom
inline image_type sh_zm_nearest_neighbor_zoom(image_type const& old_img, int w, int h)
{
	double fh = (double)h / old_img.height();
	double fw = (double)w / old_img.width();

	int part_w = int(fw + 1);
	int part_h = int(fh + 1);

	int px, py;
	// clear
	image_type new_img(w, h);
	for (px = 0; px < new_img.width(); ++px)
		for (py = 0; py < new_img.height(); ++py)
			new_img.at(px, py).is_black(false);

	// interpolation
	for (px = 0; px < old_img.width(); ++px)
	{
		for (py = 0; py < old_img.height(); ++py)
		{
			for (int k = 0; k < part_w * part_h; ++k)
			{
				int new_y = (int)(py * fh + k / part_w);
				new_y = new_y < new_img.height()? new_y : (new_img.height() - 1);

				int new_x = (int)(px * fw + k % part_w);
				new_x = new_x < new_img.width()? new_x : (new_img.width() - 1);

				// fill nearest neighbor pixel
				new_img.at(new_x, new_y) = old_img.at(px, py);
			}
		}
	}

	return new_img;
}
// zoom out
inline image_type sh_zm_zoom_out(image_type const& old_img, int w, int h, bool is_binary)
{
	if (w == 0 || h == 0) return old_img;

	double fw = (double)old_img.width() / w;
	double fh = (double)old_img.height() / h;

	int part_w = int(fw + 1);
	int part_h = int(fh + 1);
	//int part_w = xtl_round45(fw);
	//int part_h = xtl_round45(fh);

	int px, py;
	// clear
	image_type new_img(w, h);
	for (px = 0; px < new_img.width(); ++px)
		for (py = 0; py < new_img.height(); ++py)
			new_img.at(px, py).is_black(false);

	for (px = 0; px < w; ++px)
	{
		for (py = 0; py < h; ++py)
		{
			double avg_g = 0, num = 0;
			for (int k = 0; k < part_w * part_h; ++k)
			{
				int xx = int(px * fw + (k % part_w));
				int yy = int(py * fh + (k / part_w));
				if (xx >= 0 && xx < old_img.width() && yy >= 0 && yy < old_img.height())
				{
					avg_g += old_img.at(int(px * fw + (k % part_w)), int(py * fh + (k / part_w))).gray();
					num++;
				}
			}
			if (num > 0) avg_g /= num;
			else avg_g = 255;
			if (is_binary) new_img.at(px, py).is_black(avg_g < 255);
			else new_img.at(px, py).gray(int(avg_g));
		}
	}

	return new_img;
}
// bilinear zoom in
inline image_type sh_zm_bilinear_zoom_in(image_type const& old_img, int w, int h, bool is_binary)
{
	double fh = (double)h / old_img.height();
	double fw = (double)w / old_img.width();

	int part_w = int(fw + 1);
	int part_h = int(fh + 1);

	//int part_w = xtl_round45(fw);
	//int part_h = xtl_round45(fh);

	int px, py;
	// clear
	image_type new_img(w, h);
	for (px = 0; px < new_img.width(); ++px)
		for (py = 0; py < new_img.height(); ++py)
			new_img.at(px, py).is_black(false);

	// interpolation
	for (px = 0; px < old_img.width() - 1; ++px)
	{
		for (py = 0; py < old_img.height() - 1; ++py)
		{
			int f00 = old_img.at(px, py).gray();
			int f01 = old_img.at(px + 1, py).gray();
			int f10 = old_img.at(px, py + 1).gray();
			int f11 = old_img.at(px + 1, py + 1).gray();

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

				if (is_binary)
				{
					new_img.at(new_x, new_y).is_black(gray < 128);

					if ((part_w == 1 || part_h == 1) && !new_img.at(new_x, new_y).is_black())
					{
						int num = 0;
						double ffh = (double)old_img.height() / h;
						double ffw = (double)old_img.width() / w;

						int ppxw = xtl_min(px + int(ffw + 1), (int)old_img.width() - 1);
						int ppyh = xtl_min(py + int(ffh + 1), (int)old_img.height() - 1);
						for (int ppx = px; ppx < ppxw; ++ppx)
							for (int ppy = py; ppy < ppyh; ++ppy)
								if (old_img.at(ppx, ppy).is_black()) ++num;

						if (num > 0) new_img.at(new_x, new_y).is_black(true);
					}
				}
				else new_img.at(new_x, new_y).gray(gray);
			}
		}
	}

	return new_img;
}

inline image_type sh_zm_bilinear_zoom(image_type const& old_img, int w, int h, bool is_binary)
{
	image_type new_img(old_img);
	if (w > old_img.width() && h > old_img.height()) new_img = sh_zm_nearest_neighbor_zoom(new_img, w, h);
	else if (w < old_img.width() && h < old_img.height()) new_img = sh_zm_zoom_out(new_img, w, h, is_binary);
	else
	{
		if (w > old_img.width()) new_img = sh_zm_nearest_neighbor_zoom(new_img, w, new_img.height());
		if (h > old_img.height()) new_img = sh_zm_nearest_neighbor_zoom(new_img, new_img.width(), h);
		if (w < old_img.width()) new_img = sh_zm_zoom_out(new_img, w, new_img.height(), is_binary);
		if (h < old_img.height()) new_img = sh_zm_zoom_out(new_img, new_img.width(), h, is_binary);
	}
	
	/*if (w > old_img.width() && h > old_img.height()) new_img = sh_zm_nearest_neighbor_zoom(new_img, w, h);
	else if (w < old_img.width() && h < old_img.height()) new_img = sh_sc_zoom_out(new_img, w, h);
	else
	{
		if (w > old_img.width()) new_img = sh_zm_nearest_neighbor_zoom(new_img, w, new_img.height());
		if (h > old_img.height()) new_img = sh_zm_nearest_neighbor_zoom(new_img, new_img.width(), h);
		if (w < old_img.width()) new_img = sh_sc_zoom_out(new_img, w, new_img.height());
		if (h < old_img.height()) new_img = sh_sc_zoom_out(new_img, new_img.width(), h);
	}*/
	return new_img;
}
#endif // SH_ZM_H
