/* ///////////////////////////////////////////////////////////////////////
 * File:		is_convertible.h		
 *
 * Created:		08.03.17					
 * Updated:		08.07.09
 *
 * Brief: is_convertible traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_H
#define EXTL_TYPE_TRAITS_IS_CONVERTIBLE_H

#ifndef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#	error extl::is_convertible is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"
#include "is_arithmetic.h"
#include "is_void.h"

#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	include "add_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
#	include "is_abstract.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_CONVERTIBLE(type1, type2)			EXTL_MUST_BE_2_(is_convertible, type1, type2)
#define EXTL_MUST_BE_CV_CONVERTIBLE(type1, type2)		EXTL_MUST_BE_CV_2_(is_convertible, type1, type2)

#define EXTL_MUST_NOT_BE_CONVERTIBLE(type1, type2)		EXTL_MUST_NOT_BE_2_(is_convertible, type1, type2)
#define EXTL_MUST_NOT_BE_CV_CONVERTIBLE(type1, type2)	EXTL_MUST_NOT_BE_CV_2_(is_convertible, type1, type2)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
#ifdef EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT
/* DMC */
#	if defined(EXTL_COMPILER_IS_DMC)
struct any_conversion
{
    template<typename_param_k T> 
	any_conversion(T const volatile &);

    template<typename_param_k T>
	any_conversion(T&);
};
template<typename_param_k From>
struct is_convertible_helper
{
	template<typename_param_k To>
	struct result
	{
		template<typename_param_k T>
		static no_type EXTL_CDECL is_convertible_checker(any_conversion, float, T);
        static yes_type EXTL_CDECL is_convertible_checker(To, int, int);
		static From from;
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(yes_type) == sizeof(is_convertible_checker(from, 0, 0))));
	};
}; 
EXTL_TEMPLATE_SPECIALISATION
struct is_convertible_helper<void>
{
	template<typename_param_k To>
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (is_void<To>::value));
	};
};

template <typename_param_k From, typename_param_k To>
struct is_convertible_impl
    : is_convertible_helper<From>::template result<To>
{
};

/* BORLAND */
#	elif defined(EXTL_COMPILER_IS_BORLAND)

struct any_conversion
{
    template<typename_param_k T> 
	any_conversion(const volatile T&);

    template<typename_param_k T>
	any_conversion(T&);
};
template<typename_param_k T>
struct checker
{
	static no_type EXTL_CDECL is_convertible_checker(any_conversion, ...);
	static yes_type EXTL_CDECL is_convertible_checker(T, int);
};

template<typename_param_k From, typename_param_k To>
struct is_convertible_impl
{
    static From from;
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = 
										(sizeof(yes_type) == sizeof(checker<To>::is_convertible_checker(from, 0))));

};
#	else
template<typename_param_k From>
struct is_convertible_helper
{
	template<typename_param_k To>
	struct result
	{
		// DMC would generate ambiguous 
		static no_type EXTL_CDECL is_convertible_checker(...);
        static yes_type EXTL_CDECL is_convertible_checker(To);
		static From from;

	#ifdef EXTL_COMPILER_IS_MSVC
	#	pragma warning(push)
	#	pragma warning(disable:4244)
	#endif
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(yes_type) == sizeof(is_convertible_checker(from))));
	#ifdef EXTL_COMPILER_IS_MSVC
	#	pragma warning(pop)
	#endif

	};
};
EXTL_TEMPLATE_SPECIALISATION
struct is_convertible_helper<void>
{
	template<typename_param_k To>
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (is_void<To>::value));
	};
};

template<typename_param_k From, typename_param_k To>
struct is_convertible_impl
    : is_convertible_helper<From>::template_qual_k result<To>
{
};

#	endif

#if !defined(EXTL_COMPILER_IS_BORLAND) && \
		!defined(EXTL_COMPILER_IS_VECTORC) && \
			defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) 
template<typename_param_k From, typename_param_k To>
struct is_convertible
{
#	ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
	typedef typename_type_k add_ref<From>::type reference;
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_and	<	(op_or	<	(is_void<To>::value)
																	,	(is_convertible_impl<reference, To>::value)
																	>::value)
														,	(op_not<(is_array<To>::value)>::value)
														>::value));
#	else
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_and	<	(op_or	<	(is_void<To>::value)
																	,	(is_convertible_impl<From, To>::value)
																	>::value)
														,	(op_not<(is_array<To>::value)>::value)
														>::value));
#	endif
};

#else /* !defined(EXTL_COMPILER_IS_BORLAND) && \
			!defined(EXTL_COMPILER_IS_VECTORC) */

template<e_bool_t is_arithmetic1, e_bool_t is_arithmetic2, e_bool_t is_abstract>
struct is_convertible_impl_select
{
   template < typename_param_k From, typename_param_k To >
   struct rebind
   {
      typedef is_convertible_impl<From, To> type;
   };
};

/* arithmetic ==> arithmetic */
EXTL_TEMPLATE_SPECIALISATION
struct is_convertible_impl_select< e_true_v, e_true_v, e_false_v >
{
   template < typename_param_k From, typename_param_k To >
   struct rebind
   {
      typedef yes_type type;
   };
};

/* non-arithmetic ==> abstract */
EXTL_TEMPLATE_SPECIALISATION
struct is_convertible_impl_select< e_false_v, e_false_v, e_true_v >
{
   template < typename_param_k From, typename_param_k To >
   struct rebind
   {
      typedef no_type type;
   };
};

/* arithmetic ==> abstract */
EXTL_TEMPLATE_SPECIALISATION
struct is_convertible_impl_select< e_true_v, e_false_v, e_true_v >
{
   template < typename_param_k From, typename_param_k To >
   struct rebind
   {
      typedef no_type type;
   };
};

template < typename_param_k From, typename_param_k To >
struct is_convertible_impl_dispatch_base
{
   typedef is_convertible_impl_select	<	(is_arithmetic<From>::value) 
										,	(is_arithmetic<To>::value)
#	ifdef EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
										,	(is_abstract<To>::value)
#	else
										,	e_false_v
#	endif
										> selector;

   typedef typename_type_k selector::template_qual_k rebind<From, To> is_convertible_impl_binder;
   typedef typename_type_k is_convertible_impl_binder::type type;
};

template < typename_param_k From, typename_param_k To >
struct is_convertible_impl_dispatch 
   : public is_convertible_impl_dispatch_base<From, To>::type
{};

EXTL_BOOL_TRAIT_DEF_2(is_convertible, (is_convertible_impl_dispatch<T1, T2>::value))

#endif /* !defined(EXTL_COMPILER_IS_BORLAND) && \
			!defined(EXTL_COMPILER_IS_VECTORC) */

/* void(cv) ==> void(cv) */
#ifdef EXTL_CV_VOID_SPEC_SUPPORT
#   define EXTL_BOOL_CV_VOID_TRAIT_SPEC2_PART1(trait, spec1, spec2, value) \
    EXTL_BOOL_TRAIT_SPEC_2(trait, spec1, spec2, value) \
    EXTL_BOOL_TRAIT_SPEC_2(trait, spec1, spec2 const, value) \
    EXTL_BOOL_TRAIT_SPEC_2(trait, spec1, spec2 volatile, value) \
    EXTL_BOOL_TRAIT_SPEC_2(trait, spec1, spec2 const volatile, value) 

    EXTL_BOOL_CV_VOID_TRAIT_SPEC2_PART1(is_convertible, void, void, e_true_v) 
    EXTL_BOOL_CV_VOID_TRAIT_SPEC2_PART1(is_convertible, void const, void, e_true_v) 
    EXTL_BOOL_CV_VOID_TRAIT_SPEC2_PART1(is_convertible, void volatile, void, e_true_v) 
    EXTL_BOOL_CV_VOID_TRAIT_SPEC2_PART1(is_convertible, void const volatile, void, e_true_v) 

#	undef EXTL_BOOL_CV_VOID_TRAIT_SPEC2_PART1
#else
    EXTL_BOOL_TRAIT_SPEC_2(is_convertible, void, void, e_true_v)
#endif /* EXTL_CV_VOID_SPEC_SUPPORT */

// partial specializtion: From==>void(cv), void(cv)==>To) 
#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k To, is_convertible,void, To, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k From, is_convertible, From, void, e_false_v)
#	ifdef EXTL_CV_VOID_SPEC_SUPPORT
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k To, is_convertible,void const, To, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k To, is_convertible,void volatile, To, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k To, is_convertible,void const volatile, To, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k From, is_convertible, From, void const, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k From, is_convertible, From, void volatile, e_false_v)
EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(typename_param_k From, is_convertible, From, void const volatile, e_false_v)
#	endif
#endif /* EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT */

#endif /* EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_convertible_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_CONVERTIBLE_H */
/* //////////////////////////////////////////////////////////////////// */
