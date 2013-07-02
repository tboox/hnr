/* ///////////////////////////////////////////////////////////////////////
 * File:		expr_op.h		
 *
 * Created:		08.08.11			
 * Updated:		08.08.13
 *
 * Brief: expr_op class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_DETAIL_EXPR_OP_H
#define EXTL_MATH_DETAIL_EXPR_OP_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_EOP_SCALAR_SUPPORT
#	undef EXTL_EOP_SCALAR_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		EXTL_WORKAROUND_MSVC(==, 1200)	// VC6.0 support rvo
#	define EXTL_MATH_EOP_SCALAR_SUPPORT
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k T>
class eop_scalar;

// expr_traits
template<typename_param_k E>
struct expr_traits
{
	typedef E const&		expr_type;
};

#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
template<typename_param_k T>
struct expr_traits<eop_scalar<T> >
{
	typedef eop_scalar<T>	expr_type;
};
#endif

// eop_scalar
template<typename_param_k T>
class eop_scalar
{
	public:
		typedef eop_scalar															class_type;
		typedef T																	value_type;
		typedef T*																	pointer;
		typedef T const*															const_pointer;
		typedef T&																	reference;
		typedef T const&															const_reference;
		typedef e_size_t															size_type;
		typedef e_bool_t															bool_type;
		typedef e_ptrdiff_t															difference_type;
		typedef	e_int_t																int_type;	
		typedef e_size_t															index_type;

	private:
		// note: const_reference
		const_reference																m_value;

	public:
		explicit_k eop_scalar(const_reference value)
			: m_value(value)
		{
		}
	public:
		size_type			size() const					{ return 0;			}

	public:
		// note: const_reference
		const_reference	operator [](index_type index) const { return m_value;	}
};
// eop_add
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k E2
		>
class eop_add
{
	public:
		typedef typename_type_k expr_traits<E1>::expr_type							expr1_type;
		typedef typename_type_k expr_traits<E2>::expr_type							expr2_type;
		typedef eop_add																class_type;
		typedef	eop_scalar<T>														scalar_type;
		typedef typename_type_k scalar_type::value_type								value_type;
		typedef typename_type_k scalar_type::pointer								pointer;
		typedef typename_type_k scalar_type::const_pointer							const_pointer;
		typedef typename_type_k scalar_type::reference								reference;
		typedef typename_type_k scalar_type::const_reference						const_reference;
		typedef typename_type_k scalar_type::size_type								size_type;
		typedef typename_type_k scalar_type::bool_type								bool_type;
		typedef typename_type_k scalar_type::difference_type						difference_type;
		typedef	typename_type_k scalar_type::int_type								int_type;	
		typedef typename_type_k scalar_type::index_type								index_type;

	private:
		expr1_type																	m_expr1;
		expr2_type																	m_expr2;

	public:
		eop_add(expr1_type expr1, expr2_type expr2)
			: m_expr1(expr1), m_expr2(expr2)
		{
		}
	public:
		size_type size() const			
		{
			EXTL_ASSERT	(	m_expr1.size() == 0 
						||	m_expr2.size() == 0 
						||	m_expr1.size() == m_expr2.size());
			return m_expr1.size() != 0? m_expr1.size() : m_expr2.size();	
		}

	public:
		// note: not const_reference
		value_type operator [](index_type index) const 
		{ 
			EXTL_ASSERT(index < size());
			return m_expr1[index] + m_expr2[index];	
		}

};
// eop_sub
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k E2
		>
class eop_sub
{
	public:
		typedef typename_type_k expr_traits<E1>::expr_type							expr1_type;
		typedef typename_type_k expr_traits<E2>::expr_type							expr2_type;
		typedef eop_sub																class_type;
		typedef	eop_scalar<T>														scalar_type;
		typedef typename_type_k scalar_type::value_type								value_type;
		typedef typename_type_k scalar_type::pointer								pointer;
		typedef typename_type_k scalar_type::const_pointer							const_pointer;
		typedef typename_type_k scalar_type::reference								reference;
		typedef typename_type_k scalar_type::const_reference						const_reference;
		typedef typename_type_k scalar_type::size_type								size_type;
		typedef typename_type_k scalar_type::bool_type								bool_type;
		typedef typename_type_k scalar_type::difference_type						difference_type;
		typedef	typename_type_k scalar_type::int_type								int_type;	
		typedef typename_type_k scalar_type::index_type								index_type;

	private:
		expr1_type																	m_expr1;
		expr2_type																	m_expr2;

	public:
		eop_sub(expr1_type expr1, expr2_type expr2)
			: m_expr1(expr1), m_expr2(expr2)
		{
		}

	public:
		size_type size() const			
		{
			EXTL_ASSERT	(	m_expr1.size() == 0 
						||	m_expr2.size() == 0 
						||	m_expr1.size() == m_expr2.size());
			return m_expr1.size() != 0? m_expr1.size() : m_expr2.size();	
		}

	public:
		// note: not const_reference
		value_type operator [](index_type index) const 
		{ 
			EXTL_ASSERT(index < size());
			return m_expr1[index] - m_expr2[index];	
		}
};
// eop_mul
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k E2
		>
class eop_mul
{
	public:
		typedef typename_type_k expr_traits<E1>::expr_type							expr1_type;
		typedef typename_type_k expr_traits<E2>::expr_type							expr2_type;
		typedef eop_mul																class_type;
		typedef	eop_scalar<T>														scalar_type;
		typedef typename_type_k scalar_type::value_type								value_type;
		typedef typename_type_k scalar_type::pointer								pointer;
		typedef typename_type_k scalar_type::const_pointer							const_pointer;
		typedef typename_type_k scalar_type::reference								reference;
		typedef typename_type_k scalar_type::const_reference						const_reference;
		typedef typename_type_k scalar_type::size_type								size_type;
		typedef typename_type_k scalar_type::bool_type								bool_type;
		typedef typename_type_k scalar_type::difference_type						difference_type;
		typedef	typename_type_k scalar_type::int_type								int_type;	
		typedef typename_type_k scalar_type::index_type								index_type;

	private:
		expr1_type																	m_expr1;
		expr2_type																	m_expr2;

	public:
		eop_mul(expr1_type expr1, expr2_type expr2)
			: m_expr1(expr1), m_expr2(expr2)
		{
		}

	public:
		size_type size() const			
		{
			EXTL_ASSERT	(	m_expr1.size() == 0 
						||	m_expr2.size() == 0 
						||	m_expr1.size() == m_expr2.size());
			return m_expr1.size() != 0? m_expr1.size() : m_expr2.size();	
		}

	public:
		// note: not const_reference
		value_type operator [](index_type index) const 
		{ 
			EXTL_ASSERT(index < size());
			return m_expr1[index] * m_expr2[index];	
		}
};
// eop_div
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k E2
		>
class eop_div
{
	public:
		typedef typename_type_k expr_traits<E1>::expr_type							expr1_type;
		typedef typename_type_k expr_traits<E2>::expr_type							expr2_type;
		typedef eop_div																class_type;
		typedef	eop_scalar<T>														scalar_type;
		typedef typename_type_k scalar_type::value_type								value_type;
		typedef typename_type_k scalar_type::pointer								pointer;
		typedef typename_type_k scalar_type::const_pointer							const_pointer;
		typedef typename_type_k scalar_type::reference								reference;
		typedef typename_type_k scalar_type::const_reference						const_reference;
		typedef typename_type_k scalar_type::size_type								size_type;
		typedef typename_type_k scalar_type::bool_type								bool_type;
		typedef typename_type_k scalar_type::difference_type						difference_type;
		typedef	typename_type_k scalar_type::int_type								int_type;	
		typedef typename_type_k scalar_type::index_type								index_type;

	private:
		expr1_type																	m_expr1;
		expr2_type																	m_expr2;

	public:
		eop_div(expr1_type expr1, expr2_type expr2)
			: m_expr1(expr1), m_expr2(expr2)
		{
		}

	public:
		size_type size() const			
		{
			EXTL_ASSERT	(	m_expr1.size() == 0 
						||	m_expr2.size() == 0 
						||	m_expr1.size() == m_expr2.size());
			return m_expr1.size() != 0? m_expr1.size() : m_expr2.size();	
		}

	public:
		// note: not const_reference
		value_type operator [](index_type index) const 
		{ 
			EXTL_ASSERT(index < size());
			return m_expr1[index] / m_expr2[index];	
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_DETAIL_EXPR_OP_H */
/* //////////////////////////////////////////////////////////////////// */
