/* ///////////////////////////////////////////////////////////////////////
 * File:		object_initialiser.h		
 *
 * Created:		08.07.30				
 * Updated:		08.07.30
 *
 * Brief: object_initialiser class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_OBJECT_INITIALISER_H
#define EXTL_MEMORY_OBJECT_INITIALISER_H

/*!\file object_initialiser.h
 * \brief object_initialiser class
 */
#ifndef __cplusplus
#	error object_initialiser.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "initialiser_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief object_initialiser class
 *
 * \param T The value type
 * 
 * \ingroup extl_group_memory
 */
template<typename_param_k T>
class object_initialiser
	: public initialiser_base<object_initialiser<T>, T>
{
	/// \name Types
	/// @{
	public:
		typedef initialiser_base<object_initialiser<T>, T>					base_type;
		typedef object_initialiser											class_type;
		typedef typename_type_k base_type::value_type						value_type;
		typedef typename_type_k base_type::pointer							pointer;
		typedef typename_type_k base_type::const_pointer					const_pointer;
		typedef typename_type_k base_type::reference						reference;
		typedef typename_type_k base_type::const_reference					const_reference;
		typedef typename_type_k base_type::size_type						size_type;
	/// @}

	/// \name Construct and Destruct
	/// @{
	public:
		void do_construct(pointer p)
		{
			new(p) T();
		}
		void do_construct(pointer p, const_reference value)
		{
			new(p) T(value);
		}
		void do_destruct(pointer p)
		{
			// vc 7.1 warning: "p" : unreference argument
			EXTL_SUPPRESS_UNUSED(p);
			p->~T();
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_OBJECT_INITIALISER_H */
/* //////////////////////////////////////////////////////////////////// */
