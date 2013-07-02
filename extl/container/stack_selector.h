/* ///////////////////////////////////////////////////////////////////////
 * File:		stack_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The stack selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_STACK_SELECTOR_H
#define EXTL_CONTAINER_STACK_SELECTOR_H

/*!\file stack_selector.h
 * \brief The stack selector
 */
#ifndef __cplusplus
#	error stack_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_stack.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief stack_selector class
 *
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Val>
struct stack_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_stack<Val>				stack_type;
#else
	typedef basic_stack	<	Val
						,	typename_type_def_k array_selector<T>::array_type
						>					stack_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_STACK_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


