/* ///////////////////////////////////////////////////////////////////////
 * File:		list_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The list selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_LIST_SELECTOR_H
#define EXTL_CONTAINER_LIST_SELECTOR_H

/*!\file list_selector.h
 * \brief The list selector
 */
#ifndef __cplusplus
#	error list_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_list.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief list_selector class
 *
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Val>
struct list_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_list<Val>				list_type;
#else
	typedef basic_list	<	Val
						,	typename_type_k allocator_selector<Val>::allocator_type 
						,	typename_type_k memory_traits_selector<Val>::memory_traits_type
						,	typename_type_k initialiser_selector<Val>::initialiser_type
						>				list_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_LIST_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


