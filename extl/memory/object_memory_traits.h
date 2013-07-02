/* ///////////////////////////////////////////////////////////////////////
 * File:		object_memory_traits.h		
 *
 * Created:		08.07.30				
 * Updated:		08.10.08
 *
 * Brief::		object_memory_traits class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_OBJECT_MEMORY_TRAITS_H
#define EXTL_MEMORY_OBJECT_MEMORY_TRAITS_H

/*!\file object_memory_traits.h
 * \brief object_memory_traits class 
 */
#ifndef __cplusplus
#	error object_memory_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "initialiser_selector.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief object_memory_traits class which is compatible with std.
 *
 * \param T the value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k T>
struct object_memory_traits
{
	/// \name Types
	/// @{
	public:
		typedef object_memory_traits<T>												class_type;
		typedef T																	value_type; 
		typedef value_type*															pointer;			
		typedef value_type const*													const_pointer;
		typedef value_type&															reference;			
		typedef value_type const&													const_reference;
		typedef	e_size_t															size_type;
		typedef e_int_t																int_type;
		typedef typename_type_k initialiser_selector<T>::initialiser_type			initialiser_type;
	/// @}
		
	public:
		/// Copy
		static const_pointer copy(pointer dest, const_pointer src, size_type n)
		{
			EXTL_ASSERT(NULL != dest);
			return non_pod_copy_n(dest, src, n);
		}
		/// Move
		static const_pointer move(pointer dest, const_pointer src, size_type n)
		{
			EXTL_ASSERT(NULL != dest);
			return non_pod_move_n(dest, src, n);
		}
		/// Fill
		static const_pointer fill(pointer dest, const_reference value, size_type n)
		{
			EXTL_ASSERT(NULL != dest);
			return non_pod_fill_n(dest, value, n);
		}
		/// Fill 0
		static const_pointer fill_0(pointer dest, size_type n)
		{
			EXTL_ASSERT(NULL != dest);
			return non_pod_fill_0_n(dest, n);
		}
}; 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_OBJECT_MEMORY_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
