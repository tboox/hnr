/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_color.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The basic_color class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_BASIC_COLOR_H
#define EXTL_GRAPHIC_BASIC_COLOR_H

/*!\file basic_color.h
 * \brief basic_color class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
// make rgba
#define EXTL_RGBA(r, g, b, a)	((r << 24) | (g << 16) | (b << 8) | (a))
#define EXTL_RGB(r, g, b)		(EXTL_RGBA(r, g, b, 0))

// get rgba components 
#define EXTL_RGBA_GETR(rgba)	((rgba >> 24) & 0x000000FF)
#define EXTL_RGBA_GETG(rgba)	((rgba >> 16) & 0x000000FF)
#define EXTL_RGBA_GETB(rgba)	((rgba >> 8) & 0x000000FF)
#define EXTL_RGBA_GETA(rgba)	((rgba) & 0x000000FF)

// set rgba components 
#define EXTL_RGBA_SETR(rgba, r)	do{ rgba &= 0x00FFFFFF; rgba |= ((r << 24) & 0xFF000000); }while (0)
#define EXTL_RGBA_SETG(rgba, g)	do{ rgba &= 0xFF00FFFF; rgba |= ((g << 16) & 0x00FF0000); }while (0)
#define EXTL_RGBA_SETB(rgba, b)	do{ rgba &= 0xFFFF00FF; rgba |= ((b << 8) & 0x0000FF00); }while (0)
#define EXTL_RGBA_SETA(rgba, a)	do{ rgba &= 0xFFFFFF00; rgba |= ((a) & 0x000000FF); }while (0)

// rgba constants
#define EXTL_RGBA_BLACK			EXTL_RGB(0, 0, 0)
#define EXTL_RGBA_WHITE			EXTL_RGB(255, 255, 255)
#define EXTL_RGBA_RED			EXTL_RGB(255, 0, 0)
#define EXTL_RGBA_GREEN			EXTL_RGB(0, 255, 0)
#define EXTL_RGBA_BLUE			EXTL_RGB(0, 0, 255)
#define EXTL_RGBA_YELLOW		EXTL_RGB(255, 255, 0)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief basic_color
 *
 * \ingroup extl_group_graphic
 */
class basic_color
{
	/// \name Types
	/// @{
	public:
		typedef basic_color						class_type;
		typedef e_uint32_t						rgba_type;
		typedef e_int_t							int_type;
		typedef int_type						value_type;
		typedef value_type&						reference;
		typedef value_type const&				const_reference;
		typedef e_bool_t						bool_type;
	/// @}


	/// \name Members
	/// @{
	private:
		/// 32bit: r g b a
		rgba_type								m_rgba;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k basic_color(rgba_type const& c = rgba_type())
			: m_rgba(c)
		{
		}
		basic_color	(	const_reference r
					,	const_reference g
					,	const_reference b
					,	const_reference a = value_type()
					)
			: m_rgba(EXTL_RGBA(r, g, b, a))
		{
		}
		basic_color(class_type const& rhs)
			: m_rgba(rhs.rgba())
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		value_type const	red() const					{ return EXTL_RGBA_GETR(rgba());	}
		void				red(const_reference val)	{ EXTL_RGBA_SETR(m_rgba, val);		}

		value_type const	green() const				{ return EXTL_RGBA_GETG(rgba());	}
		void				green(const_reference val)	{ EXTL_RGBA_SETG(m_rgba, val);		}

		value_type const	blue() const				{ return EXTL_RGBA_GETB(rgba());	}
		void				blue(const_reference val)	{ EXTL_RGBA_SETB(m_rgba, val);		}

		value_type const	alpha() const				{ return EXTL_RGBA_GETA(rgba());	}
		void				alpha(const_reference val)	{ EXTL_RGBA_SETA(m_rgba, val);		}

		value_type const	gray() const				{ return ((red() + green() + blue()) / 3);		}
		void				gray(const_reference val)	{ red(val); green(val); blue(val);				}

		bool_type const		is_black() const			{ return (m_rgba == EXTL_RGBA_BLACK);				}
		void				is_black(bool_type b)		{ b? rgba(EXTL_RGBA_BLACK) : rgba(EXTL_RGBA_WHITE);	}

		rgba_type const		rgba() const				{ return m_rgba;	}
		void				rgba(rgba_type const& val)	{ m_rgba = val;		}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void				swap(class_type& rhs)		{ std_swap(m_rgba, rhs.m_rgba);	}
		void				clear()						{ rgba(rgba_type());			}
	/// @}

	/// \name Operators
	/// @{
	public:
		bool_type			operator ==(class_type const& rhs) const	{ return (rgba() == rhs.rgba());	}
		bool_type			operator ==(rgba_type const& rhs) const		{ return (rgba() == rhs);			}

		bool_type			operator !=(class_type const& rhs) const	{ return !((*this) == rhs);			}	
		bool_type			operator !=(rgba_type const& rhs) const		{ return (rgba() != rhs);			}	
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_BASIC_COLOR_H */
/* //////////////////////////////////////////////////////////////////// */
