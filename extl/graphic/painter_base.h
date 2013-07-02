/* ///////////////////////////////////////////////////////////////////////
 * File:		painter_base.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The painter_base class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_PAINTER_BASE_H
#define EXTL_GRAPHIC_PAINTER_BASE_H

/*!\file painter_base.h
 * \brief painter_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "basic_rect.h"
#include "basic_color.h"
#include "basic_point.h"
#include "basic_size.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief painter_base
 *
 * \param Dev the derived type
 * \param Img the image type
 *
 * \ingroup extl_group_graphic
 */

template<	typename_param_k Dev
		,	typename_param_k Img
		>
class painter_base
{
	/// \name Types
	/// @{
	public:
		typedef Dev										derived_type;
		typedef painter_base							class_type;
		typedef Img										image_type;
		typedef typename_type_k image_type::bool_type	bool_type;
		typedef typename_type_k image_type::color_type	color_type;
		typedef typename_type_k color_type::rgba_type	rgba_type;
		typedef e_int_t									int_type;
		typedef e_float_t								float_type;
		typedef basic_rect<int_type>					rect_type;
		typedef basic_point<int_type>					point_type;
		typedef basic_size<int_type>					size_type;
		typedef basic_rect<float_type>					frect_type;
		typedef basic_point<float_type>					fpoint_type;
		typedef basic_size<float_type>					fsize_type;
	/// @}

	/// \name Members
	/// @{
	private:
		rect_type										m_canvas;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k painter_base(rect_type const& canvas)
			: m_canvas(canvas)
		{
		}
	/// @}

	/// \name Interfaces
	/// \note not use canvas
	/// @{
	public:
		void				do_pixel(int_type /*x*/, int_type /*y*/, color_type const& /*c*/){}
		color_type const	do_pixel(int_type /*x*/, int_type /*y*/) const {}
	/// @}

	/// \name Methods - use canvas
	/// @{
	public:
		void				pixel(int_type x, int_type y, color_type const& c);
		color_type const	pixel(int_type x, int_type y) const;

		/// draw image
		void				draw_image(image_type const& image)	{ draw_image(0, 0, image);	}
		void				draw_image(int_type x, int_type y, image_type const& image);
	/// @}

	/// \name Attributes
	/// @{
	public:
		rect_type&				canvas()		{ return m_canvas;	}
		rect_type const&		canvas() const	{ return m_canvas;	}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		derived_type&			derive()		{ return static_cast<derived_type&>(*this);			}
		derived_type const&		derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */
// Template declaration 
#ifdef EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL
#	undef EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL
#endif

#define EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL			\
template<	typename_param_k Dev						\
		,	typename_param_k Img						\
		>

// Class qualification 
#ifdef EXTL_GRAPHIC_PAINTER_BASE_QUAL
#	undef EXTL_GRAPHIC_PAINTER_BASE_QUAL
#endif

#define EXTL_GRAPHIC_PAINTER_BASE_QUAL	painter_base<Dev, Img>

// Class qualification 
#ifdef EXTL_GRAPHIC_PAINTER_BASE_RET_QUAL
#	undef EXTL_GRAPHIC_PAINTER_BASE_RET_QUAL
#endif

#define EXTL_GRAPHIC_PAINTER_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_GRAPHIC_PAINTER_BASE_QUAL::ret_type	\
					EXTL_GRAPHIC_PAINTER_BASE_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL
inline void EXTL_GRAPHIC_PAINTER_BASE_QUAL::pixel(int_type x, int_type y, color_type const& c)
{
	int_type new_x = canvas().left() + x;
	int_type new_y = canvas().top() + y;
	EXTL_ASSERT(canvas().contains(new_x, new_y));

	if (canvas().contains(new_x, new_y))
		derive().do_pixel(new_x, new_y, c);
}

EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL
inline EXTL_GRAPHIC_PAINTER_BASE_RET_QUAL(color_type const)::pixel(int_type x, int_type y) const
{
	int_type new_x = canvas().left() + x;
	int_type new_y = canvas().top() + y;
	EXTL_ASSERT(canvas().contains(new_x, new_y));

	if (canvas().contains(new_x, new_y))
		return derive().do_pixel(new_x, new_y);
	return color_type();
}

EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL
inline void EXTL_GRAPHIC_PAINTER_BASE_QUAL::draw_image(int_type x, int_type y, image_type const& image)
{
	rect_type rect = canvas().make_intersection(canvas().left() + x, canvas().top() + y, image.width(), image.height());
	if (rect.is_empty()) return ;

	// only draws intersection of canvas and image
	for (int_type px = rect.left(); px < rect.right(); ++px)
	{
		for (int_type py = rect.top(); py < rect.bottom(); ++py)
		{
			derive().do_pixel(px, py, image.at(px - x, py - y));
		}
	}
}
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_GRAPHIC_PAINTER_BASE_TEMPLATE_DECL
#undef EXTL_GRAPHIC_PAINTER_BASE_QUAL
#undef EXTL_GRAPHIC_PAINTER_BASE_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_PAINTER_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
