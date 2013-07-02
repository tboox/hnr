#ifndef SH_RL_H
#define SH_RL_H

#include "prefix.h"

typedef basic_list<point_type>					point_list_type;
// region labeling split
inline void sh_rl_labeling_split_image_impl(image_type const& old_img, scoped_buffer<point_list_type*>& label_table)
{
	basic_matrix<int>	label_matrix(old_img.height(), old_img.width());

	int nolabel = old_img.width() * old_img.height() + 1;

	// initialize
	int px, py;
	for (px = 0; px < (int)old_img.width(); ++px)
	{
		if (old_img.at(px, 0).is_black())
		{
			label_matrix.at(0, px) = label_table.size();

			point_list_type* plist = new point_list_type();
			plist->push_back(point_type(px, 0));
			label_table.push_back(plist);
		}
		else label_matrix.at(0, px) = nolabel;
	}
	/*for (py = 1; py < (int)old_img.height(); ++py)
	{
		if (old_img.at(0, py).is_black())
		{
			label_matrix.at(py, 0) = label_table.size();

			point_list_type* plist = new point_list_type();
			plist->push_back(point_type(0, py));
			label_table.push_back(plist);
		}
		else label_matrix.at(py, 0) = nolabel;
	}*/

	for (py = 1; py < (int)old_img.height(); ++py)
	{
		if (old_img.at(0, py).is_black())
		{
			label_matrix.at(py, 0) = label_table.size();

			point_list_type* plist = new point_list_type();
			plist->push_back(point_type(0, py));
			label_table.push_back(plist);
		}
		else label_matrix.at(py, 0) = nolabel;

		for (px = 1; px < (int)old_img.width(); ++px)
		{
			if (old_img.at(px, py).is_black())
			{
				//if (px + 1 >= (int)old_img.width())
				//	label_matrix.at(py - 1, px + 1) = nolabel;

				int label = xtl_min(label_matrix.at(py, px - 1), label_matrix.at(py - 1, px - 1), label_matrix.at(py - 1, px), px + 1 < (int)old_img.width()? label_matrix.at(py - 1, px + 1) : nolabel);
				if (label != nolabel)
				{
					EXTL_ASSERT(label_table[label] != NULL);
					label_table[label]->push_back(point_type(px, py));
					//label_table[label]->push_front(point_type(px, py));
					label_matrix.at(py, px) = label;

					// merge lables
					if (old_img.at(px - 1, py).is_black() && label_matrix.at(py, px - 1) != label)
					{
						int old_label = label_matrix.at(py, px - 1);
						point_list_type* plist = label_table[old_label];
						label_table[label]->insert(label_table[label]->end(), plist->begin(), plist->end());
						//label_table[label]->insert(label_table[label]->begin(), plist->begin(), plist->end());
						for (point_list_type::iterator p = plist->begin(); p != plist->end(); ++p) label_matrix.at((*p).y(), (*p).x()) = label;
						delete label_table[old_label];
						label_table[old_label] = NULL;
						//label_matrix.at(py, px - 1) = label;
					}
					if (old_img.at(px - 1, py - 1).is_black() && label_matrix.at(py - 1, px - 1) != label)
					{
						int old_label = label_matrix.at(py - 1, px - 1);
						point_list_type* plist = label_table[old_label];
						label_table[label]->insert(label_table[label]->end(), plist->begin(), plist->end());
						//label_table[label]->insert(label_table[label]->begin(), plist->begin(), plist->end());
						for (point_list_type::iterator p = plist->begin(); p != plist->end(); ++p) label_matrix.at((*p).y(), (*p).x()) = label;
						delete label_table[old_label];
						label_table[old_label] = NULL;
						//label_matrix.at(py - 1, px - 1) = label;
					}
					if (old_img.at(px, py - 1).is_black() && label_matrix.at(py - 1, px) != label)
					{
						int old_label = label_matrix.at(py - 1, px);
						point_list_type* plist = label_table[old_label];
						label_table[label]->insert(label_table[label]->end(), plist->begin(), plist->end());
						//label_table[label]->insert(label_table[label]->begin(), plist->begin(), plist->end());
						for (point_list_type::iterator p = plist->begin(); p != plist->end(); ++p) label_matrix.at((*p).y(), (*p).x()) = label;
						delete label_table[old_label];
						label_table[old_label] = NULL;
						//label_matrix.at(py - 1, px) = label;
					}
					if (px + 1 < (int)old_img.width() && old_img.at(px + 1, py - 1).is_black() && label_matrix.at(py - 1, px + 1) != label)
					{
						int old_label = label_matrix.at(py - 1, px + 1);
						point_list_type* plist = label_table[old_label];
						label_table[label]->insert(label_table[label]->end(), plist->begin(), plist->end());
						//label_table[label]->insert(label_table[label]->begin(), plist->begin(), plist->end());
						for (point_list_type::iterator p = plist->begin(); p != plist->end(); ++p) label_matrix.at((*p).y(), (*p).x()) = label;
						delete label_table[old_label];
						label_table[old_label] = NULL;
						//label_matrix.at(py - 1, px + 1) = label;
					}
				}
				else
				{
					label_matrix.at(py, px) = label_table.size();

					point_list_type* plist = new point_list_type();
					plist->push_back(point_type(px, py));
					label_table.push_back(plist);
				}
			}
			else label_matrix.at(py, px) = nolabel;
		}
	}
}

inline image_type sh_rl_labeling_split_on_color(image_type const& old_img)
{
	scoped_buffer<point_list_type*> label_table;
	sh_rl_labeling_split_image_impl(old_img, label_table);

	int count = 0;
	image_type new_img(old_img);
	for (int i = 0; i < (int)label_table.size(); ++i)
	{
		if (label_table[i] != NULL)
		{
			++count;
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;
			point_list_type* plist = label_table[i];
			for (point_list_type::iterator p = plist->begin(); p != plist->end(); ++p)
			{
				new_img.at((*p).x(), (*p).y()).red(r);
				new_img.at((*p).x(), (*p).y()).green(g);
				new_img.at((*p).x(), (*p).y()).blue(b);
			}

			delete label_table[i];
			label_table[i] = NULL;
		}
	}

	QMessageBox::warning(NULL, "", QObject::tr("count: %1").arg(count));
	return new_img;
}

struct sh_rl_image_info
{
	sh_rl_image_info(point_type const& p = point_type(), image_type const& img = image_type())
			: pos(p), image(img)
	{
	}
	point_type	pos;
	image_type	image;
};
typedef scoped_buffer<sh_rl_image_info*>			pimages_info_type;
typedef basic_matrix<sh_rl_image_info*>				pimages_info_mtx_type;
typedef scoped_buffer<pimages_info_type>			pimages_info_row_type;

inline pimages_info_mtx_type sh_rl_labeling_split_to_matrix(image_type const& old_img, bool is_filter = true)
{
	// split images
	scoped_buffer<point_list_type*> label_table;
	sh_rl_labeling_split_image_impl(old_img, label_table);

	// save splited images
	pimages_info_mtx_type pimgs_info_mtx(static_cast<sh_rl_image_info*>(NULL), old_img.height(), old_img.width());
	for (int i = 0; i < (int)label_table.size(); ++i)
	{
		if (label_table[i] != NULL)
		{
			point_list_type* plist = label_table[i];

			int max_x = 0, max_y = 0;
			int min_x = old_img.width() + 1, min_y = old_img.height() + 1;
			for (point_list_type::iterator p = plist->begin(); p != plist->end(); ++p)
			{
				min_x = (*p).x() < min_x? (*p).x() : min_x;
				min_y = (*p).y() < min_y? (*p).y() : min_y;

				max_x = (*p).x() > max_x? (*p).x() : max_x;
				max_y = (*p).y() > max_y? (*p).y() : max_y;
			}

			// filter smaller image
			int w = max_x - min_x + 1;
			int h = max_y - min_y + 1;
			if ((!is_filter && w > 0 && h > 0) || (is_filter && w > 0 && h > 4 && w < 100 && h < 200 && (double(h) / w) > 0.5))
			{
				sh_rl_image_info* pimg_info = new sh_rl_image_info(point_type((min_x + max_x) / 2, (min_y + max_y) / 2), image_type(w + 2, h + 2));
				for (int px = 0; px < (int)pimg_info->image.width(); ++px)
					for (int py = 0; py < (int)pimg_info->image.height(); ++py)
						pimg_info->image.at(px, py).is_black(false);

				for (point_list_type::iterator q = plist->begin(); q != plist->end(); ++q)
					pimg_info->image.at((*q).x() - min_x + 1, (*q).y() - min_y + 1).is_black(true);

				pimgs_info_mtx.at(pimg_info->pos.y(), pimg_info->pos.x()) = pimg_info;
			}

			delete label_table[i];
			label_table[i] = NULL;
		}
	}

	return pimgs_info_mtx;
}
struct sh_rl_comparer
{
	bool operator()(sh_rl_image_info const* lhs, sh_rl_image_info const* rhs) const
	{
		return (lhs->pos.x() < rhs->pos.x());
	}
};

inline pimages_info_row_type sh_rl_labeling_split_to_row(image_type const& old_img, bool is_filter = true)
{
	pimages_info_mtx_type pimgs_info_mtx = sh_rl_labeling_split_to_matrix(old_img, is_filter);

	// stats histogram
	int px, py;
	int h = 0, n = 0;
	scoped_buffer<bool> hs(false, pimgs_info_mtx.row());
	for (py = 0; py < (int)pimgs_info_mtx.row(); ++py)
	{
		for (px = 0; px < (int)pimgs_info_mtx.col(); ++px)
		{
			if (pimgs_info_mtx.at(py, px) != NULL)
			{
				h += pimgs_info_mtx.at(py, px)->image.height();
				++n;
				hs[py] = true;
				break;
			}
		}
	}
	if (n == 0) return scoped_buffer<pimages_info_type>();

	// adaptive connective threshold
	int hr = xtl_round45(double(h) * 0.4 / double(n));

	scoped_buffer<pimages_info_type> pimgs_info_row;
	for (py = 0; py < (int)pimgs_info_mtx.row(); ++py)
	{
		if (!hs[py]) continue;

		// Judge connectivity(interval: hr)
		bool is_connected = false;
		for (int i = (py > hr? (py - hr) : 0); i < py; ++i)
		{
			if (hs[i])
			{
				is_connected = true;
				break;
			}
		}

		if (is_connected && pimgs_info_row.size() > 0)	// add to current row
		{
			for (px = 0; px < (int)pimgs_info_mtx.col(); ++px)
			{
				if (pimgs_info_mtx.at(py, px) != NULL)
					pimgs_info_row.back().push_back(pimgs_info_mtx.at(py, px));
			}
		}
		else	// new row
		{
			pimages_info_type pimgs_info;
			for (px = 0; px < (int)pimgs_info_mtx.col(); ++px)
			{
				if (pimgs_info_mtx.at(py, px) != NULL)
					pimgs_info.push_back(pimgs_info_mtx.at(py, px));
			}
			pimgs_info_row.push_back(pimgs_info);
		}
	}

	for (int i = 0; i < (int)pimgs_info_row.size(); ++i)
		xtl_sort(pimgs_info_row[i].begin(), pimgs_info_row[i].end(), sh_rl_comparer());

	return pimgs_info_row;
}

#endif // SH_RL_H
