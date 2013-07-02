/* ///////////////////////////////////////////////////////////////////////
 * File:		prefix.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: The prefix file of the type traits library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_PREFIX_H
#define EXTL_TYPE_TRAITS_PREFIX_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../../prefix.h"
#include "../yes_no.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

// EXTL_MUST_BE_... and EXTL_MUST_NOT_BE_...
#ifdef EXTL_TYPE_TRAITS_SUPPORT
#	define EXTL_MUST_BE_(trait, type)		\
				EXTL_STATIC_ASSERT((EXTL_NS(trait)< type >::value))
#	define EXTL_MUST_NOT_BE_(trait, type)	\
				EXTL_STATIC_ASSERT((0 == (EXTL_NS(trait)< type >::value)))
#else
#	define EXTL_MUST_BE_(trait, type)		((void)0)
#	define EXTL_MUST_NOT_BE_(trait, type)	((void)0)
#endif

#ifdef EXTL_TYPE_TRAITS_SUPPORT
#	define EXTL_MUST_BE_2_(trait, type1, type2)		\
			EXTL_STATIC_ASSERT((EXTL_NS(trait)< type1, type2 >::value))
#	define EXTL_MUST_NOT_BE_2_(trait, type1, type2)	\
			EXTL_STATIC_ASSERT((0 == (EXTL_NS(trait)< type1, type2 >::value)))
#else
#	define EXTL_MUST_BE_2(trait, type1, type2)		((void)0)
#	define EXTL_MUST_NOT_BE_2(trait, type1, type2)	((void)0)
#endif

// EXTL_MODIFY_TYPE
// e.g. #define EXTL_REMOVE_PTR(src_type)	EXTL_MODIFY_TYPE(remove_ptr, src_type)
#ifdef EXTL_TYPE_TRAITS_SUPPORT
#	ifdef EXTL_COMPILER_IS_BORLAND
#		define EXTL_MODIFY_TYPE(trait, src_type)		\
					EXTL_NS(trait)< src_type >::type
#	else
#		define EXTL_MODIFY_TYPE(trait, src_type)		\
					EXTL_NS(trait)< src_type >::type
#	endif
#else
#	define EXTL_MODIFY_TYPE(trait, src_type)	((void)0)
#	define EXTL_MODIFY_TYPE(trait, src_type)	((void)0)
#endif

// EXTL_MUST_BE_... with cv-qualified
#define EXTL_MUST_BE_CV_(trait, type)	EXTL_MUST_BE_(trait, type); \
										EXTL_MUST_BE_(trait, const type); \
										EXTL_MUST_BE_(trait, volatile type); \
										EXTL_MUST_BE_(trait, const volatile type)

#define EXTL_MUST_NOT_BE_CV_(trait, type)	EXTL_MUST_NOT_BE_(trait, type); \
											EXTL_MUST_NOT_BE_(trait, const type); \
											EXTL_MUST_NOT_BE_(trait, volatile type); \
											EXTL_MUST_NOT_BE_(trait, const volatile type)

#define EXTL_MUST_BE_CV_2_(trait, type1, type2)	EXTL_MUST_BE_2_(trait, type1, type2); \
												EXTL_MUST_BE_2_(trait, const type1, const type2); \
												EXTL_MUST_BE_2_(trait, volatile type1, volatile type2); \
												EXTL_MUST_BE_2_(trait, const volatile type1, const volatile type2)

#define EXTL_MUST_NOT_BE_CV_2_(trait, type1, type2)	EXTL_MUST_NOT_BE_2_(trait, type1, type2); \
													EXTL_MUST_NOT_BE_2_(trait, const type1, const type2); \
													EXTL_MUST_NOT_BE_2_(trait, volatile type1, volatile type2); \
													EXTL_MUST_NOT_BE_2_(trait, const volatile type1, const volatile type2)


/* ///////////////////////////////////////////////////////////////////////
 * helpful macros about bool type traits 
 */

// Type traits definition: < typename T > 
#define EXTL_BOOL_TRAIT_DEF_1(trait, V)	\
		template < typename_param_k T > \
		struct trait \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits specialization: < spec_T > 
#define EXTL_BOOL_TRAIT_SPEC_1(trait, spec_T, V)	\
		EXTL_TEMPLATE_SPECIALISATION \
		struct trait< spec_T > \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits specialization: < spec_T1, spec_T2 > 
#define EXTL_BOOL_TRAIT_SPEC_2(trait, spec_T1, spec_T2, V)	\
		EXTL_TEMPLATE_SPECIALISATION \
		struct trait< spec_T1, spec_T2 > \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits partial specialization: < spec_T >(include: param1) 
#define EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_1(param1, trait, spec_T, V)	\
		template < param1 > \
		struct trait< spec_T > \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits partial specialization: < spec_T >(include: param1,param2) 
#define EXTL_BOOL_TRAIT_PARTIAL_SPEC_1_2(param1, param2, trait, spec_T, V)	\
		template < param1 ,param2 > \
		struct trait< spec_T > \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits definition: < typename T1, typename T2 > 
#define EXTL_BOOL_TRAIT_DEF_2(trait, V)	\
		template < typename_param_k T1, typename_param_k T2 > \
		struct trait \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits partial specialization: < spec_T1, spec_T2 >(include: param1) 
#define EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_1(param1, trait, spec_T1, spec_T2, V)	\
		template < param1 > \
		struct trait< spec_T1, spec_T2 > \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 

// Type traits partial specialization: < spec_T1, spec_T2 >(include: param1, param2) 
#define EXTL_BOOL_TRAIT_PARTIAL_SPEC_2_2(param1, param2, trait, spec_T1, spec_T2, V)	\
		template < param1, param2 > \
		struct trait< spec_T1, spec_T2 > \
		{ \
			EXTL_STATIC_MEMBER_CONST(e_bool_t, value = V); \
		}; 


// Type traits specialization with cv-qualified
// note: spec_T cannot be void */
#ifdef EXTL_CV_SPEC_SUPPORT	
#	define EXTL_BOOL_TRAIT_CV_SPEC_1(trait, spec_T, V)	\
			EXTL_BOOL_TRAIT_SPEC_1(trait, spec_T, V) \
			EXTL_BOOL_TRAIT_SPEC_1(trait, const spec_T, V) \
			EXTL_BOOL_TRAIT_SPEC_1(trait, volatile spec_T, V) \
			EXTL_BOOL_TRAIT_SPEC_1(trait, const volatile spec_T, V) 
#else
#	define EXTL_BOOL_TRAIT_CV_SPEC_1(trait, spec_T, V)	\
			EXTL_BOOL_TRAIT_SPEC_1(trait, spec_T, V) 
#endif

/* ///////////////////////////////////////////////////////////////////////
 * helpful macros about type definition
 */

// Type definition: < typename T > 
#define EXTL_TYPE_TRAIT_DEF_1(trait, ResultT)	\
		template < typename_param_k T > \
		struct trait \
		{ \
			typedef ResultT type; \
		}; 

// Type specialization: < spec_T > 
#define EXTL_TYPE_TRAIT_SPEC_1(trait, spec_T, ResultT)	\
		EXTL_TEMPLATE_SPECIALISATION \
		struct trait< spec_T > \
		{ \
			typedef ResultT type; \
		}; 

// Type specialization: < spec_T1, spec_T2 > 
#define EXTL_TYPE_TRAIT_SPEC_2(trait, spec_T1, spec_T2, ResultT)	\
		EXTL_TEMPLATE_SPECIALISATION \
		struct trait< spec_T1, spec_T2 > \
		{ \
			typedef ResultT type; \
		}; 

// Type partial specialization: < spec_T >(include: param1) 
#define EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_1(param1, trait, spec_T, ResultT)	\
		template < param1 > \
		struct trait< spec_T > \
		{ \
			typedef ResultT type; \
		}; 

// Type partial specialization: < spec_T1, spec_T2 >(include: param1) 
#define EXTL_TYPE_TRAIT_PARTIAL_SPEC_2_1(param1, trait, spec_T1, spec_T2, ResultT)	\
		template < param1 > \
		struct trait< spec_T1, spec_T2 > \
		{ \
			typedef ResultT type; \
		}; 

// Type partial specialization: < spec_T >(include: param1,param2) 
// note: ResultT != T[N] 
#define EXTL_TYPE_TRAIT_PARTIAL_SPEC_1_2(param1, param2, trait, spec_T, ResultT)	\
		template < param1 ,param2 > \
		struct trait< spec_T > \
		{ \
			typedef ResultT type; \
		}; 

// Type partial specialization about array: < spec_T >(include: param1,param 2)
// note: ResultT == T type[N] 
#define EXTL_TYPE_TRAIT_PARTIAL_SPEC_TO_ARRAY_1_2(param1, param2, trait, spec_T, ResultT)	\
		template < param1 ,param2 > \
		struct trait< spec_T > \
		{ \
			typedef ResultT; \
		}; 


/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_PREFIX_H */
/* //////////////////////////////////////////////////////////////////// */
