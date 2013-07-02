/* ///////////////////////////////////////////////////////////////////////
 * File:		for.h		
 *
 * Created:		09.01.26			
 * Updated:		09.01.26	
 *
 * Brief:		The for algorithms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_FOR_H
#define EXTL_ALGORITHM_FOR_H

/*!\file for.h
 * \brief The for algorithms
 */
#ifndef __cplusplus
#	error for.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std/algorithm.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!xtl_foreach
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k Pr>
EXTL_INLINE Pr xtl_foreach(InIt first, InIt last, Pr pred)
{	
	return std_foreach(first, last, pred);
}

/*!for_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k Ctr, typename_param_k Pr>
EXTL_INLINE Pr for_all(Ctr& container, Pr pred)
{	
	return xtl_foreach(container.begin(), container.end(), pred);
}

/*!rfor_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k Ctr, typename_param_k Pr>
EXTL_INLINE Pr rfor_all(Ctr& container, Pr pred)
{	
	return xtl_foreach(container.rbegin(), container.rend(), pred);
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_FOR_H */
/* //////////////////////////////////////////////////////////////////// */
