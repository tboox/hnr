/* ///////////////////////////////////////////////////////////////////////
 * File:		allocator_traits.h		
 *
 * Created:		08.05.26					
 * Updated:		08.05.26
 *
 * Brief: Memory allocator traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_ALLOCATOR_TRAITS_H
#define EXTL_MEMORY_ALLOCATOR_TRAITS_H

/*!\file allocator_traits.h
 * \brief Memory allocator traits
 */
#ifndef __cplusplus
#	error allocator_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "allocator.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief allocator_traits class
 *
 * \param A The allocator type
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k A >
struct allocator_traits
{
	/// Indicates whether reallocate is supported
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_reallocate = e_false_v);
};

#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
template < typename_param_k T >
struct allocator_traits< malloc_allocator<T> >
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_reallocate = e_true_v);
};
template < typename_param_k T, typename_param_k ST, typename_param_k Tag >
struct allocator_traits< basic_pool_allocator<T, ST, Tag> >
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_reallocate = e_true_v);
};
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_ALLOCATOR_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */


