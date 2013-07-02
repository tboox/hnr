/* ///////////////////////////////////////////////////////////////////////
 * File:		allocator_selector.h		
 *
 * Created:		08.03.22					
 * Updated:		08.04.14	
 *
 * Brief: Memory allocator selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_ALLOCATOR_SELECTOR_H
#define EXTL_MEMORY_ALLOCATOR_SELECTOR_H

/*!\file allocator_selector.h
 * \brief Memory allocator selector
 */
#ifndef __cplusplus
#	error allocator_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_allocator_selector.h"
#include "basic_pool_allocator.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief allocator_selector class
 *
 * \param T The allocator type
 *
 * [Allocators]
 * null_allocator<T>
 * new_allocator<T>
 * malloc_allocator<T>
 * std::allocator<T>
 *
 * basic_pool_allocator<T, A, L, MAX_FREE_INDEX>
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
struct allocator_selector
{
	/// \name Types
	/// @{
#if defined(EXTL_MEMORY_ALLOCATOR_SELECT_NULL_ALLOCATOR)
	typedef null_allocator<T>			allocator_type;
#elif defined(EXTL_MEMORY_ALLOCATOR_SELECT_NEW_ALLOCATOR)
	typedef new_allocator<T>			allocator_type;
#elif defined(EXTL_MEMORY_ALLOCATOR_SELECT_MALLOC_ALLOCATOR)
	typedef malloc_allocator<T>			allocator_type;
#elif defined(EXTL_MEMORY_ALLOCATOR_SELECT_BASIC_POOL_ALLOCATOR)
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_pool_allocator<T>		allocator_type;
#	else
	typedef basic_pool_allocator<	T
								,	typename_type_k synch_traits_selector::synch_traits_type
								,	default_basic_pool_allocator_tag
								>		allocator_type;
#	endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
#elif defined(EXTL_MEMORY_ALLOCATOR_SELECT_STD_ALLOCATOR) 
#	if !defined(EXTL_NO_STL)
	typedef EXTL_NS_STD(allocator)<T>	allocator_type;
#	else
#		ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_pool_allocator<T>		allocator_type;
#		else
	typedef basic_pool_allocator<	T
								,	typename_type_k synch_traits_selector::synch_traits_type
								,	default_basic_pool_allocator_tag
								>		allocator_type;
#		endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
#	endif /* EXTL_NO_STL */
#else
#	error Unknown allocator.
#endif
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_ALLOCATOR_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


