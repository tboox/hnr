/* ///////////////////////////////////////////////////////////////////////
 * File:		vvector_expr.h		
 *
 * Created:		08.08.11			
 * Updated:		09.01.27
 *
 * Brief:		the vvector_expr class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_DETAIL_VVECTOR_EXPR_H
#define EXTL_MATH_DETAIL_VVECTOR_EXPR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "expr_op.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

/* \brief vvector_expr
 *
 * \param T The value type
 * \param E The expression type: e.g. eop_add<eop_mul<...> ...> or eop_scalar<>
 *
 */
template<	typename_param_k T
		,	typename_param_k E
		>
class vvector_expr 
{
	public:
		typedef E																	expr_type;
		typedef vvector_expr															class_type;
		typedef typename_type_k expr_type::value_type								value_type;
		typedef typename_type_k expr_type::pointer									pointer;
		typedef typename_type_k expr_type::const_pointer							const_pointer;
		typedef typename_type_k expr_type::reference								reference;
		typedef typename_type_k expr_type::const_reference							const_reference;
		typedef typename_type_k expr_type::size_type								size_type;
		typedef typename_type_k expr_type::bool_type								bool_type;
		typedef typename_type_k expr_type::difference_type							difference_type;
		typedef	typename_type_k expr_type::int_type									int_type;	
		typedef typename_type_k expr_type::index_type								index_type;

	private:
		expr_type																	m_expr;

	public:
		explicit_k vvector_expr(expr_type const& expr)
			: m_expr(expr)
		{
		}

	public:
		size_type			size() const						{ return m_expr.size();	}

	public:
		value_type			operator [](index_type index) const	{ return m_expr[index];	}
	
	public:
		expr_type&			expr()			{ return m_expr;	}
		expr_type const&	expr() const	{ return m_expr;	}
};

// expr + expr
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k E2
		>
vvector_expr	<	T
			,	eop_add	<T, E1, E2> 
			>
operator +(vvector_expr<T, E1> const& expr1, vvector_expr<T, E2> const& expr2)
{
	return vvector_expr	<	T
						,	eop_add	<T, E1, E2> 
						>
						(	eop_add	<T, E1, E2>
									(	expr1.expr()
									,	expr2.expr()
									)
						);
}

// expr - expr
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k E2
		>
vvector_expr	<	T
			,	eop_sub	<T, E1, E2> 
			>
operator -(vvector_expr<T, E1> const& expr1, vvector_expr<T, E2> const& expr2)
{
	return vvector_expr	<	T
						,	eop_sub	<T, E1, E2> 
						>
						(	eop_sub	<T, E1, E2>
									(	expr1.expr()
									,	expr2.expr()
									)
						);
}

#ifdef EXTL_MATH_EOP_SCALAR_SUPPORT
// expr + value
template<	typename_param_k T
		,	typename_param_k E1
		>
vvector_expr	<	T
			,	eop_add	<	T
						,	E1
						,	eop_scalar<T>
						>
			>
operator +(vvector_expr<T, E1> const& expr1, T const& value)
{
	return vvector_expr	<	T
						,	eop_add	<	T
									,	E1
									,	eop_scalar<T>
									> 
						>
						(	eop_add	<	T
									,	E1
									,	eop_scalar<T>
									>
									(	expr1.expr()
									,	eop_scalar<T>(value) // temporary copy
									)
						);
}
// value + expr
template<	typename_param_k T
		,	typename_param_k E2
		>
vvector_expr	<	T
			,	eop_add	<	T
						,	eop_scalar<T>
						,	E2 
						>
			>
operator +(T const& value, vvector_expr<T, E2> const& expr2)
{
	return vvector_expr	<	T
						,	eop_add	<	T
									,	eop_scalar<T>
									,	E2
									> 
						>
						(	eop_add	<	T
									,	eop_scalar<T>
									,	E2
									>
									(	eop_scalar<T>(value) // temporary copy
									,	expr2.expr()
									)
						);
}

// expr - value
template<	typename_param_k T
		,	typename_param_k E1
		>
vvector_expr	<	T
			,	eop_sub	<	T
						,	E1
						,	eop_scalar<T>
						>
			>
operator -(vvector_expr<T, E1> const& expr1, T const& value)
{
	return vvector_expr	<	T
						,	eop_sub	<	T
									,	E1
									,	eop_scalar<T>
									> 
						>
						(	eop_sub	<	T
									,	E1
									,	eop_scalar<T>
									>
									(	expr1.expr()
									,	eop_scalar<T>(value) // temporary copy
									)
						);
}
// value - expr
template<	typename_param_k T
		,	typename_param_k E2
		>
vvector_expr	<	T
			,	eop_sub	<	T
						,	eop_scalar<T>
						,	E2 
						>
			>
operator -(T const& value, vvector_expr<T, E2> const& expr2)
{
	return vvector_expr	<	T
						,	eop_sub	<	T
									,	eop_scalar<T>
									,	E2
									> 
						>
						(	eop_sub	<	T
									,	eop_scalar<T>
									,	E2
									>
									(	eop_scalar<T>(value) // temporary copy
									,	expr2.expr()
									)
						);
}

// expr * value
template<	typename_param_k T
		,	typename_param_k E1
		>
vvector_expr	<	T
			,	eop_mul	<	T
						,	E1
						,	eop_scalar<T>
						>
			>
operator *(vvector_expr<T, E1> const& expr1, T const& value)
{
	return vvector_expr	<	T
						,	eop_mul	<	T
									,	E1
									,	eop_scalar<T>
									> 
						>
						(	eop_mul	<	T
									,	E1
									,	eop_scalar<T>
									>
									(	expr1.expr()
									,	eop_scalar<T>(value) // temporary copy
									)
						);
}
// value * expr
template<	typename_param_k T
		,	typename_param_k E2
		>
vvector_expr	<	T
			,	eop_mul	<	T
						,	eop_scalar<T>
						,	E2 
						>
			>
operator *(T const& value, vvector_expr<T, E2> const& expr2)
{
	return vvector_expr	<	T
						,	eop_mul	<	T
									,	eop_scalar<T>
									,	E2
									> 
						>
						(	eop_mul	<	T
									,	eop_scalar<T>
									,	E2
									>
									(	eop_scalar<T>(value) // temporary copy
									,	expr2.expr()
									)
						);
}
// expr / value
template<	typename_param_k T
		,	typename_param_k E1
		>
vvector_expr	<	T
			,	eop_div	<	T
						,	E1
						,	eop_scalar<T>
						>
			>
operator /(vvector_expr<T, E1> const& expr1, T const& value)
{
	return vvector_expr	<	T
						,	eop_div	<	T
									,	E1
									,	eop_scalar<T>
									> 
						>
						(	eop_div	<	T
									,	E1
									,	eop_scalar<T>
									>
									(	expr1.expr()
									,	eop_scalar<T>(value) // temporary copy
									)
						);
}
// value / expr
template<	typename_param_k T
		,	typename_param_k E2
		>
vvector_expr	<	T
			,	eop_div	<	T
						,	eop_scalar<T>
						,	E2 
						>
			>
operator /(T const& value, vvector_expr<T, E2> const& expr2)
{
	return vvector_expr	<	T
						,	eop_div	<	T
									,	eop_scalar<T>
									,	E2
									> 
						>
						(	eop_div	<	T
									,	eop_scalar<T>
									,	E2
									>
									(	eop_scalar<T>(value) // temporary copy
									,	expr2.expr()
									)
						);
}
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_DETAIL_VVECTOR_EXPR_H */
/* //////////////////////////////////////////////////////////////////// */
