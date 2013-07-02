/* ///////////////////////////////////////////////////////////////////////
 * File:		array_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The array selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_ARRAY_SELECTOR_H
#define EXTL_CONTAINER_ARRAY_SELECTOR_H

/*!\file array_selector.h
 * \brief The array selector
 */
#ifndef __cplusplus
#	error array_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_array.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief array_selector class
 *
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Val>
struct array_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_array<Val>				array_type;
#else
	typedef basic_array	<	Val
						,	typename_type_def_k buffer_selector<Val>::buffer_type 
						>					array_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_ARRAY_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


