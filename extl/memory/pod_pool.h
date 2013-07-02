/* ///////////////////////////////////////////////////////////////////////
 * File:		pod_pool.h		
 *
 * Created:		08.04.21					
 * Updated:		08.05.01	
 *
 * Brief: pod_pool class - faster than object_pool
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_POD_POOL_H
#define EXTL_MEMORY_POD_POOL_H

/*!\file pod_pool.h
 * \brief pod_pool class - faster than object_pool
 *
 * Note: The size of an element must be less than 8K,
 * and only one element is allocated at a time
 */
#ifndef __cplusplus
#	error pod_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "fixed_pool.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "../type/traits/is_pod.h"
#endif

#ifdef EXTL_MEMORY_POD_POOL_TEST_ENABLE
#	include "../counter/clock_counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief pod_pool class
 *
 * \param T The element type
 * \param CHUNK_SIZE The size of a chunk
 * \param A The allocator type
 *
 * [Structure]
 *
 *               --------------------      --------------------
 * m_chunks ---> |      chunk1      | ---> |      chunk2      | ---> NULL
 *               --------------------      --------------------
 *                       ¡ý
 *			             -------------------------------------
 * one chunk: m_head --> |    element1    -|->   element2   -|-> NULL
 *                       -------------------------------------
 *
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t CHUNK_SIZE = EXTL_FIXED_POOL_DEFAULT_CHUNK_SIZE
		,	typename_param_k A = typename_type_def_k allocator_selector<e_byte_t>::allocator_type	
#else
		,	e_size_t CHUNK_SIZE
		,	typename_param_k A
#endif
		>
class pod_pool
	: public fixed_pool< sizeof(T), CHUNK_SIZE, A >	
{
	private:
		typedef fixed_pool< sizeof(T), CHUNK_SIZE, A >						base_type;
	/// \name Types
	/// @{
	public:
		typedef pod_pool<T, CHUNK_SIZE, A>									class_type;
		typedef T															value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef typename_type_k base_type::allocator_type			allocator_type;
		typedef typename_type_k allocator_type::size_type					size_type;
	/// @}

	private:
		/// Prohibit copy constructor and copy assignment 
		pod_pool(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		pod_pool()
			: base_type()
		{
		#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
			EXTL_MUST_BE_POD(value_type);
		#endif
		}
		~pod_pool()
		{
		}
	/// @}

	public:
		/// Gets the allocator
		allocator_type allocator() const
		{
			return base_type::allocator();
		}
		/// Allocates a fixed-size pod memory block
		pointer allocate(size_type n = 1)
		{
			EXTL_ASSERT(1 == n);
			return reinterpret_cast<pointer>(base_type::allocate(n));
		}
		/// Only puts the pod block back into the pool
		void deallocate(pointer pod)
		{
			base_type::deallocate(reinterpret_cast<e_byte_t*>(pod));
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_POD_POOL_TEST_ENABLE
#	include "unit_test/pod_pool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_POD_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
