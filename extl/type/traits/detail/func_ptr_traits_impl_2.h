/* ///////////////////////////////////////////////////////////////////////
 * File:		func_ptr_traits_impl_2.h		
 *
 * Created:		08.07.18	
 * Updated:		08.07.18
 *
 * Brief: func_ptr_traits implemention - use type buffer
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_IMPL_2_H
#define EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_IMPL_2_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "_func_def.h"

// Only supported at VC 6.0, 7.0 and 7.1
#include "detail/type_buffer.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
// cdecl: function specialization
#define EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(num)							\
template <EXTL_FUNC_PARAM_T_##num>										\
static save_type<	func_ptr_wrap_	<	e_false_v						\
									,	e_true_v						\
									,	e_false_v						\
									,	e_false_v						\
									,	num								\
									,	EXTL_FUNC_PARAM_WITH_RET_##num	\
									>									\
				,	ID													\
				> test(RT (*)(EXTL_FUNC_PARAM_##num));

// stdcall: function specialization
#define EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(num)							\
template <EXTL_FUNC_PARAM_T_##num>										\
static save_type<	func_ptr_wrap_	<	e_false_v						\
									,	e_false_v						\
									,	e_true_v						\
									,	e_false_v						\
									,	num								\
									,	EXTL_FUNC_PARAM_WITH_RET_##num	\
									>									\
				,	ID													\
				> test(RT (EXTL_STDCALL*)(EXTL_FUNC_PARAM_##num));

// fastcall: function specialization
#define EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(num)							\
template <EXTL_FUNC_PARAM_T_##num>										\
static save_type<	func_ptr_wrap_	<	e_false_v						\
									,	e_false_v						\
									,	e_false_v						\
									,	e_true_v						\
									,	num								\
									,	EXTL_FUNC_PARAM_WITH_RET_##num	\
									>									\
				,	ID													\
				> test(RT (EXTL_FASTCALL*)(EXTL_FUNC_PARAM_##num));

// cdecl: function specialization with ...
#define EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(num)				\
template <EXTL_FUNC_PARAM_T_##num>										\
static save_type<	func_ptr_wrap_	<	e_false_v						\
									,	e_true_v						\
									,	e_false_v						\
									,	e_false_v						\
									,	num								\
									,	EXTL_FUNC_PARAM_WITH_RET_##num	\
									>									\
				,	ID													\
				> test(RT (*)(EXTL_FUNC_PARAM_##num ...));

// stdcall: function specialization with ...
#define EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(num)			\
template <EXTL_FUNC_PARAM_T_##num>										\
static save_type<	func_ptr_wrap_	<	e_false_v						\
									,	e_false_v						\
									,	e_true_v						\
									,	e_false_v						\
									,	num								\
									,	EXTL_FUNC_PARAM_WITH_RET_##num	\
									>									\
				,	ID													\
				> test(RT (EXTL_STDCALL*)(EXTL_FUNC_PARAM_##num ...));

// fastcall: function specialization with ...
#define EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(num)			\
template <EXTL_FUNC_PARAM_T_##num>										\
static save_type<	func_ptr_wrap_	<	e_false_v						\
									,	e_false_v						\
									,	e_false_v						\
									,	e_true_v						\
									,	num								\
									,	EXTL_FUNC_PARAM_WITH_RET_##num	\
									>									\
				,	ID													\
				> test(RT (EXTL_FASTCALL*)(EXTL_FUNC_PARAM_##num ...));
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	e_bool_t has_ellipsis_		= e_false_v
		,	e_bool_t is_cdecl_			= e_false_v
		,	e_bool_t is_stdcall_		= e_false_v
		,	e_bool_t is_fastcall_		= e_false_v
		,	e_size_t param_num_			= 0
		,	typename_param_k RT			= e_null_t
		,	typename_param_k P1			= e_null_t
		,	typename_param_k P2			= e_null_t
		,	typename_param_k P3			= e_null_t
		,	typename_param_k P4			= e_null_t
		,	typename_param_k P5			= e_null_t
		,	typename_param_k P6			= e_null_t
		,	typename_param_k P7			= e_null_t
		,	typename_param_k P8			= e_null_t
		,	typename_param_k P9			= e_null_t
		>
struct func_ptr_wrap_
{
	EXTL_FUNC_PARAM_TYPE_DEF_9

	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = param_num_);
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = is_cdecl_);								
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = is_stdcall_);								
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = is_fastcall_);								
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = has_ellipsis_);
};

template< typename_param_k FP, typename_param_k ID >
struct func_ptr_traits_impl_tester
{
	static save_type<func_ptr_wrap_<>, ID> test(...);

	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(0)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(1)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(2)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(3)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(4)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(5)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(6)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(7)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(8)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL(9)

#ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(0)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(1)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(2)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(3)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(4)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(5)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(6)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(7)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(8)
	EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(9)
#endif

#ifdef EXTL_STDCALL_SUPPORT
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(0)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(1)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(2)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(3)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(4)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(5)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(6)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(7)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(8)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL(9)

#	ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(0)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(1)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(2)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(3)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(4)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(5)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(6)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(7)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(8)
	EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(9)
#	endif /* EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT */
#endif /* EXTL_STDCALL_SUPPORT */

#ifdef EXTL_FASTCALL_SUPPORT
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(0)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(1)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(2)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(3)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(4)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(5)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(6)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(7)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(8)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL(9)

#	ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(0)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(1)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(2)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(3)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(4)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(5)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(6)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(7)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(8)
	EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(9)
#	endif /* EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT */
#endif /* EXTL_FASTCALL_SUPPORT */

	static FP fp;
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = sizeof( test(fp) )); 
	typedef typename_type_k type_buffer<ID>::result::type type;
};

template<typename_param_k FP>
struct func_ptr_traits_impl 
	: func_ptr_traits_impl_tester<FP, func_ptr_traits_impl<FP> >::type
{
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#undef EXTL_FUNC_PTR_TRAITS_SPEC_CDECL
#undef EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL
#undef EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL

#undef EXTL_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS
#undef EXTL_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS
#undef EXTL_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "_func_undef.h"

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_IMPL_2_H */
/* //////////////////////////////////////////////////////////////////// */
