/* ///////////////////////////////////////////////////////////////////////
 * File:		is_mem_func_ptr_tester.h		
 *
 * Created:		08.02.10			
 * Updated:		08.07.13
 *
 * Brief: is_mem_func_ptr traits specialization test
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_TESTER_H
#define EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_TESTER_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

/* member function specialization */
#define EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC_(templatelist, arglist)	\
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (T::*)(arglist)); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (T::*)(arglist) const); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (T::*)(arglist) volatile); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (T::*)(arglist) volatile const); 
/* member function specialization with __cdecl */
#ifdef EXTL_CDECL_SUPPORT
#	define EXTL_IS_MEM_FUNC_PTR_TESTER_CDECL_SPEC_(templatelist, arglist)	\
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_CDECL T::*)(arglist)); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_CDECL T::*)(arglist) const); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_CDECL T::*)(arglist) volatile); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_CDECL T::*)(arglist) volatile const); 
#else
#	define EXTL_IS_MEM_FUNC_PTR_TESTER_CDECL_SPEC_(templatelist, arglist)
#endif

/* member function specialization with __fastcall */
#ifdef EXTL_FASTCALL_SUPPORT
#	define EXTL_IS_MEM_FUNC_PTR_TESTER_FASTCALL_SPEC_(templatelist, arglist)	\
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_FASTCALL T::*)(arglist)); \
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_FASTCALL T::*)(arglist) const); \
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_FASTCALL T::*)(arglist) volatile); \
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_FASTCALL T::*)(arglist) volatile const);
#else
#	define EXTL_IS_MEM_FUNC_PTR_TESTER_FASTCALL_SPEC_(templatelist, arglist)
#endif				

/* member function specialization with __stdcall */
#ifdef EXTL_STDCALL_SUPPORT
#	define EXTL_IS_MEM_FUNC_PTR_TESTER_STDCALL_SPEC_(templatelist, arglist)	\
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_STDCALL T::*)(arglist)); \
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_STDCALL T::*)(arglist) const); \
										template <templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_STDCALL  T::*)(arglist) volatile); \
										template < templatelist > \
										yes_type is_mem_func_ptr_tester(R (EXTL_STDCALL  T::*)(arglist) const volatile);
#else
#	define EXTL_IS_MEM_FUNC_PTR_TESTER_STDCALL_SPEC_(templatelist, arglist)
#endif

/* function parameter list */
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_0
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_1	T0
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_2	T0, T1
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_3	T0, T1, T2
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_4	T0, T1, T2, T3
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_5	T0, T1, T2, T3, T4
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_6	T0, T1, T2, T3, T4, T5
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_7	T0, T1, T2, T3, T4, T5, T6
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_8	T0, T1, T2, T3, T4, T5, T6, T7
#define EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_9	T0, T1, T2, T3, T4, T5, T6, T7, T8

/* template parameter list */
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_0	typename_param_k R, typename_param_k T
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_1	typename_param_k R, typename_param_k T, typename_param_k T0
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_2	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_3	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_4	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2, typename_param_k T3
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_5	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_6	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4, typename_param_k T5
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_7	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4, typename_param_k T5, typename_param_k T6
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_8	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4, typename_param_k T5, typename_param_k T6, typename_param_k T7
#define EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_9	typename_param_k R, typename_param_k T, typename_param_k T0, typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4, typename_param_k T5, typename_param_k T6, typename_param_k T7, typename_param_k T8

/* function specialization without ... */
#define EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(num)	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC_( \
												EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num , \
												EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num) \
												\
												EXTL_IS_MEM_FUNC_PTR_TESTER_CDECL_SPEC_( \
												EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num, \
												EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num)\
												\
												EXTL_IS_MEM_FUNC_PTR_TESTER_FASTCALL_SPEC_( \
												EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num, \
												EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num)\
												\
												EXTL_IS_MEM_FUNC_PTR_TESTER_STDCALL_SPEC_( \
												EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num, \
												EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num)
/* function specialization with ... */
#define EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(num)	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC_(  \
															EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num , \
															EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num ...)) \
															\
															EXTL_IS_MEM_FUNC_PTR_TESTER_CDECL_SPEC_( \
															EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num, \
															EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num ...)\
															\
															EXTL_IS_MEM_FUNC_PTR_TESTER_FASTCALL_SPEC_( \
															EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num, \
															EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num ...)\
															\
															EXTL_IS_MEM_FUNC_PTR_TESTER_STDCALL_SPEC_( \
															EXTL_IS_MEM_FUNC_PTR_TESTER_TEMPLATE_ARGLIST_##num, \
															EXTL_IS_MEM_FUNC_PTR_TESTER_ARGLIST_##num ...)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */

	EXTL_INLINE no_type EXTL_CDECL is_mem_func_ptr_tester(...);

	/* function specialization without ... */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(0) /* 0 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(1) /* 1 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(2) /* 2 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(3) /* 3 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(4) /* 4 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(5) /* 5 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(6) /* 6 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(7) /* 7 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(8) /* 8 params */

	/* VC 6.0 only support 8 params in default case (please use /Zm option) */
#	if !defined(EXTL_COMPILER_IS_MSVC) || (_MSC_VER > 1200)
	EXTL_IS_MEM_FUNC_PTR_TESTER_SPEC(9) /* 9 params */
#	endif

	/* function specialization with ... */
#	ifdef EXTL_ELLIPSIS_IN_MEM_FUNC_TESTING_SUPPORT	

	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(0) /* 0 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(1) /* 1 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(2) /* 2 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(3) /* 3 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(4) /* 4 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(5) /* 5 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(6) /* 6 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(7) /* 7 params */
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(8) /* 8 params */

#	if !defined(EXTL_COMPILER_IS_MSVC) || (_MSC_VER > 1200)
	EXTL_IS_MEM_FUNC_PTR_TESTER_WITH_ELLIPSIS_SPEC(9) /* 9 params */
#	endif

#	endif

#endif	/* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_TESTER_H */
/* //////////////////////////////////////////////////////////////////// */
