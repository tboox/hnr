/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The bit selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BIT_SELECTOR_H
#define EXTL_CONTAINER_BIT_SELECTOR_H

/*!\file bit_selector.h
 * \brief The bit selector
 */
#ifndef __cplusplus
#	error bit_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "bit_field.h"
#include "bit_array.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief bit_selector class
 *
 * \param F The field type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k F>
struct bit_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef bit_array<F>				array_type;
	typedef bit_field<F>				field_type;
#else
	typedef bit_array	<	F
						,	typename_type_k buffer_selector<F>::buffer_type
						>				array_type;
	typedef bit_field<F>				field_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BIT_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


