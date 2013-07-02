#ifndef SH_SC_H
#define SH_SC_H

#include "sh_ed.h"

// Content-Aware Image Resizing using Seam Carving
#if 0
typedef basic_matrix<double>					float_image_type;
typedef basic_matrix<double>					float_image_type;

// gradient image
inline float_image_type sh_sc_impl_gradient_image(image_type const& old_img, scoped_buffer<double*> const& templates, int n)
{
	int mid = n >> 1;
	int w = (int)old_img.width();
	int h = (int)old_img.height();
	float_image_type grad_img(w, h);
	for (int px = -mid; px < w - mid; ++px)
	{
		for (int py = -mid; py < h - mid; ++py)
		{
			scoped_buffer<double> gs(0.0, templates.size());
			double g = 0;
			for (int i = 0; i < (int)templates.size(); ++i)
			{
				for (int k = 0; k < n * n; ++k)
				{
					int xx = px + k % n;
					int yy = py + k / n;
					if (xx < 0) xx = 0;
					if (yy < 0) yy = 0;
					if (xx > w - 1) xx = w - 1;
					if (yy > h - 1) yy = h - 1;
					
					gs[i] += old_img.at(xx, yy).gray() * templates[i][k];
				}
				g += fabs(gs[i]);
				//g += gs[i] * gs[i];
			}
			//grad_img.at(px + mid, py + mid) = g;
			//grad_img.at(px + mid, py + mid) = xtl_sqrt(g);
			//grad_img.at(px + mid, py + mid) = g / (templates.size() * n * n) > 5? g : 0;
			grad_img.at(px + mid, py + mid) = g > 256? 255 : g;
		}
	}

	return grad_img;
}

inline scoped_buffer<double*> sh_sc_sobel()
{
	static double s1[9] =	{	-1, -2, -1
							,	0, 0, 0
							,	1, 2, 1
							};

	static double s2[9] =	{	-1, 0, 1
							,	-2, 0, 2
							,	-1, 0, 1
							};

	/*static double s3[9] =	{	0, -1, -2
							,	1, 0, -1
							,	2, 1, 0
							};

	static double s4[9] =	{	0, 1, 2
							,	-1, 0, 1
							,	-2, -1, 0
							};*/

	scoped_buffer<double*> templates;
	templates.push_back((double*)s1);
	templates.push_back((double*)s2);
	//templates.push_back((double*)s3);
	//templates.push_back((double*)s4);

	return templates;
}

inline scoped_buffer<double*> sh_sc_prewitt()
{
	static double s1[9] =	{	-1, -1, -1
							,	0, 0, 0
							,	1, 1, 1
							};

	static double s2[9] =	{	-1, 0, 1
							,	-1, 0, 1
							,	-1, 0, 1
							};

	scoped_buffer<double*> templates;
	templates.push_back((double*)s1);
	templates.push_back((double*)s2);

	return templates;
}

inline scoped_buffer<double*> sh_sc_isotropic()
{
	static double s1[9] =	{	-1, -1.414213, -1
							,	0, 0, 0
							,	1, 1.414213, 1
							};

	static double s2[9] =	{	-1, 0, 1
							,	-1.414213, 0, 1.414213
							,	-1, 0, 1
							};

	scoped_buffer<double*> templates;
	templates.push_back((double*)s1);
	templates.push_back((double*)s2);

	return templates;
}
inline float_image_type sh_sc_horizontal_energy(float_image_type const& grad_img)
{
	float_image_type energy_img(grad_img);
	for (int px = 1; px < (int)grad_img.row(); ++px)
	{
		for (int py = 0; py < (int)grad_img.col(); ++py)
		{
			if (py == 0) energy_img.at(px, py) += xtl_min(energy_img.at(px - 1, py), energy_img.at(px - 1, py + 1));
			else if (py == (int)grad_img.col() - 1) energy_img.at(px, py) += xtl_min(energy_img.at(px - 1, py - 1), energy_img.at(px - 1, py));
			else energy_img.at(px, py) += xtl_min(energy_img.at(px - 1, py - 1), energy_img.at(px - 1, py), energy_img.at(px - 1, py + 1));
		}
	}
	return energy_img;
}
inline float_image_type sh_sc_vertical_energy(float_image_type const& grad_img)
{
	float_image_type energy_img(grad_img);
	for (int py = 1; py < (int)grad_img.col(); ++py)
	{
		for (int px = 0; px < (int)grad_img.row(); ++px)
		{
			if (px == 0) energy_img.at(px, py) += xtl_min(energy_img.at(px, py - 1), energy_img.at(px + 1, py - 1));
			else if (px == (int)grad_img.row() - 1) energy_img.at(px, py) += xtl_min(energy_img.at(px - 1, py - 1), energy_img.at(px, py - 1));
			else energy_img.at(px, py) += xtl_min(energy_img.at(px - 1, py - 1), energy_img.at(px, py - 1), energy_img.at(px + 1, py - 1));
		}
	}
	return energy_img;
}
inline image_type sh_sc_vertical_remove(image_type const& old_img, float_image_type& energy_img, int n)
{
	int px, py;
	int w = (int)energy_img.row();
	int h = (int)energy_img.col();

	image_type new_img(old_img);
	while (n-- && w > 0)
	{
		// find the position of minimum energy
		double min_pos = 0;
		for (px = 0; px < w; ++px)
			min_pos = energy_img.at(px, h - 1) < energy_img.at(min_pos, h - 1)? px : min_pos;

		image_type tmp_img(w - 1, h);
		//float_image_type tmp_enery(w - 1, h);
		for (py = h - 1; py >= 0; --py)
		{
			// find position
			if (py == h - 1) ;
			else if (min_pos == 0)
				min_pos = energy_img.at(min_pos, py) < energy_img.at(min_pos + 1, py)? min_pos : min_pos + 1;
			else if (min_pos == w - 1)
				min_pos = energy_img.at(min_pos - 1, py) < energy_img.at(min_pos, py)? min_pos - 1 : min_pos;
			else
			{
				int min_pos_2 = energy_img.at(min_pos, py) < energy_img.at(min_pos + 1, py)? min_pos : min_pos + 1;
				min_pos = energy_img.at(min_pos_2, py) < energy_img.at(min_pos - 1, py)? min_pos_2 : min_pos - 1;
			}

			int ppx = 0;
			for (px = 0; px < w; ++px)
			{
				if (px != min_pos)
				{
					tmp_img.at(ppx, py) = new_img.at(px, py);
					//tmp_enery.at(ppx, py) = energy_img.at(px, py);
					++ppx;
				}
			}
		}

		new_img = tmp_img;
		//energy_img = tmp_enery;
		--w;
	}

	return new_img;
}
inline image_type sh_sc_horizontal_remove(image_type const& old_img, float_image_type& energy_img, int n)
{
	int px, py;
	int w = (int)energy_img.row();
	int h = (int)energy_img.col();

	image_type new_img(old_img);
	while (n-- && h > 0)
	{
		// find the position of minimum energy
		double min_pos = 0;
		for (py = 0; py < h; ++py)
			min_pos = energy_img.at(h - 1, py) < energy_img.at(h - 1, min_pos)? py : min_pos;

		image_type tmp_img(w, h - 1);
		for (px = w - 1; px >= 0; --px)
		{
			// find position
			if (px == w - 1) ;
			else if (min_pos == 0)
				min_pos = energy_img.at(px, min_pos) < energy_img.at(px, min_pos + 1)? min_pos : min_pos + 1;
			else if (min_pos == h - 1)
				min_pos = energy_img.at(px, min_pos - 1) < energy_img.at(px, min_pos)? min_pos - 1 : min_pos;
			else
			{
				int min_pos_2 = energy_img.at(px, min_pos) < energy_img.at(px, min_pos + 1)? min_pos : min_pos + 1;
				min_pos = energy_img.at(px, min_pos_2) < energy_img.at(px, min_pos - 1)? min_pos_2 : min_pos - 1;
			}

			int ppy = 0;
			for (py = 0; py < h; ++py)
			{
				if (py != min_pos)
				{
					tmp_img.at(px, ppy) = new_img.at(px, py);
					++ppy;
				}
			}
		}

		new_img = tmp_img;
		--h;
	}

	return new_img;
}
// seam carving zoom out
inline image_type sh_sc_zoom_out(image_type const& old_img, int w, int h)
{
	//float_image_type grad_img = sh_sc_impl_gradient_image(old_img, sh_sc_sobel(), 3);
	//float_image_type grad_img = sh_sc_impl_gradient_image(old_img, sh_sc_prewitt(), 3);
	//float_image_type grad_img = sh_sc_impl_gradient_image(old_img, sh_sc_isotropic(), 3);
	//float_image_type energy_img = sh_sc_vertical_energy(grad_img);
	//float_image_type energy_img = sh_sc_horizontal_energy(grad_img);
	//image_type new_img = sh_sc_horizontal_remove(old_img, energy_img, 100);
	//image_type new_img = sh_sc_vertical_remove(old_img, energy_img, 174);

	image_type new_img(old_img);
	int zoom_w = old_img.width() - w;
	int zoom_h = old_img.height() - h;
	while (zoom_w > 0 || zoom_h > 0)
	{
		image_type tmp_img(new_img);

		float_image_type grad_img;
		float_image_type energy_img;
		if (zoom_w > 0)
		{
			grad_img = sh_sc_impl_gradient_image(tmp_img, sh_sc_sobel(), 3);
			energy_img = sh_sc_vertical_energy(grad_img);
			new_img = sh_sc_vertical_remove(tmp_img, energy_img, 1);
			--zoom_w;
		}

		if (zoom_h > 0)
		{
			tmp_img = new_img;
			grad_img = sh_sc_impl_gradient_image(tmp_img, sh_sc_sobel(), 3);
			energy_img = sh_sc_horizontal_energy(grad_img);
			new_img = sh_sc_horizontal_remove(tmp_img, energy_img, 1);
			--zoom_h;
		}
	}

	//int px, py;
	//double max_v = 0;
	// show grad image
	/*image_type new_img(grad_img.row(), grad_img.col());
	for (px = 0; px < (int)grad_img.row(); ++px)
		for (py = 0; py < (int)grad_img.col(); ++py)
			max_v = grad_img.at(px, py) > max_v? grad_img.at(px, py) : max_v;

	for (px = 0; px < (int)grad_img.row(); ++px)
		for (py = 0; py < (int)grad_img.col(); ++py)
			//new_img.at(px, py).gray((int)grad_img.at(px, py) * 256 / max_v);
			new_img.at(px, py).gray(((int)grad_img.at(px, py)) > 256? 255 : (int)grad_img.at(px, py));*/

	/*image_type new_img(energy_img.row(), energy_img.col());
	for (px = 0; px < (int)energy_img.row(); ++px)
		for (py = 0; py < (int)energy_img.col(); ++py)
			max_v = energy_img.at(px, py) > max_v? energy_img.at(px, py) : max_v;

	for (px = 0; px < (int)energy_img.row(); ++px)
		for (py = 0; py < (int)energy_img.col(); ++py)
			new_img.at(px, py).gray((int)energy_img.at(px, py) * 256 / max_v);*/
			//new_img.at(px, py).gray((int)energy_img.at(px, py) > 256? 255 : (int)energy_img.at(px, py));

	return new_img;
}
#endif
#endif // SH_SC_H
