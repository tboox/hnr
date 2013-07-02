/* ///////////////////////////////////////////////////////////////////////
 * File:		vmatrix_selector.h		
 *
 * Created:		09.03.15	
 * Updated:		09.03.15	
 *
 * Brief:		vmatrix_selector class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_VMATRIX_SELECTOR_H
#define EXTL_MATH_VMATRIX_SELECTOR_H

/*!\file vmatrix_selector.h
 * \brief vmatrix_selector class
 */

#ifndef __cplusplus
#	error vmatrix_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_vmatrix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief vmatrix_selector class
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k Val>
struct vmatrix_selector
{
	typedef basic_vmatrix	<	Val
							,	typename_type_k buffer_selector<Val>::buffer_type
							>			vmatrix_type;
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_VMATRIX_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
