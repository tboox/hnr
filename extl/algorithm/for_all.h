/* ///////////////////////////////////////////////////////////////////////
 * File:		for_all.h		
 *
 * Created:		08.07.01			
 * Updated:		08.07.01	
 *
 * Brief: The for_all and rfor_all functions
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_FOR_ALL_H
#define EXTL_ALGORITHM_FOR_ALL_H

/*!\file for_all.h
 * \brief The for_all and rfor_all functions
 */
#ifndef __cplusplus
#	error for_all.h need be supported by c++.
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

/*!for_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k Ctr, typename_param_k Func>
EXTL_INLINE Func for_all(Ctr& container, Func func)
{	
	return std_foreach(container.begin(), container.end(), func);
}

/*!rfor_all
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k Ctr, typename_param_k Func>
EXTL_INLINE Func rfor_all(Ctr& container, Func func)
{	
	return std_foreach(container.rbegin(), container.rend(), func);
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_FOR_ALL_H */
/* //////////////////////////////////////////////////////////////////// */
