/* ///////////////////////////////////////////////////////////////////////
 * File:		initialiser_selector.h		
 *
 * Created:		08.07.30				
 * Updated:		08.07.30
 *
 * Brief: initialiser_selector class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_INITIALISER_SELECTOR_H
#define EXTL_MEMORY_INITIALISER_SELECTOR_H

/*!\file initialiser_selector.h
 * \brief initialiser_selector class
 */
#ifndef __cplusplus
#	error initialiser_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "object_initialiser.h"
#include "pod_initialiser.h"

#include "../type/traits/is_arithmetic.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "../type/traits/is_pod.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	include "../type/traits/is_scalar.h"
#endif

#ifdef EXTL_MPL_IF_SUPPORT
#	include "../mpl/if_.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief initialiser_selector class
 *
 * \param T The value type
 * 
 * \ingroup extl_group_memory
 */
template<typename_param_k T>
struct initialiser_selector
{
	#ifdef EXTL_MPL_IF_SUPPORT
		#if defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
			typedef typename_type_k EXTL_NS_MPL(if_)<	(is_pod<T>::value)
													,	pod_initialiser<T>
													,	object_initialiser<T>
													>::type			initialiser_type;

		#elif defined(EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT)
			typedef typename_type_k EXTL_NS_MPL(if_)<	(is_scalar<T>::value)
													,	pod_initialiser<T>
													,	object_initialiser<T>
													>::type			initialiser_type;

		#else
			typedef typename_type_k EXTL_NS_MPL(if_)<	(is_arithmetic<T>::value)
													,	pod_initialiser<T>
													,	object_initialiser<T>
													>::type			initialiser_type;
		#endif
	#else
		typedef object_initialiser<T>								initialiser_type;
	#endif
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_INITIALISER_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
