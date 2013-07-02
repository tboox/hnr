/* ///////////////////////////////////////////////////////////////////////
 * File:		zoom_filter.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The zoom_filter class - zoom in & zoom out
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_IMAGE_ZOOM_FILTER_H
#define EXTL_GRAPHIC_IMAGE_ZOOM_FILTER_H

/*!\file zoom_filter.h
 * \brief zoom_filter class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief zoom_filter
 *
 * \ingroup extl_group_graphic
 */
template<	typename_param_k DstPainter
		,	typename_param_k SrcPainter
		>
class zoom_filter
{
	/// \name Types
	/// @{
	public:
		typedef zoom_filter										class_type;
		typedef	DstPainter										dst_painter_type;
		typedef	SrcPainter										src_painter_type;
		typedef typename_type_k src_painter_type::size_type		size_type;
		typedef typename_type_k src_painter_type::bool_type		bool_type;
		typedef typename_type_k src_painter_type::color_type	color_type;
		typedef typename_type_k color_type::rgba_type			rgba_type;
		typedef typename_type_k src_painter_type::index_type	index_type;
		typedef typename_type_k src_painter_type::int_type		int_type;
		typedef typename_type_k src_painter_type::rect_type		rect_type;
	/// @}

	/// \name Members
	/// @{
	private:
	/// @}

	/// \name Constructors
	/// @{
	public:
	/// @}

	/// \name Methods
	/// @{
	public:
		void operator()(dst_painter_type& dst_painter, src_painter_type const& src_painter)
		{
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_IMAGE_ZOOM_FILTER_H */
/* //////////////////////////////////////////////////////////////////// */
