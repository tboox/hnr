/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_matrix.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.21
 *
 * Brief:		basic_matrix class - for compact matrix
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_MATRIX_H
#define EXTL_CONTAINER_BASIC_MATRIX_H

/*!\file basic_matrix.h
 * \brief basic_matrix class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "matrix_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: basic_matrix class
 *
 * \param Val The element type
 * \param Buf The buffer type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k Val
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k Buf = typename_type_def_k buffer_selector<Val>::buffer_type 
#else
		,	typename_param_k Buf	
#endif
		>
class basic_matrix
	: public matrix_base	<	basic_matrix<Val, Buf>
							,	Buf
							>
{
	private:
		typedef matrix_base	<	basic_matrix<Val, Buf>
							,	Buf
							>														base_type;

	/// \name Types
	/// @{
	public:
		typedef basic_matrix														class_type;
		typedef typename_type_k base_type::buffer_type								buffer_type;
		typedef typename_type_k base_type::allocator_type							allocator_type;
		typedef typename_type_k base_type::value_type								value_type;
		typedef typename_type_k base_type::pointer									pointer;
		typedef typename_type_k base_type::const_pointer							const_pointer;
		typedef typename_type_k base_type::reference								reference;
		typedef typename_type_k base_type::const_reference							const_reference;
		typedef typename_type_k base_type::iterator									iterator;
		typedef typename_type_k base_type::const_iterator							const_iterator;
		typedef typename_type_k base_type::reverse_iterator							reverse_iterator;
		typedef typename_type_k base_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::difference_type							difference_type;
		typedef	typename_type_k base_type::int_type									int_type;	
		typedef typename_type_k base_type::index_type								index_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_matrix()
			: base_type()
		{
		}
		basic_matrix(class_type const& rhs)
			: base_type(rhs)
		{
		}
		basic_matrix(index_type d0, index_type d1)
			: base_type(d0, d1)
		{
		}
		basic_matrix(const_reference value, index_type d0, index_type d1)
			: base_type(value, d0, d1)
		{
		}
		basic_matrix(const_pointer p, index_type d0, index_type d1)
			: base_type(p, d0, d1)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& rhs)	{ return base_type::operator=(rhs);		}
		class_type& operator=(const_reference value)	{ return base_type::operator=(value);	}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_BASIC_MATRIX_H */
/* //////////////////////////////////////////////////////////////////// */
