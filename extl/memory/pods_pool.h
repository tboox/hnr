/* ///////////////////////////////////////////////////////////////////////
 * File:		pods_pool.h		
 *
 * Created:		08.05.04					
 * Updated:		08.05.04	
 *
 * Brief: pods_pool class - faster than objects_pool
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_PODS_POOL_H
#define EXTL_MEMORY_PODS_POOL_H

/*!\file pods_pool.h
 * \brief pod_pool class - faster than objects_pool
 */
#ifndef __cplusplus
#	error pods_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_pool.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "../type/traits/is_pod.h"
#endif

#ifdef EXTL_MEMORY_PODS_POOL_TEST_ENABLE
#	include "../counter/clock_counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief pods_pool class
 *
 * \param T: The element type
 *
 * \ingroup extl_group_memory
 */
template< typename_param_k T >
class pods_pool
	: public default_basic_pool
{
	private:
		typedef default_basic_pool													base_type;
	/// \name Types
	/// @{
	public:
		typedef pods_pool<T>														class_type;
		typedef T																	value_type;
		typedef typename_type_k base_type::allocator_type							allocator_type;
		typedef value_type*															pointer;
		typedef value_type const*													const_pointer;
		typedef value_type															reference;
		typedef value_type															const_reference;
		typedef typename_type_k base_type::size_type								size_type;
	/// @}

	/// \name Constuctors
	/// @{
	public:
		pods_pool()
			: base_type()
		{
		#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
			EXTL_MUST_BE_POD(value_type);
		#endif
		}
		~pods_pool()
		{
		}
	/// @}

	public:
		/// Allocates memory block of the specified size 
		pointer allocate(size_type size)
		{
			return static_cast<pointer>(base_type::allocate(size * sizeof(value_type)));
		}

		/// Reallocates memory block of the specified size 
		pointer reallocate(pointer pods, size_type size)
		{
			return static_cast<pointer>(base_type::reallocate(static_cast<void*>(pods), size * sizeof(value_type)));
		}
		
		/// Deallocates the block to pool 
		void deallocate(pointer pods)
		{
			base_type::deallocate(static_cast<void*>(pods));
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_PODS_POOL_TEST_ENABLE
#	include "unit_test/pods_pool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_PODS_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
