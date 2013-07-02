/* ///////////////////////////////////////////////////////////////////////
 * File:		find_all.h		
 *
 * Created:		08.07.01			
 * Updated:		08.07.01	
 *
 * Brief: The find_all and rfind_all functions
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_FIND_ALL_H
#define EXTL_ALGORITHM_FIND_ALL_H

/*!\file find_all.h
 * \brief The find_all and rfind_all functions
 */
#ifndef __cplusplus
#	error find_all.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std\algorithm.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* For compatibility.
 * WATCOM need return container_traits<C>::const_iterator instead of C::const_iterator
 */
EXTL_DETAIL_BEGIN_NAMESPACE
template <typename_param_k C>
struct container_traits
{	
	typedef typename_type_k C::iterator					iterator;
	typedef typename_type_k C::const_iterator			const_iterator;
	typedef typename_type_k C::reverse_iterator			reverse_iterator;
	typedef typename_type_k C::const_reverse_iterator	const_reverse_iterator;
};
EXTL_DETAIL_END_NAMESPACE

/*!find_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Val> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_iterator find_all(C const& container, Val const& value)
{
	return std_find(container.begin(), container.end(), value);
}
/*!rfind_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Val> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_reverse_iterator rfind_all(C const& container, Val const& value)
{
	return std_find(container.rbegin(), container.rend(), value);
}
/*!find_all_if
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Pr> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_iterator find_all_if(C const& container, Pr pred)
{
	return std_find_if(container.begin(), container.end(), pred);
}
/*!rfind_all_if
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k C, typename_param_k Pr> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
const_reverse_iterator rfind_all_if(C const& container, Pr pred)
{
	return std_find_if(container.rbegin(), container.rend(), pred);
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_FIND_ALL_H */
/* //////////////////////////////////////////////////////////////////// */
