/* ///////////////////////////////////////////////////////////////////////
 * File:		matrix_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The matrix selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_MATRIX_SELECTOR_H
#define EXTL_CONTAINER_MATRIX_SELECTOR_H

/*!\file matrix_selector.h
 * \brief The matrix selector
 */
#ifndef __cplusplus
#	error matrix_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_matrix.h"
#include "sparse_matrix.h"
#include "symmetrical_matrix.h"
#include "symmetrical_sparse_matrix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief matrix_selector class
 *
 * \param Val The value type
 *
 * \ingroup extl_group_memory
 */
template<typename_param_k Val>
struct matrix_selector
{
	/// \name Types
	/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	typedef basic_matrix<Val>				matrix_type;
	typedef symmetrical_matrix<Val>			symmetrical_matrix_type;
#else
	typedef basic_matrix<	Val
						,	typename_type_k buffer_selector<Val>::buffer_type 
						>					matrix_type;
	typedef symmetrical_matrix	<	Val
								,	typename_type_k buffer_selector<Val>::buffer_type 
								>			symmetrical_matrix_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	typedef sparse_matrix<Val>				sparse_matrix_type;
	typedef symmetrical_sparse_matrix<Val>	symmetrical_sparse_matrix_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_MATRIX_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


