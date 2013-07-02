/* ///////////////////////////////////////////////////////////////////////
 * File:		comparsion.h		
 *
 * Created:		08.11.20			
 * Updated:		08.11.20
 *
 * Brief:		The Comparsion Operators
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_STD_COMPARISON_H
#define EXTL_FUNCTIONAL_STD_COMPARISON_H

/*!\file comparsion.h
 * \brief comparsion class
 */
#ifndef __cplusplus
#	error comparsion.h need be supported by c++.
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

/*!functor for operator ==
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_equal_to
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs == rhs);
	}
};

/*!functor for operator !=
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_not_equal_to
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs != rhs);
	}
};

/*!functor for operator >
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_greater
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs > rhs);
	}
};

/*!functor for operator >=
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_greater_equal
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs >= rhs);
	}
};
/*!functor for operator <
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_less
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs < rhs);
	}
};

/*!functor for operator <=
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_less_equal
	: public func2_base<e_bool_t, T, T>
{	
	e_bool_t operator()(T const& lhs, T const& rhs) const
	{
		return (lhs <= rhs);
	}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_FUNCTIONAL_STD_COMPARISON_H */
/* //////////////////////////////////////////////////////////////////// */
