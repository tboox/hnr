/* ///////////////////////////////////////////////////////////////////////
 * File:		nearest_neighbor_zoom_filter.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The nearest_neighbor_zoom_filter class - zoom in & zoom out
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_IMAGE_NEAREST_NEIGHBOR_ZOOM_FILTER_H
#define EXTL_GRAPHIC_IMAGE_NEAREST_NEIGHBOR_ZOOM_FILTER_H

/*!\file nearest_neighbor_zoom_filter.h
 * \brief nearest_neighbor_zoom_filter class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief nearest_neighbor_zoom_filter
 *
 * \param sPainter the source painter
 * \param dPainter the destination painter
 *
 * <pre>
 *
 * src:
 * 1 0
 * 0 0
 *
 * dst:
 * 1 1 0
 * 1 1 0
 * 0 0 0
 *
 * </pre>
 *
 * \ingroup extl_group_graphic
 */
template<	typename_param_k sPainter
		,	typename_param_k dPainter
		>
class nearest_neighbor_zoom_filter
{
	/// \name Types
	/// @{
	public:
		typedef nearest_neighbor_zoom_filter					class_type;
		typedef	dPainter										dpainter_type;
		typedef	sPainter										spainter_type;
		typedef typename_type_k spainter_type::bool_type		bool_type;
		typedef typename_type_k spainter_type::color_type		color_type;
		typedef typename_type_k color_type::rgba_type			rgba_type;
		typedef typename_type_k spainter_type::int_type			int_type;
		typedef typename_type_k spainter_type::float_type		float_type; 
		typedef typename_type_k spainter_type::rect_type		rect_type;
		typedef typename_type_k spainter_type::size_type		size_type;
		typedef typename_type_k spainter_type::point_type		point_type;
		typedef typename_type_k spainter_type::frect_type		frect_type;
		typedef typename_type_k spainter_type::fsize_type		fsize_type;
		typedef typename_type_k spainter_type::fpoint_type		fpoint_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		void filter(spainter_type const& spainter, dpainter_type& dpainter)
		{
			rect_type const& scanvas = spainter.canvas();
			rect_type const& dcanvas = dpainter.canvas();

			// calculate scale factor
			float_type fh = static_cast<float_type>(dcanvas.height()) / scanvas.height();
			float_type fw = static_cast<float_type>(dcanvas.width()) / scanvas.width();
			
			// the fill size
			int_type part_w = static_cast<int_type>(fw + 1);
			int_type part_h = static_cast<int_type>(fh + 1);

			int_type px, py;
			// clear
			for (px = dcanvas.left(); px <= dcanvas.right(); ++px)
				for (py = dcanvas.top(); py <= dcanvas.bottom(); ++py)
					dpainter.do_pixel(px, py, color_type());

			// interpolation
			for (px = scanvas.left(); px <= scanvas.right(); ++px)
			{
				for (py = scanvas.top(); py <= scanvas.bottom(); ++py)
				{
					// part_rect[part_h][part_w]
					for (int_type k = 0; k < part_w * part_h; ++k)
					{
						int_type new_x = static_cast<int_type>(px * fw + k % part_w);
						new_x = new_x <= dcanvas.right()? new_x : dcanvas.right();

						int_type new_y = static_cast<int_type>(py * fh + k / part_w);
						new_y = new_y <= dcanvas.bottom()? new_y : dcanvas.bottom();

						// fill nearest neighbor pixel
						dpainter.do_pixel(new_x, new_y, spainter.do_pixel(px, py));
					}
				}
			}
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_IMAGE_NEAREST_NEIGHBOR_ZOOM_FILTER_H */
/* //////////////////////////////////////////////////////////////////// */
