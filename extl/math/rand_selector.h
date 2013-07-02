/* ///////////////////////////////////////////////////////////////////////
 * File:		rand_selector.h		
 *
 * Created:		08.12.15		
 * Updated:		08.12.15
 *
 * Brief:		rand_selector class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_RAND_SELECTOR_H
#define EXTL_MATH_RAND_SELECTOR_H

/*!\file rand_selector.h
 * \brief rand_selector class
 */

#ifndef __cplusplus
#	error rand_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "linear_rand.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief rand_selector class
 *
 * \ingroup extl_group_algorithm
 */
struct rand_selector
{
	typedef linear_rand			rand_type;
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_RAND_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
