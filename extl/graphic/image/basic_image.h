/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_image.h		
 *
 * Created:		08.12.31	
 * Updated:		08.12.31
 *
 * Brief:		The basic_image class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_GRAPHIC_IMAGE_BASIC_IMAGE_H
#define EXTL_GRAPHIC_IMAGE_BASIC_IMAGE_H

/*!\file basic_image.h
 * \brief basic_image class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../container/matrix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_BEGIN_WHOLE_NAMESPACE

/*!brief basic_image
 *
 * \ingroup extl_group_graphic
 */
class basic_image
{
	/// \name Types
	/// @{
	public:
		typedef basic_image										class_type;
		typedef	matrix_selector<basic_color>::matrix_type		matrix_type;
		typedef matrix_type::value_type							value_type;
		typedef matrix_type::reference							reference;
		typedef matrix_type::const_reference					const_reference;
		typedef matrix_type::pointer							pointer;
		typedef matrix_type::const_pointer						const_pointer;
		typedef matrix_type::bool_type							bool_type;
		typedef value_type										color_type;
		typedef e_int_t											int_type;	
		typedef basic_size<int_type>							size_type;
	/// @}

	/// \name Members
	/// @{
	private:
		matrix_type												m_matrix;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_image(class_type const& rhs)
			: m_matrix(rhs.matrix())
		{
		}
		explicit_k basic_image(int_type width = 0, int_type height = 0, const_reference value = value_type())
			: m_matrix(value, height, width)
		{
		}
		explicit_k basic_image(size_type size, const_reference value = value_type())
			: m_matrix(value, size.height(), size.width())
		{
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		const_reference		at(int_type x, int_type y) const	{ return matrix().at(y, x);	}
		reference			at(int_type x, int_type y)			{ return matrix().at(y, x);	}
	
		int_type			height() const	{ return matrix().row();	}
		int_type			width() const	{ return matrix().col();	}

		size_type			size() const		{ return size_type(width(), height());	}
		bool_type			is_empty() const	{ return (0 == size().width()) && (0 == size().height());	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void				swap(class_type& rhs)			{ matrix().swap(rhs.m_matrix);	}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		matrix_type const&	matrix() const					{ return m_matrix;		}
		matrix_type&		matrix()						{ return m_matrix;		}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::graphic namespace 
 */
EXTL_GRAPHIC_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_GRAPHIC_IMAGE_BASIC_IMAGE_H */
/* //////////////////////////////////////////////////////////////////// */
