/* ///////////////////////////////////////////////////////////////////////
 * File:		expr_vvector.h		
 *
 * Created:		08.08.11			
 * Updated:		09.01.27
 *
 * Brief:		the expression vvector class - delay to calculate value array expression
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_EXPR_VVECTOR_H
#define EXTL_MATH_EXPR_VVECTOR_H

#ifndef EXTL_MATH_EXPR_VVECTOR_SUPPORT
#	error expr_vvector.h is not supported by the current compiler.
#endif

/*!\file expr_vvector.h
 * \brief the expression vvector class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "detail/expr_op.h"
#include "detail/vvector_expr.h"

#ifdef EXTL_MATH_VVECTOR_TEST_ENABLE
#	include "../counter/counter.h"
#	include "basic_vvector.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief expr_vvector
 *
 * \param T The value type
 * \param A The val-array type
 *
 * \ingroup extl_group_math
 */
template<	typename_param_k T
		,	typename_param_k A
		>
class expr_vvector
{
	/// \name Types
	/// @{
	public:
		typedef A																	array_type;
		typedef expr_vvector															class_type;
		typedef typename_type_k array_type::value_type								value_type;
		typedef typename_type_k array_type::pointer									pointer;
		typedef typename_type_k array_type::const_pointer							const_pointer;
		typedef typename_type_k array_type::reference								reference;
		typedef typename_type_k array_type::const_reference							const_reference;
		typedef typename_type_k array_type::size_type								size_type;
		typedef typename_type_k array_type::bool_type								bool_type;
		typedef typename_type_k array_type::difference_type							difference_type;
		typedef	typename_type_k array_type::int_type								int_type;	
		typedef typename_type_k array_type::index_type								index_type;
	/// @}

	/// \name Members
	/// @{
	private:
		// note: reference
		array_type&																	m_array;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k expr_vvector(array_type& ar)
			: m_array(ar)
		{}
	/// @}

	private:
		expr_vvector(class_type const& rhs);

	/// \name Assignment
	/// @{
	public:
		/// expr => array
		template<	typename_param_k T2
				,	typename_param_k E2
				>
		class_type& operator =(EXTL_NS_DETAIL(vvector_expr)<T2, E2> const& expr)
		{
			EXTL_ASSERT(size() == expr.size());
			size_type n = size();
			for (size_type i = 0; i < n; ++i)
			{
				m_array[i] = expr[i];
			}
			return *this;
		}

		/// array => array
		class_type& operator =(class_type const& rhs)
		{
			if (this != &rhs)
			{
				EXTL_ASSERT(size() == rhs.size());
				size_type n = size();
				for (size_type i = 0; i < n; ++i)
				{
					m_array[i] = rhs[i];
				}
			}
			
			return *this;
		}

		/// value => array
		class_type& operator =(const_reference value)
		{
			m_array = value;
			return *this;
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		size_type			size() const						{ return m_array.size();	}
	/// @}

	/// \name Accessors
	/// @{
	public:
		reference			operator [](index_type index)		{ return m_array[index];	}
		const_reference		operator [](index_type index) const { return m_array[index];	}

		array_type&			array()								{ return m_array;			}
		array_type const&	array() const						{ return m_array;			}
	/// @}

};


// array + array
template<	typename_param_k T
		,	typename_param_k A1
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_add)	<T, A1, A2>
							>
operator +(expr_vvector<T, A1> const& ar1, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_add)	<T, A1, A2>
										>
										(	EXTL_NS_DETAIL(eop_add)	<T, A1, A2>
																	(	ar1.array()
																	,	ar2.array()
																	)
										);
}

// array + expr
template<	typename_param_k T
		,	typename_param_k A1
		,	typename_param_k E2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_add)	<T, A1, E2>
							>
operator +(expr_vvector<T, A1> const& ar1, EXTL_NS_DETAIL(vvector_expr)<T, E2> const& expr2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_add)	<T, A1, E2>
										>
										(	EXTL_NS_DETAIL(eop_add)	<T, A1, E2>
																	(	ar1.array()
																	,	expr2.expr()
																	)
										);
}
// expr + array
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_add)	<T,	E1,	A2>
							>
operator +(EXTL_NS_DETAIL(vvector_expr)<T, E1> const& expr1, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_add)	<T,	E1,	A2>
										>
										(	EXTL_NS_DETAIL(eop_add)	<T,	E1,	A2>
																	(	expr1.expr()
																	,	ar2.array()
																	)
										);
}

// array - array
template<	typename_param_k T
		,	typename_param_k A1
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_sub)	<T, A1, A2>
							>
operator -(expr_vvector<T, A1> const& ar1, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_sub)	<T, A1, A2>
										>
										(	EXTL_NS_DETAIL(eop_sub)	<T, A1, A2>
																	(	ar1.array()
																	,	ar2.array()
																	)
										);
}

// array - expr
template<	typename_param_k T
		,	typename_param_k A1
		,	typename_param_k E2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_sub)	<T, A1, E2>
							>
operator -(expr_vvector<T, A1> const& ar1, EXTL_NS_DETAIL(vvector_expr)<T, E2> const& expr2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_sub)	<T, A1, E2>
										>
										(	EXTL_NS_DETAIL(eop_sub)	<T, A1, E2>
																	(	ar1.array()
																	,	expr2.expr()
																	)
										);
}
// expr - array
template<	typename_param_k T
		,	typename_param_k E1
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_sub)	<T,	E1,	A2>
							>
operator -(EXTL_NS_DETAIL(vvector_expr)<T, E1> const& expr1, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_sub)	<T,	E1,	A2>
										>
										(	EXTL_NS_DETAIL(eop_sub)	<T,	E1,	A2>
																	(	expr1.expr()
																	,	ar2.array()
																	)
										);
}


#ifdef EXTL_MATH_EOP_SCALAR_SUPPORT
// array + value
template<	typename_param_k T
		,	typename_param_k A1
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_add)	<	T
														,	A1
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														> 
							>
operator +(expr_vvector<T, A1> const& ar1, T const& value)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_add)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	> 
										>
										(	EXTL_NS_DETAIL(eop_add)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	>
																	(	ar1.array()
																	,	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	)
										);
}
// value + array
template<	typename_param_k T
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_add)	<	T
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														,	A2 
														> 
							>
operator +(T const& value, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_add)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	> 
										>
										(	EXTL_NS_DETAIL(eop_add)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	>
																	(	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	,	ar2.array()
																	)
										);
}

// array - value
template<	typename_param_k T
		,	typename_param_k A1
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_sub)	<	T
														,	A1
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														> 
							>
operator -(expr_vvector<T, A1> const& ar1, T const& value)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_sub)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	> 
										>
										(	EXTL_NS_DETAIL(eop_sub)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	>
																	(	ar1.array()
																	,	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	)
										);
}
// value - array
template<	typename_param_k T
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_sub)	<	T
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														,	A2 
														> 
							>
operator -(T const& value, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_sub)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	> 
										>
										(	EXTL_NS_DETAIL(eop_sub)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	>
																	(	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	,	ar2.array()
																	)
										);
}

// array * value
template<	typename_param_k T
		,	typename_param_k A1
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_mul)	<	T
														,	A1
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														> 
							>
operator *(expr_vvector<T, A1> const& ar1, T const& value)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_mul)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	> 
										>
										(	EXTL_NS_DETAIL(eop_mul)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	>
																	(	ar1.array()
																	,	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	)
										);
}
// value * array
template<	typename_param_k T
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_mul)	<	T
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														,	A2 
														> 
							>
operator *(T const& value, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_mul)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	> 
										>
										(	EXTL_NS_DETAIL(eop_mul)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	>
																	(	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	,	ar2.array()
																	)
										);
}

// array / value
template<	typename_param_k T
		,	typename_param_k A1
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_div)	<	T
														,	A1
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														> 
							>
operator /(expr_vvector<T, A1> const& ar1, T const& value)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_div)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	> 
										>
										(	EXTL_NS_DETAIL(eop_div)	<	T
																	,	A1
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	>
																	(	ar1.array()
																	,	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	)
										);
}
// value / array
template<	typename_param_k T
		,	typename_param_k A2
		>
EXTL_NS_DETAIL(vvector_expr)	<	T
							,	EXTL_NS_DETAIL(eop_div)	<	T
														,	EXTL_NS_DETAIL(eop_scalar)<T>
														,	A2 
														> 
							>
operator /(T const& value, expr_vvector<T, A2> const& ar2)
{
	return EXTL_NS_DETAIL(vvector_expr)	<	T
										,	EXTL_NS_DETAIL(eop_div)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	> 
										>
										(	EXTL_NS_DETAIL(eop_div)	<	T
																	,	EXTL_NS_DETAIL(eop_scalar)<T>
																	,	A2
																	>
																	(	EXTL_NS_DETAIL(eop_scalar)<T>(value) // temporary copy
																	,	ar2.array()
																	)
										);
}
#endif


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_EXPR_VVECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
