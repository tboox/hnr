/* ///////////////////////////////////////////////////////////////////////
 * File:		buffer_selector.h		
 *
 * Created:		08.10.21				
 * Updated:		08.10.21	
 *
 * Brief:		the memory buffer selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BUFFER_SELECTOR_H
#define EXTL_MEMORY_BUFFER_SELECTOR_H

/*!\file buffer_selector.h
 * \brief memory buffer selector
 */
#ifndef __cplusplus
#	error buffer_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "scoped_buffer.h"
#include "stack_buffer.h"
#include "attached_buffer.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief buffer_selector class
 *
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Val>
struct buffer_selector
{
	/// \name Types
	/// @{
#if (1)
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef scoped_buffer<Val>			scoped_buffer_type;
	typedef stack_buffer<Val>			stack_buffer_type;
	typedef attached_buffer<Val>		attached_buffer_type;
#	else
	typedef scoped_buffer	<	Val
							,	EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE
							,	typename_type_k allocator_selector<Val>::allocator_type 
							,	typename_type_k memory_traits_selector<Val>::memory_traits_type
							,	typename_type_k initialiser_selector<Val>::initialiser_type
							>			scoped_buffer_type;
	typedef stack_buffer<	Val
						,	EXTL_MEMORY_STACK_BUFFER_MAX_SPACE
						,	typename_type_k memory_traits_selector<Val>::memory_traits_type
						>				stack_buffer_type;
	typedef attached_buffer<	Val
							,	EXTL_MEMORY_ATTACHED_BUFFER_MAX_SPACE
							,	typename_type_k memory_traits_selector<Val>::memory_traits_type
							>			attached_buffer_type;
#	endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
#else
#	error Unknown buffer.
#endif

	typedef scoped_buffer_type			buffer_type;
	typedef scoped_buffer_type			large_buffer_type;
	typedef stack_buffer_type			small_buffer_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_BUFFER_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


