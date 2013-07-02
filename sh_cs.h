#ifndef SH_CS_H
#define SH_CS_H

// cluster split
#include "prefix.h"

typedef scoped_buffer<image_type>	images_type;
typedef scoped_buffer<point_type>	points_type;

struct sh_cs_class
{
	point_type	center;
	point_type	reserve1;
	points_type	pts;
	rect_type	region;
	int			density;
	double		reserve2;
};
typedef sh_cs_class					class_type;
typedef scoped_buffer<sh_cs_class>	classes_type;

struct comparer
{
	bool operator()(class_type const& lhs, class_type const& rhs) const
	{
		return (lhs.density < rhs.density);
	}
};

inline classes_type sh_cs_kmean_density_centers(image_type const& old_img, int k, int part_n = 50)
{
	if (old_img.is_empty()) return classes_type();

	int i, j;
	// calculate part_n
	points_type pts;
	for (int px = 0; px < (int)old_img.width(); ++px)
		for (int py = 0; py < (int)old_img.height(); ++py)
			if (old_img.at(px, py).is_black()) pts.push_back(point_type(px, py));

	double avg_d = 0;
	double n = 0;
	for (i = 0; i < (int)pts.size(); ++i)
	{
		for (j = i; j < (int)pts.size(); ++j)
		{
			double d = (pts[i].x() - pts[j].x()) * (pts[i].x() - pts[j].x());
			d += (pts[i].y() - pts[j].y()) * (pts[i].y() - pts[j].y());
			d = xtl_sqrt(d);
			avg_d += d;
			++n;
		}
	}
	avg_d /= n;
	part_n = int(avg_d * 0.35);

	QMessageBox::warning(NULL, "", QObject::tr("%1 %2").arg(avg_d).arg(part_n));

	// the image is too small
	if (old_img.width() < part_n || old_img.height() < part_n)
		part_n = xtl_min(old_img.width(), old_img.height()) / 2;

	// traverse per-column
	int pixel_n = part_n * part_n;
	int part_n_2 = part_n >> 1;
	classes_type densities;
	for (int py = -part_n_2; py < (int)old_img.height() - part_n_2; ++py)
	{
		// initialize density
		int density = 0;
		for (i = 0; i < pixel_n; ++i)
		{
			if ((py + i / part_n) >= 0 && (py + i / part_n) < old_img.height())
				if (old_img.at(i % part_n_2, py + i / part_n).is_black()) ++density;
		}

		// stats partial histogram
		for (int px = -part_n_2; px < (int)old_img.width() - part_n_2; ++px)
		{
			if (old_img.at(px + part_n_2 , py + part_n_2).is_black())
			{
				class_type tmp;
				tmp.center = point_type(px + part_n_2 , py + part_n_2);
				tmp.density = density;
				tmp.region = rect_type(0, 0, 0, 0);
				tmp.reserve1 = point_type(0, 0);
				densities.push_back(tmp);
			}

			// update density
			for (i = 0; i < part_n; ++i)
			{
				if ((py + i) >= 0 && (py + i) < old_img.height())
				{
					// remove previous partial column
					if (px >= 0) if (old_img.at(px, py + i).is_black()) --density;

					// add next partial column
					if (px + part_n < old_img.width())
						if (old_img.at(px + part_n, py + i).is_black()) ++density;
				}
			}
		}
	}

	int sort_n = xtl_max((int)(densities.size() * 0.1), k);
	heap_sort_top_n(densities.begin(), densities.end(), sort_n, comparer());
	//QMessageBox::warning(NULL, "", QObject::tr("%1 %2").arg(sort_n).arg(densities.size()));
	//densities.erase(densities.begin() + sort_n, densities.end());
	/*classes_type cls;
	cls.push_back(densities.front());
	densities.erase(densities.begin());

	while ((int)cls.size() < k)
	{
		double max_d = 0;

		classes_type::iterator p;
		classes_type::iterator max_p = densities.begin();
		for (p = densities.begin(); p != densities.end(); ++p)
		{
			double avg_d = 0;
			for (i = 0; i < (int)cls.size(); ++i)
			{
				double d = ((*p).center.x() - cls[i].center.x()) * ((*p).center.x() - cls[i].center.x());
				d += ((*p).center.y() - cls[i].center. y()) * ((*p).center.y() - cls[i].center.y());
				d = xtl_sqrt(d);
				avg_d += d;
			}
			avg_d /= cls.size();

			if (avg_d > max_d)
			{
				max_d = avg_d;
				max_p = p;
			}
		}

		cls.push_back(*max_p);
		densities.erase(max_p);
	}*/
	classes_type cls;
	for (i = 0; k != 0 && i < (int)densities.size(); ++i, --k)
	{
		class_type c;
		c.center = densities[rand() % densities.size()].center;
		c.region = rect_type(0, 0, 0, 0);
		c.reserve1 = point_type(0, 0);
		cls.push_back(c);
	}

	
	/*classes_type cls;
	for (p = densities.begin(); k != 0 && p != densities.end(); ++p, --k)
	{
		class_type c;
		c.center = (*p).center;
		c.region = rect_type(0, 0, 0, 0);
		c.reserve1 = point_type(0, 0);
		cls.push_back(c);
	}*/

	return cls;
}
inline classes_type sh_cs_kmean(points_type const& old_pts, int k)
{
	if (old_pts.is_empty()) return classes_type();

	int i, j;
	// initialize cluster points
	classes_type cls(k);
	for (i = 0; i < (int)cls.size(); ++i)
	{
		cls[i].center = old_pts[rand() % old_pts.size()];
		cls[i].region = rect_type(0, 0, 0, 0);
		cls[i].reserve1 = point_type(0, 0);
	}

	int n = 0;
	double min_ds = -1;
	double min_ods = 0;
	while (1)
	{
		double ds = 0;
		for (i = 0; i < (int)old_pts.size(); ++i)
		{
			// find cluster point for the minmum distance between old_pts[i] and it
			double min_d = -1;
			int min_j = 0;
			for (j = 0; j < (int)cls.size(); ++j)
			{
				double d = (old_pts[i].x() - cls[j].center.x()) * (old_pts[i].x() - cls[j].center.x());
				d += (old_pts[i].y() - cls[j].center.y()) * (old_pts[i].y() - cls[j].center.y());
				d = xtl_sqrt(d);

				if (min_d == -1 || d < min_d)
				{
					min_d = d;
					min_j = j;
				}
			}

			// rank
			cls[min_j].pts.push_back(old_pts[i]);

			// update region
			cls[min_j].region.left(xtl_min(old_pts[i].x(), cls[min_j].region.left()));
			cls[min_j].region.right(xtl_max(old_pts[i].x(), cls[min_j].region.right()));
			cls[min_j].region.top(xtl_min(old_pts[i].y(), cls[min_j].region.top()));
			cls[min_j].region.bottom(xtl_max(old_pts[i].y(), cls[min_j].region.bottom()));

			// center sum
			cls[min_j].reserve1.x(cls[min_j].reserve1.x() + old_pts[i].x());
			cls[min_j].reserve1.y(cls[min_j].reserve1.y() + old_pts[i].y());

			// the distance sum
			ds += min_d;
		}

		if (min_ds == -1 || ds < min_ds)
		{
			min_ods = min_ds;
			min_ds = ds;
		}

		// update cluster center
		for (i = 0; i < (int)cls.size(); ++i)
		{
			if (cls[i].pts.is_empty()) continue;

			cls[i].center.x(cls[i].reserve1.x() / cls[i].pts.size());
			cls[i].center.y(cls[i].reserve1.y() / cls[i].pts.size());
		}

		if (fabs(min_ds - min_ods) > 0.000001)
		{
			cls[i].pts.clear();
			cls[i].region = rect_type(0, 0, 0, 0);
			cls[i].reserve1 = point_type(0, 0);
		}
		else break;

		if (++n > 50)
		{
			break;
		}
	}
	return cls;
}

inline classes_type sh_cs_fcm(points_type const& old_pts, int k, int m = 3)
{
	if (old_pts.is_empty()) return classes_type();

	int i, j;
	// initialize cluster points
	classes_type cls(k);
	for (i = 0; i < (int)cls.size(); ++i)
	{
		cls[i].center = old_pts[rand() % old_pts.size()];
		cls[i].region = rect_type(0, 0, 0, 0);
		cls[i].reserve1 = point_type(0, 0);
	}

	// initialize membership function u[i][j]
	basic_matrix<double> u(cls.size(), old_pts.size());
	for (i = 0; i < (int)cls.size(); ++i)
		for (j = 0; j < (int)old_pts.size(); ++j)
			u.at(i, j) = 1.0f / (cls.size() * old_pts.size());

	int n = 0;
	while (1)
	{
		// calculate object function min y = ...
		// and update membership function u[i][j]
		double y = 0;
		for (j = 0; j < (int)old_pts.size(); ++j)
		{
			double sum = 0;
			for (i = 0; i < (int)cls.size(); ++i)
			{
				double p = xtl_pow(u.at(i, j), m);
				double d = (old_pts[j].x() - cls[i].center.x()) * (old_pts[j].x() - cls[i].center.x());
				d += (old_pts[j].y() - cls[i].center.y()) * (old_pts[j].y() - cls[i].center.y());
				y += p * d;

				if (d == 0) u.at(i, j) = 1;
				else u.at(i, j) = xtl_pow((1.0f / d), 1.0f / (m - 1));
				sum += u.at(i, j);
			}
			for (i = 0; i < (int)cls.size(); ++i)
			{
				u.at(i, j) /= sum;
			}
		}

		// update center
		for (i = 0; i < (int)cls.size(); ++i)
		{
			double top_x = 0, top_y = 0;
			double btm = 0;
			for (j = 0; j < (int)old_pts.size(); ++j)
			{
				double a = xtl_pow(u.at(i, j), m);
				top_x += a * old_pts[j].x();
				top_y += a * old_pts[j].y();
				btm += a;
			}

			cls[i].center.x(int(top_x / btm));
			cls[i].center.y(int(top_y / btm));
		}
		if (n++ > 50)
		{
			break;
		}
	}

	for (i = 0; i < (int)old_pts.size(); ++i)
	{
		// find cluster point for the minmum distance between old_pts[i] and it
		/*double min_d = -1;
		int min_j = 0;
		for (j = 0; j < (int)cls.size(); ++j)
		{
			double d = (old_pts[i].x() - cls[j].center.x()) * (old_pts[i].x() - cls[j].center.x());
			d += (old_pts[i].y() - cls[j].center.y()) * (old_pts[i].y() - cls[j].center.y());
			d = xtl_sqrt(d);

			if (min_d == -1 || d < min_d)
			{
				min_d = d;
				min_j = j;
			}
		}

		// rank
		cls[min_j].pts.push_back(old_pts[i]);

		// update region
		cls[min_j].region.left(xtl_min(old_pts[i].x(), cls[min_j].region.left()));
		cls[min_j].region.right(xtl_max(old_pts[i].x(), cls[min_j].region.right()));
		cls[min_j].region.top(xtl_min(old_pts[i].y(), cls[min_j].region.top()));
		cls[min_j].region.bottom(xtl_max(old_pts[i].y(), cls[min_j].region.bottom()));*/

		double max_u = 0;
		int max_j = 0;
		for (j = 0; j < (int)cls.size(); ++j)
		{
			if (u.at(j, i) > max_u)
			{
				max_u = u.at(j, i);
				max_j = j;
			}
		}

		// rank
		cls[max_j].pts.push_back(old_pts[i]);

		// update region
		cls[max_j].region.left(xtl_min(old_pts[i].x(), cls[max_j].region.left()));
		cls[max_j].region.right(xtl_max(old_pts[i].x(), cls[max_j].region.right()));
		cls[max_j].region.top(xtl_min(old_pts[i].y(), cls[max_j].region.top()));
		cls[max_j].region.bottom(xtl_max(old_pts[i].y(), cls[max_j].region.bottom()));
	}

	return cls;

}
inline image_type sh_cs_kmean_splited_image(image_type const& old_img)
{
	if (old_img.is_empty()) return old_img;

	points_type pts;
	for (int px = 0; px < (int)old_img.width(); ++px)
		for (int py = 0; py < (int)old_img.height(); ++py)
			if (old_img.at(px, py).is_black()) pts.push_back(point_type(px, py));

	classes_type cls(sh_cs_kmean(pts, 50));
	if (cls.is_empty()) return old_img;

	image_type new_img(old_img);
	for (int i = 0; i < (int)cls.size(); ++i)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		for (int j = 0; j < (int)cls[i].pts.size(); ++j)
		{
			new_img.at(cls[i].pts[j].x(), cls[i].pts[j].y()).red(r);
			new_img.at(cls[i].pts[j].x(), cls[i].pts[j].y()).green(g);
			new_img.at(cls[i].pts[j].x(), cls[i].pts[j].y()).blue(b);
		}
	}

	return new_img;
}

inline image_type sh_cs_fcm_splited_image(image_type const& old_img)
{
	if (old_img.is_empty()) return old_img;

	points_type pts;
	for (int px = 0; px < (int)old_img.width(); ++px)
		for (int py = 0; py < (int)old_img.height(); ++py)
			if (old_img.at(px, py).is_black()) pts.push_back(point_type(px, py));

	//classes_type cls(sh_cs_kmean(pts, 50));
	classes_type cls(sh_cs_fcm(pts, 50));
	if (cls.is_empty()) return old_img;

	image_type new_img(old_img);
	for (int i = 0; i < (int)cls.size(); ++i)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		for (int j = 0; j < (int)cls[i].pts.size(); ++j)
		{
			new_img.at(cls[i].pts[j].x(), cls[i].pts[j].y()).red(r);
			new_img.at(cls[i].pts[j].x(), cls[i].pts[j].y()).green(g);
			new_img.at(cls[i].pts[j].x(), cls[i].pts[j].y()).blue(b);
		}
	}

	return new_img;
}

#endif // SH_CS_H
