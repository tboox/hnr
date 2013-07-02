/* ///////////////////////////////////////////////////////////////////////
 * File:		mem_func_ptr_traits_impl.h		
 *
 * Created:		08.07.20		
 * Updated:		08.07.20
 *
 * Brief: mem_func_ptr_traits implemention - use partial specialization
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_IMPL_H
#define EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_IMPL_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "_func_def.h"
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
// cdecl: function partial specialization
#define EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(num)											\
template<	typename_param_k C																\
		,	EXTL_FUNC_PARAM_T_##num>														\
struct mem_func_ptr_traits_impl<RT (C::*)(EXTL_FUNC_PARAM_##num)>							\
{																							\
	typedef C	container_type;																\
	EXTL_FUNC_PARAM_TYPE_DEF_##num															\
																							\
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = num);									\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_true_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_false_v);							\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_false_v);							\
};
// stdcall: function partial specialization
#define EXTL_MEM_FUNC_PTR_TRAITSSPEC_STDCALL(num)											\
template<	typename_param_k C																\
		,	EXTL_FUNC_PARAM_T_##num>														\
struct mem_func_ptr_traits_impl<RT (EXTL_STDCALL C::*)(EXTL_FUNC_PARAM_##num)>				\
{																							\
	typedef C	container_type;																\
	EXTL_FUNC_PARAM_TYPE_DEF_##num															\
																							\
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = num);									\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_true_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_false_v);							\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_false_v);							\
};
// fastcall: function partial specialization
#define EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(num)											\
template<	typename_param_k C																\
		,	EXTL_FUNC_PARAM_T_##num>														\
struct mem_func_ptr_traits_impl<RT (EXTL_FASTCALL C::*)(EXTL_FUNC_PARAM_##num)>				\
{																							\
	typedef C	container_type;																\
	EXTL_FUNC_PARAM_TYPE_DEF_##num															\
																							\
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = num);									\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_true_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_false_v);							\
};
// cdecl: function partial specialization with ...
#define EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(num)								\
template<	typename_param_k C																\
		,	EXTL_FUNC_PARAM_T_##num>														\
struct mem_func_ptr_traits_impl<RT (C::*)(EXTL_FUNC_PARAM_##num ...)>						\
{																							\
	typedef C	container_type;																\
	EXTL_FUNC_PARAM_TYPE_DEF_##num															\
																							\
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = num);									\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_true_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_false_v);							\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_true_v);							\
};
// stdcall: function partial specialization with ...
#define EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(num)							\
template<	typename_param_k C																\
		,	EXTL_FUNC_PARAM_T_##num>														\
struct mem_func_ptr_traits_impl<RT (EXTL_STDCALL C::*)(EXTL_FUNC_PARAM_##num ...)>			\
{																							\
	typedef C	container_type;																\
	EXTL_FUNC_PARAM_TYPE_DEF_##num															\
																							\
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = num);									\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_true_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_false_v);							\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_true_v);							\
};

// fastcall: function partial specialization with ...
#define EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(num)							\
template<	typename_param_k C																\
		,	EXTL_FUNC_PARAM_T_##num>														\
struct mem_func_ptr_traits_impl<RT (EXTL_FASTCALL C::*)(EXTL_FUNC_PARAM_##num ...)>			\
{																							\
	typedef C	container_type;																\
	EXTL_FUNC_PARAM_TYPE_DEF_##num															\
																							\
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = num);									\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_false_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_true_v);								\
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_true_v);							\
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k FP>
struct mem_func_ptr_traits_impl
{
	typedef e_null_t	container_type;
	typedef e_null_t	return_type;				
	typedef e_null_t	param1_type;				
	typedef e_null_t	param2_type;				
	typedef e_null_t	param3_type;				
	typedef e_null_t	param4_type;				
	typedef e_null_t	param5_type;				
	typedef e_null_t	param6_type;				
	typedef e_null_t	param7_type;				
	typedef e_null_t	param8_type;				
	typedef e_null_t	param9_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 0);									
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_cdecl = e_false_v);								
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_stdcall = e_false_v);								
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_fastcall = e_false_v);							
	EXTL_STATIC_MEMBER_CONST(e_bool_t, has_ellipsis = e_false_v);
};

EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(0)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(1)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(2)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(3)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(4)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(5)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(6)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(7)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(8)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL(9)

#ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(0)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(1)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(2)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(3)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(4)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(5)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(6)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(7)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(8)
EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS(9)
#endif

#if defined(EXTL_TEMPLATE_FUNC_PARTIAL_SPEC_WITH_CALL_CONV_SUPPORT) && \
		defined(EXTL_TEMPLATE_PARTIAL_SPEC_DISTINGUISH_DIFFERENT_FUNC_CALL_CONV_SUPPORT)

#	ifdef EXTL_STDCALL_SUPPORT
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(0)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(1)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(2)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(3)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(4)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(5)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(6)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(7)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(8)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL(9)

#		ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(0)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(1)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(2)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(3)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(4)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(5)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(6)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(7)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(8)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS(9)
#		endif /* EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT */
#	endif /* EXTL_STDCALL_SUPPORT */

#	ifdef EXTL_FASTCALL_SUPPORT
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(0)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(1)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(2)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(3)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(4)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(5)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(6)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(7)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(8)
	EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL(9)

#		ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(0)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(1)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(2)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(3)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(4)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(5)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(6)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(7)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(8)
		EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS(9)
#		endif /* EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT */
#	endif /* EXTL_FASTCALL_SUPPORT */

#endif/* defined(EXTL_TEMPLATE_FUNC_PARTIAL_SPEC_WITH_CALL_CONV_SUPPORT) && \
			defined(EXTL_TEMPLATE_PARTIAL_SPEC_DISTINGUISH_DIFFERENT_FUNC_CALL_CONV_SUPPORT) */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#undef EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL
#undef EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL
#undef EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL

#undef EXTL_MEM_FUNC_PTR_TRAITS_SPEC_CDECL_WITH_ELLIPSIS
#undef EXTL_MEM_FUNC_PTR_TRAITS_SPEC_STDCALL_WITH_ELLIPSIS
#undef EXTL_MEM_FUNC_PTR_TRAITS_SPEC_FASTCALL_WITH_ELLIPSIS
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "_func_undef.h"

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
