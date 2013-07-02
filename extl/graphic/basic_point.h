/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_point.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The basic_point class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_BASIC_POINT_H
#define EXTL_GRAPHIC_BASIC_POINT_H

/*!\file basic_point.h
 * \brief basic_point class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief basic_point
 *
 * \param Val the value type
 *
 * \ingroup extl_group_graphic
 */

template<typename_param_k Val>
class basic_point
{
	/// \name Types
	/// @{
	public:
		typedef basic_point					class_type;
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
		value_type							m_x;
		value_type							m_y;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k basic_point	(	const_reference x = value_type()
								,	const_reference y = value_type()
								)
			: m_x(x)
			, m_y(y)
		{
		}
		basic_point(class_type const& rhs)
			: m_x(rhs.m_x)
			, m_y(rhs.m_y)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		value_type const	x() const					{ return m_x;		}
		void				x(const_reference val)		{ m_x = val;		}

		value_type const	y() const					{ return m_y;	}
		void				y(const_reference val)		{ m_y = val;	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void				swap(class_type& rhs)			{ std_swap(m_x, rhs.m_x); std_swap(m_y, rhs.m_y);	}
		void				clear()							{ x(value_type()); y(value_type());					}
	/// @}

	/// \name Operators
	/// @{
	public:
		bool_type			operator ==(class_type const& rhs) const	{ return ((x() == rhs.x()) && (y() == rhs.y()));		}
		bool_type			operator !=(class_type const& rhs) const	{ return !((*this) == rhs);	}	
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_BASIC_POINT_H */
/* //////////////////////////////////////////////////////////////////// */
