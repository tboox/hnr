/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_size.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The basic_size class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_BASIC_SIZE_H
#define EXTL_GRAPHIC_BASIC_SIZE_H

/*!\file basic_size.h
 * \brief basic_size class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief basic_size
 *
 * \param Val the value type
 *
 * \ingroup extl_group_graphic
 */

template<typename_param_k Val>
class basic_size
{
	/// \name Types
	/// @{
	public:
		typedef basic_size					class_type;
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
		value_type							m_width;
		value_type							m_height;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k basic_size	(	const_reference width = value_type()
								,	const_reference height = value_type()
								)
			: m_width(width)
			, m_height(height)
		{
		}
		basic_size(class_type const& rhs)
			: m_width(rhs.m_width)
			, m_height(rhs.m_height)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		value_type const	height() const					{ return m_width;	}
		void				height(const_reference val)		{ m_width = val;	}
	
		value_type const	width() const					{ return m_height;	}
		void				width(const_reference val)		{ m_height = val;	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void				swap(class_type& rhs)			{ std_swap(m_width, rhs.m_width); std_swap(m_height, rhs.m_height);	}
		void				clear()							{ width(value_type()); height(value_type()); }
	/// @}

	/// \name Operators
	/// @{
	public:
		bool_type			operator ==(class_type const& rhs) const	{ return ((width() == rhs.width()) && (height() == rhs.height()));	}
		bool_type			operator !=(class_type const& rhs) const	{ return !((*this) == rhs);	}	
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_BASIC_SIZE_H */
/* //////////////////////////////////////////////////////////////////// */
