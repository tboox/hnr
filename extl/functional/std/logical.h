/* ///////////////////////////////////////////////////////////////////////
 * File:		logical.h		
 *
 * Created:		08.11.20			
 * Updated:		08.11.20
 *
 * Brief:		The Logical Operators
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_STD_LOGICAL_H
#define EXTL_FUNCTIONAL_STD_LOGICAL_H

/*!\file logical.h
 * \brief logical class
 */
#ifndef __cplusplus
#	error logical.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../func_base.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!functor for operator &&
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_logical_and
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs && rhs);
	}
};

/*!functor for operator ||
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_logical_or
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs || rhs);
	}
};

/*!functor for operator !
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_logical_not
	: public func1_base<e_bool_t, T>
{	
	e_bool_t operator()(T const& lhs) const
	{
		return (!lhs);
	}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_FUNCTIONAL_STD_LOGICAL_H */
/* //////////////////////////////////////////////////////////////////// */
