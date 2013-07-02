/* ///////////////////////////////////////////////////////////////////////
 * File:		arithmetic.h		
 *
 * Created:		08.11.20			
 * Updated:		08.11.20
 *
 * Brief:		The Arithmetic Operators
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_STD_ARITHMETIC_H
#define EXTL_FUNCTIONAL_STD_ARITHMETIC_H

/*!\file arithmetic.h
 * \brief arithmetic class
 */
#ifndef __cplusplus
#	error arithmetic.h need be supported by c++.
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

/*!functor for operator +
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_plus
	: public func2_base<T, T, T>
{	
	T operator()(T const& lhs, T const& rhs) const
	{
		return (lhs + rhs);
	}
};

/*!functor for operator -
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_minus
	: public func2_base<T, T, T>
{	
	T operator()(T const& lhs, T const& rhs) const
	{
		return (lhs - rhs);
	}
};

/*!functor for operator *
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_multiplies
	: public func2_base<T, T, T>
{	
	T operator()(T const& lhs, T const& rhs) const
	{
		return (lhs * rhs);
	}
};

/*!functor for operator /
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_divides
	: public func2_base<T, T, T>
{	
	T operator()(T const& lhs, T const& rhs) const
	{
		return (lhs / rhs);
	}
};

/*!functor for operator %
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_modulus
	: public func2_base<T, T, T>
{	
	T operator()(T const& lhs, T const& rhs) const
	{
		return (lhs % rhs);
	}
};

/*!functor for operator -
 * 
 * \param T The value type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k T>
struct std_negate
	: public func1_base<T, T>
{	
	T operator()(T const& lhs) const
	{
		return (-lhs);
	}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_FUNCTIONAL_STD_ARITHMETIC_H */
/* //////////////////////////////////////////////////////////////////// */
