/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_rect.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The basic_rect class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_BASIC_RECT_H
#define EXTL_GRAPHIC_BASIC_RECT_H

/*!\file basic_rect.h
 * \brief basic_rect class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "basic_point.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief basic_rect
 *
 * \param Val the value type
 *
 * \code
 *
 * basic_rect<int> r(0, 0, 2, 2);
 *
 * or
 *
 * basic_rect<int> r;
 * r.top(0);
 * r.left(0);
 * r.bottom(1);
 * r.right(1);
 *
 * or
 *
 * basic_rect<int> r;
 * r.top(0);
 * r.left(0);
 * r.height(2);
 * r.width(2);
 *
 * \endcode
 *
 * \ingroup extl_group_graphic
 */

template<typename_param_k Val>
class basic_rect
{
	/// \name Types
	/// @{
	public:
		typedef basic_rect					class_type;
		typedef	Val							value_type;
		typedef value_type&					reference;
		typedef value_type const&			const_reference;
		typedef value_type*					pointer;
		typedef value_type const*			const_pointer;
		typedef e_bool_t					bool_type;
	/// @}

	/// \name Members
	/// @{
	private:
		value_type							m_left;
		value_type							m_top;
		value_type							m_width;
		value_type							m_height;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k basic_rect	(	const_reference left = value_type()
								,	const_reference top = value_type()
								,	const_reference w = value_type()
								,	const_reference h = value_type()
								)
			: m_left(left)
			, m_top(top)
			, m_width(w)
			, m_height(h)
		{
		}
		basic_rect(class_type const& rhs)
			: m_left(rhs.m_left)
			, m_top(rhs.m_top)
			, m_width(rhs.m_width)
			, m_height(rhs.m_height)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		value_type const	top() const						{ return m_top;		}
		void				top(const_reference val)		{ m_top = val;		}

		value_type const	bottom() const					{ return (top() + height() - 1);	}
		void				bottom(const_reference val)		{ height(val + 1 - top());			}

		value_type const	left() const					{ return m_left;	}
		void				left(const_reference val)		{ m_left = val;		}

		value_type const	right() const					{ return (left() + width() - 1);	}
		void				right(const_reference val)		{ width(val + 1 - left());			}

		value_type const	height() const					{ return m_height;	}
		void				height(const_reference val)		{ m_height = val;	}
	
		value_type const	width() const					{ return m_width;	}
		void				width(const_reference val)		{ m_width = val;	}
	
		bool_type			contains(const_reference x, const_reference y, const_reference w, const_reference h) const;
		bool_type			contains(class_type const& rhs) const					{ return contains(rhs.left(), rhs.top(), rhs.width(), rhs.height());	}
		bool_type			contains(const_reference x, const_reference y) const	{ return contains(x, y, 1, 1);											}
		
		bool_type			intersects(const_reference x, const_reference y, const_reference w, const_reference h) const;
		bool_type			intersects(class_type const& rhs) const					{ return contains(rhs.left(), rhs.top(), rhs.width(), rhs.height());	}
		bool_type			intersects(const_reference x, const_reference y) const	{ return contains(x, y, 1, 1);											}
	
		class_type			make_intersection(const_reference x, const_reference y, const_reference w, const_reference h) const;
		class_type			make_intersection(class_type const& rhs) const			{ return make_intersection(rhs.left(), rhs.top(), rhs.width(), rhs.height());	}
	
		bool_type			is_empty() const	{ return (0 == width()) && (0 == height());	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void				swap(class_type& rhs)			{ std_swap(m_top, rhs.m_top); std_swap(m_left, rhs.m_left); std_swap(m_width, rhs.m_width); std_swap(m_height, rhs.m_height);	}
		void				clear()							{ top(value_type()); left(value_type()); width(value_type()); height(value_type());}
	/// @}

	/// \name Operators
	/// @{
	public:
		bool_type			operator ==(class_type const& rhs) const	{ return (top() == rhs.top()) && (height() == rhs.height()) && (left() == rhs.left()) && (width() == rhs.width());		}
		bool_type			operator !=(class_type const& rhs) const	{ return !((*this) == rhs);	}	
	/// @}

};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */

template<typename_param_k Val>
typename_type_ret_k basic_rect<Val>::
bool_type basic_rect<Val>::contains(const_reference x, const_reference y, const_reference w, const_reference h) const
{
	return	(	!(left() > x) 
			&&	!(top() > y) 
			&&	!(right() < (x + w - 1))
			&&	!(bottom() < (y + h - 1))
			);
}

template<typename_param_k Val>
typename_type_ret_k basic_rect<Val>::
bool_type basic_rect<Val>::intersects(const_reference x, const_reference y, const_reference w, const_reference h) const
{
	return	!(	(right() < x)
			&&	(bottom() < y)
			&&	(left() > (x + w - 1)) 
			&&	(top() > (y + h - 1))
			);

}

template<typename_param_k Val>
typename_type_ret_k basic_rect<Val>::
class_type basic_rect<Val>::make_intersection(const_reference x, const_reference y, const_reference w, const_reference h) const
{
	if (intersects(x, y, w, h))
	{
		class_type rect;
		rect.left(xtl_max(x, left()));
		rect.top(xtl_max(y, top()));
		rect.right(xtl_min(x + w - 1, right()));
		rect.bottom(xtl_min(y + h - 1, bottom()));
		return rect;
	}
	
	return class_type();
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_BASIC_RECT_H */
/* //////////////////////////////////////////////////////////////////// */
