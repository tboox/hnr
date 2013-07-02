/* ///////////////////////////////////////////////////////////////////////
 * File:		queue_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The queue selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_QUEUE_SELECTOR_H
#define EXTL_CONTAINER_QUEUE_SELECTOR_H

/*!\file queue_selector.h
 * \brief queue selector
 */
#ifndef __cplusplus
#	error queue_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_queue.h"
#include "fixed_reque.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief queue_selector class
 *
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Val>
struct queue_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_queue<Val>				queue_type;
	typedef fixed_reque<Val>				reque_type;
#else
	typedef basic_queue	<	Val
						,	typename_type_k list_selector<Val>::list_type
						>					queue_type;
	typedef fixed_reque	<	Val
						,	EXTL_FIXED_REQUE_DEFAULT_MAX_SIZE
						,	typename_type_k buffer_selector<T>::buffer_type
						>					reque_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_QUEUE_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


