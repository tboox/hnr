/* ///////////////////////////////////////////////////////////////////////
 * File:		string_selector.h		
 *
 * Created:		08.10.21				
 * Updated:		08.12.21	
 *
 * Brief:		the string selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_SELECTOR_H
#define EXTL_STRING_SELECTOR_H

/*!\file string_selector.h
 * \brief the string selector
 */
#ifndef __cplusplus
#	error string_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "scoped_string.h"
#include "stack_string.h"
#include "attached_string.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief string_selector class
 *
 * \param Chr The character type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Chr>
struct string_selector
{
	/// \name Types
	/// @{
#if (1)
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_scoped_string<Chr>			scoped_string_type;
	typedef basic_stack_string<Chr>				stack_string_type;
	typedef basic_attached_string<Chr>			attached_string_type;
#	else
	typedef basic_scoped_string	<	Chr
								,	EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE
								,	string_traits<Chr, std_char_traits<Chr> >
								,	typename_type_k allocator_selector<e_wchar_t>::allocator_type
								>				scoped_string_type;
	typedef basic_stack_string	<	Chr
								,	EXTL_STRING_STACK_STRING_MAX_SPACE
								,	string_traits<Chr, std_char_traits<Chr> >
								>				stack_string_type;
	typedef basic_attached_string<	Chr
								,	EXTL_STRING_ATTACHED_STRING_MAX_SPACE
								,	string_traits<Chr, std_char_traits<Chr> >
								>				attached_string_type;
#	endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
#else
#	error Unknown string.
#endif

	typedef scoped_string_type					string_type;
	typedef scoped_string_type					large_string_type;
	typedef stack_string_type					small_string_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


