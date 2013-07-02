/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_array.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.07
 *
 * Brief: basic_array class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_ARRAY_H
#define EXTL_CONTAINER_BASIC_ARRAY_H

/*!\file basic_array.h
 * \brief basic_array class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "array_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: basic_array class
 *
 * \param T The element type
 * \param B The buffer type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k B = typename_type_def_k buffer_selector<T>::buffer_type 
#else
		,	typename_param_k B
#endif
		>
class basic_array
	: public array_base<	basic_array<T, B>
						,	B
						>
{
	private:
		typedef array_base	<	basic_array<T, B>
							,	B
							>														base_type;

	/// \name Types
	/// @{
	public:
		typedef basic_array															class_type;
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
		basic_array()
			: base_type()
		{
		}
		basic_array(class_type const& rhs)
			: base_type(rhs)
		{
		}
		basic_array(const_pointer ar, size_type n)
			: base_type(ar, n)
		{
		}
		basic_array(const_reference value, size_type n)
			: base_type(value, n)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& ar)		{ return base_type::operator=(ar);		}
		class_type& operator=(const_reference value)	{ return base_type::operator=(value);	}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_BASIC_ARRAY_H */
/* //////////////////////////////////////////////////////////////////// */
