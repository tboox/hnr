/* ///////////////////////////////////////////////////////////////////////
 * File:		marray_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The marray selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_MARRAY_SELECTOR_H
#define EXTL_CONTAINER_MARRAY_SELECTOR_H

/*!\file marray_selector.h
 * \brief The marray selector
 */
#ifndef __cplusplus
#	error marray_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "fixed_marray.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief marray_selector class
 *
 * \param N The dimension of the array
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<	e_size_t N
		,	typename_param_k Val
		>
struct marray_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef fixed_marray<N, Val>				marray_type;
#else
	typedef basic_marray<	N
						,	Val
						,	typename_type_k buffer_selector<T>::buffer_type 
						>						marray_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_MARRAY_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


