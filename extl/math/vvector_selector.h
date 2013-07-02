/* ///////////////////////////////////////////////////////////////////////
 * File:		vvector_selector.h		
 *
 * Created:		09.03.15	
 * Updated:		09.03.15	
 *
 * Brief:		vvector_selector class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_VVECTOR_SELECTOR_H
#define EXTL_MATH_VVECTOR_SELECTOR_H

/*!\file vvector_selector.h
 * \brief vvector_selector class
 */

#ifndef __cplusplus
#	error vvector_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_vvector.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief vvector_selector class
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k Val>
struct vvector_selector
{
	typedef basic_vvector	<	Val
							,	typename_type_k buffer_selector<Val>::buffer_type
							>			vvector_type;
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_VVECTOR_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
