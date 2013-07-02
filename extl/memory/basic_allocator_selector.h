/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_allocator_selector.h		
 *
 * Created:		08.04.21					
 * Updated:		08.04.21
 *
 * Brief:	Basic memory allocator selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BASIC_ALLOCATOR_SELECTOR_H
#define EXTL_MEMORY_BASIC_ALLOCATOR_SELECTOR_H

/*!\file basic_allocator_selector.h
 * \brief Basic memory allocator selector
 */
#ifndef __cplusplus
#	error basic_allocator_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#ifndef EXTL_NO_STL
#	include <memory>
#endif
#include "new_allocator.h"
#include "malloc_allocator.h"
#include "null_allocator.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief basic_allocator_selector class
 *
 * \param T The allocator type
 *
 * [Allocators]
 * null_allocator<T>
 * new_allocator<T>
 * malloc_allocator<T>
 * std::allocator<T>
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
struct basic_allocator_selector
{
	/// \name Types
	/// @{
#if defined(EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_NULL_ALLOCATOR)
	typedef null_allocator<T>			allocator_type;
#elif defined(EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_NEW_ALLOCATOR)
	typedef new_allocator<T>			allocator_type;
#elif defined(EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_MALLOC_ALLOCATOR)
	typedef malloc_allocator<T>			allocator_type;
#elif defined(EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_STD_ALLOCATOR)
#	if !defined(EXTL_NO_STL)
	typedef EXTL_NS_STD(allocator)<T>	allocator_type;
#	else
	typedef new_allocator<T>			allocator_type;
#	endif
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
#endif /* EXTL_MEMORY_BASIC_ALLOCATOR_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


