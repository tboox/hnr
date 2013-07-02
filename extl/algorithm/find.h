/* ///////////////////////////////////////////////////////////////////////
 * File:		find.h		
 *
 * Created:		08.07.01			
 * Updated:		09.01.26	
 *
 * Brief:		The find functions
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_FIND_H
#define EXTL_ALGORITHM_FIND_H

/*!\file find.h
 * \brief The find functions
 */
#ifndef __cplusplus
#	error find.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std/algorithm.h"
#include "detail/container_traits.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!xtl_find
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k Val> 
EXTL_INLINE InIt xtl_find(InIt first, InIt last, Val const& value)
{
	return std_find(first, last, value);
}
/*!xtl_find_if
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k Pr> 
EXTL_INLINE InIt xtl_find_if(InIt first, InIt last, Pr pred)
{
	return std_find_if(first, last, pred); 
}

/*!find_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Val> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_iterator find_all(C const& container, Val const& value)
{
	return xtl_find(container.begin(), container.end(), value);
}
/*!rfind_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Val> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_reverse_iterator rfind_all(C const& container, Val const& value)
{
	return xtl_find(container.rbegin(), container.rend(), value);
}
/*!find_all_if
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Pr> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_iterator find_all_if(C const& container, Pr pred)
{
	return xtl_find_if(container.begin(), container.end(), pred);
}
/*!rfind_all_if
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Pr> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_reverse_iterator rfind_all_if(C const& container, Pr pred)
{
	return xtl_find_if(container.rbegin(), container.rend(), pred);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_FIND_H */
/* //////////////////////////////////////////////////////////////////// */
