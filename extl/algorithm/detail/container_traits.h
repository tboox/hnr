/* ///////////////////////////////////////////////////////////////////////
 * File:		container_traits.h		
 *
 * Created:		08.11.09			
 * Updated:		09.01.26
 *
 * Brief:		The container_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_CONTAINER_TRAITS_H
#define EXTL_ALGORITHM_CONTAINER_TRAITS_H

/*!\file container_traits.h
 * \brief The container_traits class
 */
#ifndef __cplusplus
#	error container_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

/* For compatibility.
 * WATCOM need return container_traits<C>::const_iterator instead of C::const_iterator
 */
template <typename_param_k C>
struct container_traits
{	
	typedef typename_type_k C::iterator					iterator;
	typedef typename_type_k C::const_iterator			const_iterator;
	typedef typename_type_k C::reverse_iterator			reverse_iterator;
	typedef typename_type_k C::const_reverse_iterator	const_reverse_iterator;
	typedef typename_type_k C::value_type				value_type;
	typedef typename_type_k C::reference				reference;
	typedef typename_type_k C::const_reference			const_reference;
	typedef typename_type_k C::pointer					pointer;
	typedef typename_type_k C::const_pointer			const_pointer;
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_CONTAINER_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
