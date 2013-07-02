/* ///////////////////////////////////////////////////////////////////////
 * File:		pair_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The pair selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_PAIR_SELECTOR_H
#define EXTL_CONTAINER_PAIR_SELECTOR_H

/*!\file pair_selector.h
 * \brief The pair selector
 */
#ifndef __cplusplus
#	error pair_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_pair.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief pair_selector class
 *
 * \param T1 The first type
 * \param T2 The second type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k T1
		,	typename_param_k T2
		>
struct pair_selector
{
	/// \name Types
	/// @{
	typedef basic_pair<T1, T2>				pair_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_PAIR_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


