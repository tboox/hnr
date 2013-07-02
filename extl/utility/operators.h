/* ///////////////////////////////////////////////////////////////////////
 * File:		operators.h		
 *
 * Created:		08.03.03					
 * Updated:		08.04.17
 *
 * Brief: operators helper
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_OPERATORS_H
#define EXTL_UTILITY_OPERATORS_H

/*!\file operators.h
 * \brief operators helper
 *
 * Compatibility:
 * EXTL_COMPILER_IS_DMC: no supported (link failure)
 */
#ifndef __cplusplus
#	error operators.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief empty operators_base class 
 *
 * combine multiple operators for avoiding expansive space
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T >
struct operators_base_ 
{
	/* empty base class optimization bug with GCC 3.0.0 */
#if defined(EXTL_COMPILER_IS_GCC) && __GNUC__==3 && __GNUC_MINOR__==0 && __GNU_PATCHLEVEL__==0
	e_bool_t dummy; 
#endif
};
/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */
#ifdef EXTL_OPERATORS_BASE_DEFAULT_ARG
#	undef EXTL_OPERATORS_BASE_DEFAULT_ARG
#endif

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
#	define EXTL_OPERATORS_BASE_DEFAULT_ARG(T)	typename_param_k B = operators_base_<T>
#else
#	define EXTL_OPERATORS_BASE_DEFAULT_ARG(T)	typename_param_k B 
#endif
/*!\brief operators_less_1_ class
 *
 * A and B is the same type
 * A < B ==> B > A ==> B <= A ==> A >= B
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_less_1_ : B
{
	friend e_bool_t operator>(T const& lhs, T const& rhs)	{ return (rhs < lhs);	}
	friend e_bool_t operator<=(T const& lhs, T const& rhs)	{ return !(rhs < lhs);	}
	friend e_bool_t operator>=(T const& lhs, T const& rhs)	{ return !(lhs < rhs);	}
}; 
/*!\brief operators_less_2_ class
 *
 * A and B is the difference type
 * A < B ==> B > A ==> B <= A ==> A >= B
 * A > B ==> B < A ==> B >= A ==> A <= B
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_less_2_ : B
{
	/* A < B ==> B > A ==> B <= A ==> A >= B */
	friend e_bool_t operator>(R const& lhs, L const& rhs)	{ return rhs < lhs;		}
	friend e_bool_t operator<=(R const& lhs, L const& rhs)	{ return !(rhs < lhs);	}
	friend e_bool_t operator>=(L const& lhs, R const& rhs)	{ return !(lhs < rhs);	}
	
	/* A > B ==> B < A ==> B >= A ==> A <= B */
	friend e_bool_t operator<(R const& lhs, L const& rhs)	{ return rhs > lhs;		}
	friend e_bool_t operator>=(R const& lhs, L const& rhs)	{ return !(rhs > lhs);	}
	friend e_bool_t operator<=(L const& lhs, R const& rhs)	{ return !(lhs > rhs);	}
	
};
/*!\brief operators_equal_1_ class
 *
 * A and B is the same type
 * A == B ==> A != B
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_equal_1_ : B
{
	friend e_bool_t operator!=(T const& lhs, T const& rhs) { return !(lhs == rhs); }
};

/*!\brief operators_equal_1_ class
 *
 * A and B is the difference type
 * A == B ==> A != B
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_equal_2_ : B
{
	friend e_bool_t operator==(R const& rhs, L const& lhs) { return (lhs == rhs);	}
	friend e_bool_t operator!=(R const& rhs, L const& lhs) { return !(lhs == rhs);	}
	friend e_bool_t operator!=(L const& rhs, R const& lhs) { return !(rhs == lhs);	}
};

/*!\brief operators_equal_2_ class
 *
 * combine operators_equal_1_ and operators_equal_2_
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_equal_1_2_
	: operators_equal_1_<L, operators_equal_2_<L, R, B> >
{
};

/*!\brief operators_cmp_1_ class
 *
 * combine operators_less_1_ and operators_equal_1_
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_cmp_1_
	: operators_less_1_<T, operators_equal_1_<T, B> >
{
};
/*!\brief operators_cmp_2_ class
 *
 * combine operators_less_2_ and operators_equal_2_
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_cmp_2_
	: operators_less_2_<L, R, operators_equal_2_<L, R, B> >
{
};

/*!\brief operators_cmp_2_ class
 *
 * combine operators_cmp_1_ and operators_cmp_2_
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_cmp_1_2_
	: operators_cmp_1_<L, operators_cmp_2_<L, R, B> >
{
};

/* ///////////////////////////////////////////////////////////////////////
 * operators_equal(==) ==> (!=)
 * operators_equal(<) ==> (>, <= , >=)
 *
 * Note: Using macro substitute for operators classes, 
 * because operators classes are not supported by some compilers(eg: dmc)
 */

#ifdef EXTL_OPERATORS_LESS_1_
#	undef EXTL_OPERATORS_LESS_1_
#endif

#ifdef EXTL_OPERATORS_LESS_2_
#	undef EXTL_OPERATORS_LESS_2_
#endif

#ifdef EXTL_OPERATORS_EQUAL_1_
#	undef EXTL_OPERATORS_EQUAL_1_
#endif

#ifdef EXTL_OPERATORS_EQUAL_2_
#	undef EXTL_OPERATORS_EQUAL_2_
#endif

#ifdef EXTL_OPERATORS_CMP_1_
#	undef EXTL_OPERATORS_CMP_1_
#endif

#ifdef EXTL_OPERATORS_CMP_2_
#	undef EXTL_OPERATORS_CMP_2_
#endif

#ifdef EXTL_OPERATORS_CMP_1_2_
#	undef EXTL_OPERATORS_CMP_1_2_
#endif

#define EXTL_OPERATORS_LESS_1_(T)												\
friend e_bool_t operator>(T lhs, T rhs)		{	return rhs < lhs;		}		\
friend e_bool_t operator<=(T lhs, T rhs)	{	return !(rhs < lhs);	}		\
friend e_bool_t operator>=(T lhs, T rhs)	{	return !(lhs < rhs);	}	

#define EXTL_OPERATORS_LESS_2_(L, R)											\
friend e_bool_t operator>(R lhs, L rhs)		{	return rhs < lhs;		}		\
friend e_bool_t operator<(R lhs, L rhs)		{	return rhs > lhs;		}		\
friend e_bool_t operator<=(R lhs, L rhs)	{	return !(rhs < lhs);	}		\
friend e_bool_t operator>=(R lhs, L rhs)	{	return !(rhs > lhs);	}		\
friend e_bool_t operator<=(L lhs, R rhs)	{	return !(lhs > rhs);	}		\
friend e_bool_t operator>=(L lhs, R rhs)	{	return !(lhs < rhs);	}		

#define EXTL_OPERATORS_EQUAL_1_(T)												\
friend e_bool_t operator!=(T lhs, T rhs)	{	return !(lhs == rhs);	}

#define EXTL_OPERATORS_EQUAL_2_(L, R)											\
friend e_bool_t operator==(R rhs, L lhs)	{	return lhs == rhs;		}		\
friend e_bool_t operator!=(R rhs, L lhs)	{	return !(lhs == rhs);	}		\
friend e_bool_t operator!=(L rhs, R lhs)	{	return !(rhs == lhs);	}	

#define EXTL_OPERATORS_EQUAL_1_2_(L, R)											\
EXTL_OPERATORS_EQUAL_1_(L)														\
EXTL_OPERATORS_EQUAL_2_(L, R)

#define EXTL_OPERATORS_CMP_1_(T)												\
EXTL_OPERATORS_LESS_1_(T)														\
EXTL_OPERATORS_EQUAL_1_(T)

#define EXTL_OPERATORS_CMP_2_(L, R)												\
EXTL_OPERATORS_LESS_2_(L, R)													\
EXTL_OPERATORS_EQUAL_2_(L, R)

#define EXTL_OPERATORS_CMP_1_2_(L, R)											\
EXTL_OPERATORS_CMP_1_(L)														\
EXTL_OPERATORS_CMP_2_(L, R)

/* //////////////////////////////////////////////////////////////////// */
/* binary arithmetic operators
 * +=, -=, *=, /=, ^=, &=, |=		==>			+,-,*,/,^,&,|
 */
#ifdef EXTL_OPERATORS_BINARY_OPERATOR_1
#	undef EXTL_OPERATORS_BINARY_OPERATOR_1
#endif

#ifdef EXTL_OPERATORS_BINARY_OPERATOR_2
#	undef EXTL_OPERATORS_BINARY_OPERATOR_2
#endif

#ifdef EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1
#	undef EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1
#endif

#ifdef EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2
#	undef EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Using NRVO to optimize if NRVO is supported 
 */
#if defined(EXTL_NRVO_SUPPORT) || \
		defined(EXTL_FORCE_NRVO_SUPPORT)
/* ///////////////////////////////////////////////////////////////////////
 * eg: a + b <==> b + a
 */
#	define EXTL_OPERATORS_BINARY_OPERATOR_1( NAME, OP )							\
template <typename_param_k L, typename_param_k R,								\
				EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >							\
struct operators_##NAME##_2_ : B												\
{																				\
	friend L operator OP(const L& lhs, const R& rhs)							\
    {	L ret(lhs); ret OP##= rhs; return ret;	}								\
	friend L operator OP(const R& lhs, const L& rhs)							\
    {	L ret(rhs); ret OP##= lhs; return ret;	}								\
};																				\
																				\
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >				\
struct operators_##NAME##_1_ : B												\
{																				\
	friend T operator OP(const T& lhs, const T& rhs)							\
    {	T ret(lhs); ret OP##= rhs; return ret;	}								\
};

/* ///////////////////////////////////////////////////////////////////////
 * eg: a - b <!=> b - a
 */
#	define EXTL_OPERATORS_BINARY_OPERATOR_2( NAME, OP )							\
template <typename_param_k L, typename_param_k R,								\
								EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >			\
struct operators_##NAME##_2_ : B												\
{																				\
	friend L operator OP(const L& lhs, const R& rhs)							\
    {	L ret(lhs); ret OP##= rhs; return ret;	}								\
};																				\
																				\
template <typename_param_k L, typename_param_k R,								\
								EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >			\
struct operators_##NAME##_left_2_ : B											\
{																				\
	friend L operator OP(const R& lhs, const L& rhs)							\
    {	L ret(lhs); ret OP##= rhs; return ret;	}								\
};																				\
																				\
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >				\
struct operators_##NAME##_1_ : B												\
{																				\
	friend T operator OP(const T& lhs, const T& rhs)							\
    {	T ret(lhs); ret OP##= rhs; return ret;	}								\
};

#else
/* ///////////////////////////////////////////////////////////////////////
 * The following code if optimal if NRVO is not supported, but not symmetric.
 */
#	define EXTL_OPERATORS_BINARY_OPERATOR_1( NAME, OP )							\
template <typename_param_k L, typename_param_k R,								\
				EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >							\
struct operators_##NAME##_2_ : B												\
{																				\
	friend L operator OP(L lhs, const R& rhs) {	return lhs OP##= rhs;	}		\
	friend L operator OP(const R& lhs, L rhs) {	return rhs OP##= lhs;	}		\
};																				\
																				\
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >				\
struct operators_##NAME##_1_ : B												\
{																				\
	friend T operator OP(T lhs, const T& rhs) {	return lhs OP##= rhs;	}		\
};

#	define EXTL_OPERATORS_BINARY_OPERATOR_2( NAME, OP )							\
template <typename_param_k L, typename_param_k R,								\
				EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >							\
struct operators_##NAME##_2_ : B												\
{																				\
	friend L operator OP(L lhs, const R& rhs) {	return lhs OP##= rhs;	}		\
};																				\
																				\
template <typename_param_k L, typename_param_k R,								\
				EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >							\
struct operators_##NAME##_left_2_ : B											\
{																				\
	friend L operator OP(const R& lhs, const L& rhs)							\
	{	return L(lhs) OP##= rhs;	}											\
};																				\
																				\
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >				\
struct operators_##NAME##_1_ : B												\
{																				\
	friend T operator OP(T lhs, const T& rhs) {	return lhs OP##= rhs;	}		\
};
#endif /* defined(EXTL_NRVO_SUPPORT) || \
					defined(EXTL_FORCE_NRVO_SUPPORT) */

/* //////////////////////////////////////////////////////////////////// */
/* combine operators_##NAME##_1_ and operators_##NAME##_2_*/
#define EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1( NAME )						\
template <typename_param_k L, typename_param_k R,								\
				EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >							\
struct operators_##NAME##_1_2_													\
: operators_##NAME##_1_<L, operators_##NAME##_2_<L, R, B> >						\
{																				\
};

/* combine operators_##NAME##_1_ and operators_##NAME##_2_ and operators_##NAME##_left_2_*/
#define EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2( NAME )						\
template <typename_param_k L, typename_param_k R,								\
				EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >							\
struct operators_##NAME##_1_2_													\
: operators_##NAME##_1_<L,														\
	operators_##NAME##_2_<L, R,													\
		operators_##NAME##_left_2_<L, R, B> > >									\
{																				\
};

/* ///////////////////////////////////////////////////////////////////////
 * ##_1_: same type
 * ##_2_: different type
 */

EXTL_OPERATORS_BINARY_OPERATOR_1(add, +)	/* operators_add_1_, operators_add_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_1(mul, *)	/* operators_mul_1_, operators_mul_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_1(xor, ^)	/* operators_xor_1_, operators_xor_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_1(and, &)	/* operators_and_1_, operators_and_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_1(or, |)		/* operators_or_1_, operators_or_2_ */

EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1(add)		/* operators_add_1_2_ : operators_add_1_, operators_add_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1(mul)		/* operators_mul_1_2_ : operators_mul_1_, operators_mul_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1(xor)		/* operators_xor_1_2_ : operators_xor_1_, operators_xor_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1(and)		/* operators_and_1_2_ : operators_and_1_, operators_and_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1(or)		/* operators_or_1_2_  : operators_or_1_, operators_or_2_ */

EXTL_OPERATORS_BINARY_OPERATOR_2(sub, -)		/* operators_sub_1_, operators_sub_2_, operators_sub_left_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_2(div, /)		/* operators_div_1_, operators_div_2_, operators_div_left_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_2(lshift, <<)	/* operators_lshift_1_, operators_lshift_2_, operators_lshift_left_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_2(rshift, >>)	/* operators_rshift_1_, operators_rshift_2_, operators_rshift_left_2_ */

/* VECTORC: (%##=) can not be concatenated  */
#ifndef EXTL_COMPILER_IS_VECTORC
EXTL_OPERATORS_BINARY_OPERATOR_2(mod, %)	/* operators_mod_1_, operators_mod_2_, operators_mod_left_2_ */
#endif

EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2(sub)			/* operators_sub_1_2_ : operators_sub_1_, operators_sub_2_, operators_sub_left_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2(div)			/* operators_div_1_2_ : operators_div_1_, operators_div_2_, operators_div_left_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2(lshift)		/* operators_lshift_1_2_ : operators_lshift_1_, operators_lshift_2_, operators_lshift_left_2_ */
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2(rshift)		/* operators_rshift_1_2_ : operators_rshift_1_, operators_rshift_2_, operators_rshift_left_2_ */

#ifndef EXTL_COMPILER_IS_VECTORC
EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2(mod)		/* operators_mod_1_2_ : operators_mod_1_, operators_mod_2_, operators_mod_left_2_ */
#endif

/* ///////////////////////////////////////////////////////////////////////
 * shiift operators (<< >>)
 */
/*!\brief operators_shift_1_
 *
 * operators_lshift_1_
 * operators_rshift_1_ 
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_shift_1_
	:	operators_lshift_1_<T, 
			operators_rshift_1_<T, B 
		> > 
{
};
/*!\brief operators_shift_2_
 *
 * operators_lshift_2_
 * operators_lshift_left_2_
 * operators_rshift_2_
 * operators_rshift_left_2_  
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_shift_2_
	:	operators_lshift_2_<L, R,
			operators_rshift_2_<L, R, 
				operators_lshift_left_2_<L, R,
					operators_rshift_left_2_<L, R, B
		> > > > 
{
};

/*!\brief operators_shift_2_noleft_
 *
 * operators_lshift_2_
 * operators_rshift_2_
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_shift_2_noleft_
	:	operators_lshift_2_<L, R,
			operators_rshift_2_<L, R, B
		> > 
{
};

/*!\brief operators_shift_1_2_
 * 
 * operators_shift_1_
 * operators_shift_2_ 
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_shift_1_2_
:	operators_shift_1_<L, operators_shift_2_<L, R, B > > 
{
};
/* ///////////////////////////////////////////////////////////////////////
 * arithmetic operators (+ - * /)
 */

/*!\brief operators_arithmetic_1_
 *
 * operators_add_1_
 * operators_sub_1_ 
 * operators_mul_1_
 * operators_div_1_  
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_arithmetic_1_
:	operators_add_1_<T, 
		operators_sub_1_<T,
			operators_mul_1_<T, 
				operators_div_1_<T, B 
	> > > >
{
};

/*!\brief operators_arithmetic_2_
 *
 * operators_add_2_
 * operators_sub_2_
 * operators_sub_left_2_
 * operators_mul_2_
 * operators_div_2_
 * operators_div_left_2_  
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_arithmetic_2_
:	operators_add_2_<L, R,
		operators_sub_2_<L, R,
			operators_mul_2_<L, R,
				operators_div_2_<L, R, 
					operators_sub_left_2_<L, R,
						operators_div_left_2_<L, R, B
	> > > > > >
{
};

/*!\brief operators_arithmetic_2_noleft_
 *
 * operators_add_2_
 * operators_sub_2_
 * operators_mul_2_
 * operators_div_2_
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_arithmetic_2_noleft_
:	operators_add_2_<L, R,
		operators_sub_2_<L, R,
			operators_mul_2_<L, R,
				operators_div_2_<L, R, B
	> > > > 
{
};


/*!\brief operators_arithmetic_1_2_
 * 
 * operators_arithmetic_1_
 * operators_arithmetic_2_ 
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k L, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(L) >
struct operators_arithmetic_1_2_
:	operators_arithmetic_1_<L, operators_arithmetic_2_<L, R, B > > 
{
};


/* ///////////////////////////////////////////////////////////////////////
 * Using macro substitute for operators classes, 
 * because operators classes are not supported by some compilers
 * Note: L must not be built-in type
 *
 * Compatibility: EXTL_COMPILER_IS_DMC: not support
 */

#ifdef EXTL_OPERATORS_BINARY_1_
#	undef EXTL_OPERATORS_BINARY_1_
#endif

#ifdef EXTL_OPERATORS_BINARY_2_
#	undef EXTL_OPERATORS_BINARY_2_
#endif

#ifdef EXTL_OPERATORS_BINARY_LEFT_2_
#	undef EXTL_OPERATORS_BINARY_LEFT_2_
#endif

#if (defined(EXTL_NRVO_SUPPORT) || \
		defined(EXTL_FORCE_NRVO_SUPPORT)) 

#	define EXTL_OPERATORS_BINARY_1_(T, OP)							\
friend T operator OP(T const& lhs, T const& rhs)					\
{	T ret(lhs); ret OP##= rhs; return ret;	}						\

#	define EXTL_OPERATORS_BINARY_2_(L, R, OP)						\
friend L operator OP(L const& lhs, R rhs)							\
{	L ret(lhs); ret OP##= rhs; return ret;	}						\
friend L operator OP(R lhs, L const& rhs)							\
{	L ret(rhs); ret OP##= lhs; return ret;	}	

#	define EXTL_OPERATORS_BINARY_LEFT_2_(L, R, OP)					\
friend L operator OP(L const& lhs, R rhs)							\
{	L ret(lhs); ret OP##= rhs; return ret;	}						\
friend L operator OP(R lhs, L const& rhs)							\
{	L ret(lhs); ret OP##= rhs; return ret;	}

#else

#	define EXTL_OPERATORS_BINARY_1_(T, OP)							\
friend T operator OP(T lhs, T const& rhs)							\
{	return lhs OP##= rhs;	}										\

#	define EXTL_OPERATORS_BINARY_2_(L, R, OP)						\
friend L operator OP(L lhs, R rhs)									\
{	return lhs OP##= rhs;	}										\
friend L operator OP(R lhs, L rhs)									\
{	return rhs OP##= lhs;	}	

#	define EXTL_OPERATORS_BINARY_LEFT_2_(L, R, OP)					\
friend L operator OP(L lhs, R rhs)									\
{	return lhs OP##= rhs;	}										\
friend L operator OP(R lhs, L const& rhs)							\
{	return L(lhs) OP##= rhs;	}	

#endif

#define EXTL_OPERATORS_ADD_1_(T)		EXTL_OPERATORS_BINARY_1_(T, +)
#define EXTL_OPERATORS_MUL_1_(T)		EXTL_OPERATORS_BINARY_1_(T, *)
#define EXTL_OPERATORS_XOR_1_(T)		EXTL_OPERATORS_BINARY_1_(T, ^)
#define EXTL_OPERATORS_AND_1_(T)		EXTL_OPERATORS_BINARY_1_(T, &)
#define EXTL_OPERATORS_OR_1_(T)			EXTL_OPERATORS_BINARY_1_(T, |)
#define EXTL_OPERATORS_SUB_1_(T)		EXTL_OPERATORS_BINARY_1_(T, -)
#define EXTL_OPERATORS_DIV_1_(T)		EXTL_OPERATORS_BINARY_1_(T, /)
#define EXTL_OPERATORS_MOD_1_(T)		EXTL_OPERATORS_BINARY_1_(T, %)

#define EXTL_OPERATORS_ADD_2_(L, R)		EXTL_OPERATORS_BINARY_2_(L, R, +)
#define EXTL_OPERATORS_MUL_2_(L, R)		EXTL_OPERATORS_BINARY_2_(L, R, *)
#define EXTL_OPERATORS_XOR_2_(L, R)		EXTL_OPERATORS_BINARY_2_(L, R, ^)
#define EXTL_OPERATORS_AND_2_(L, R)		EXTL_OPERATORS_BINARY_2_(L, R, &)
#define EXTL_OPERATORS_OR_2_(L, R)		EXTL_OPERATORS_BINARY_2_(L, R, |)
#define EXTL_OPERATORS_SUB_2_(L, R)		EXTL_OPERATORS_BINARY_LEFT_2_(L, R, -)
#define EXTL_OPERATORS_DIV_2_(L, R)		EXTL_OPERATORS_BINARY_LEFT_2_(L, R, /)
#define EXTL_OPERATORS_MOD_2_(L, R)		EXTL_OPERATORS_BINARY_LEFT_2_(L, R, %)

#define EXTL_OPERATORS_ADD_1_2_(L, R)				\
		EXTL_OPERATORS_ADD_1_(L)					\
		EXTL_OPERATORS_ADD_2_(L, R)
#define EXTL_OPERATORS_MUL_1_2_(L, R)				\
		EXTL_OPERATORS_MUL_1_(L)					\
		EXTL_OPERATORS_MUL_2_(L, R)
#define EXTL_OPERATORS_XOR_1_2_(L, R)				\
		EXTL_OPERATORS_XOR_1_(L)					\
		EXTL_OPERATORS_XOR_2_(L, R)
#define EXTL_OPERATORS_AND_1_2_(L, R)				\
		EXTL_OPERATORS_AND_1_(L)					\
		EXTL_OPERATORS_AND_2_(L, R)
#define EXTL_OPERATORS_OR_1_2_(L, R)				\
		EXTL_OPERATORS_OR_1_(L)						\
		EXTL_OPERATORS_OR_2_(L, R)
#define EXTL_OPERATORS_SUB_1_2_(L, R)				\
		EXTL_OPERATORS_SUB_1_(L)					\
		EXTL_OPERATORS_SUB_2_(L, R)
#define EXTL_OPERATORS_DIV_1_2_(L, R)				\
		EXTL_OPERATORS_DIV_1_(L)					\
		EXTL_OPERATORS_DIV_2_(L, R)
#define EXTL_OPERATORS_MOD_1_2_(L, R)				\
		EXTL_OPERATORS_MOD_1_(L)					\
		EXTL_OPERATORS_MOD_2_(L, R)

#define EXTL_OPERATORS_ARITHMETIC_1_(T)				\
		EXTL_OPERATORS_ADD_1_(T)					\
		EXTL_OPERATORS_SUB_1_(T)					\
		EXTL_OPERATORS_MUL_1_(T)					\
		EXTL_OPERATORS_DIV_1_(T)	

#define EXTL_OPERATORS_ARITHMETIC_2_(L, R)			\
		EXTL_OPERATORS_ADD_2_(L, R)					\
		EXTL_OPERATORS_SUB_2_(L, R)					\
		EXTL_OPERATORS_MUL_2_(L, R)					\
		EXTL_OPERATORS_DIV_2_(L, R)

#define EXTL_OPERATORS_ARITHMETIC_1_2_(L, R)		\
		EXTL_OPERATORS_ADD_1_2_(L, R)				\
		EXTL_OPERATORS_SUB_1_2_(L, R)				\
		EXTL_OPERATORS_MUL_1_2_(L, R)				\
		EXTL_OPERATORS_DIV_1_2_(L, R)
/*!\brief operators_post_inc_
 *
 * ++i ==> i--
 *
 * \ingroup extl_group_utility
 */
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_post_inc_ : B
{
#ifndef EXTL_COMPILER_IS_DMC
	public:
		friend T operator++(T& x, int)
		{
			T ret(x); /* Inc_t ret(x) */
			++x;
			return ret;
		}
	/*private: 
		typedef T Inc_t;*/
#else
	public:
		T operator++(int)
		{
			T ret(*this); 
			++*this;
			return ret;
		}
#endif
};
/*!\brief operators_post_dec_
 *
 * --i ==> i--
 *
 * \ingroup extl_group_utility
 */
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_post_dec_ : B
{
#ifdef EXTL_COMPILER_IS_DMC
	public:
		friend T operator--(T& x, int)
		{
			T ret(x); /* Dec_t ret(x) */
			--x;
			return ret;
		}
	/*private: 
		typedef T Dec_t;*/
#else
	public:
		T operator--(int)
		{
			T ret(*this); 
			--*this;
			return ret;
		}
#endif
};

/*!\brief operators_post_dec_
 *
 * i++, i--
 *
 * \ingroup extl_group_utility
 */
template <typename_param_k T, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_post_inc_dec_
:	operators_post_inc_<T, operators_post_dec_<T, B> >
{
};

/*!\brief operators_deref_
 *
 * *p ==> p->
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, typename_param_k P, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_deref_ : B
{
	P operator->() const
	{ 
		return &*static_cast<T const&>(*this); 
	}
};
/*!\brief operators_index_
 *
 * *p ==> p[]
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k T, typename_param_k I, typename_param_k R, EXTL_OPERATORS_BASE_DEFAULT_ARG(T) >
struct operators_index_ : B
{
	R operator[](I n) const
	{
		return *(static_cast<const T&>(*this) + n);
	}
};

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_OPERATORS_BINARY_OPERATOR_1
#undef EXTL_OPERATORS_BINARY_OPERATOR_2
#undef EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_1
#undef EXTL_OPERATORS_BINARY_OPERATOR_COMBINE_2
#undef EXTL_OPERATORS_BASE_DEFAULT_ARG

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_UTILITY_OPERATORS_TEST_ENABLE
#	include "unit_test/operators_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_OPERATORS_H */
/* //////////////////////////////////////////////////////////////////// */
