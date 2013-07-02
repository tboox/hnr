/* ///////////////////////////////////////////////////////////////////////
 * File:		image_painter.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The image_painter class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_IMAGE_PAINTER_H
#define EXTL_GRAPHIC_IMAGE_PAINTER_H

/*!\file image_painter.h
 * \brief image_painter class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../painter_base.h"
#include "basic_image.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief image_painter
 *
 * \param Img the image type
 *
 * \ingroup extl_group_graphic
 */
template<typename_param_k Img>
class image_painter
	: public painter_base<image_painter<Img>, Img>
{
	/// \name Types
	/// @{
	public:
		typedef painter_base<image_painter<Img>, Img>		base_type;
		typedef image_painter								class_type;
		typedef typename_type_k base_type::image_type		image_type;
		typedef typename_type_k base_type::bool_type		bool_type;
		typedef typename_type_k base_type::color_type		color_type;
		typedef typename_type_k color_type::rgba_type		rgba_type;
		typedef typename_type_k base_type::int_type			int_type;
		typedef typename_type_k base_type::rect_type		rect_type;
		typedef typename_type_k base_type::size_type		size_type;
		typedef typename_type_k base_type::point_type		point_type;
		typedef typename_type_k base_type::frect_type		frect_type;
		typedef typename_type_k base_type::fsize_type		fsize_type;
		typedef typename_type_k base_type::fpoint_type		fpoint_type;
	/// @}

	/// \name Members
	/// @{
	private:
		image_type&											m_image;
	/// @}

	/// \name Constructors
	/// @{
	public:
		image_painter(image_type& image)
			: base_type(rect_type(0, 0, image.width(), image.height()))
			, m_image(image)
		{}
	/// @}

	/// \name Attributes
	/// @{
	public:
		image_type&				image()			{ return m_image;									}
		image_type const&		image()	const	{ return static_cast<image_type const&>(m_image);	}
	/// @}

	/// \name Methods
	/// @{
	public:
		void				do_pixel(int_type x, int_type y, color_type const& color)
		{
			EXTL_ASSERT(x >= 0 && y >= 0);
			image().at(x, y) = color;
		}
		color_type const	do_pixel(int_type x, int_type y) const
		{
			EXTL_ASSERT(x >= 0 && y >= 0);
			return image().at(x, y);
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_IMAGE_PAINTER_H */
/* //////////////////////////////////////////////////////////////////// */
