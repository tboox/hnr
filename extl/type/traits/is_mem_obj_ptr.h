/* ///////////////////////////////////////////////////////////////////////
 * File:		is_mem_obj_ptr.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_mem_obj_ptr traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_H
#define EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_H

#ifndef EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_SUPPORT
#	error extl::is_mem_obj_ptr is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
#	include "is_mem_func_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#	include "is_mem_ptr.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_MEM_OBJ_PTR(type)			EXTL_MUST_BE_(is_mem_obj_ptr, type)
#define EXTL_MUST_BE_CV_MEM_OBJ_PTR(type)		EXTL_MUST_BE_CV_(is_mem_obj_ptr, type)

#define EXTL_MUST_NOT_BE_MEM_OBJ_PTR(type)		EXTL_MUST_NOT_BE_(is_mem_obj_ptr, type)
#define EXTL_MUST_NOT_BE_CV_MEM_OBJ_PTR(type)	EXTL_MUST_NOT_BE_CV_(is_mem_obj_ptr, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

template <typename_param_k T>
struct is_mem_obj_ptr_impl
{
   EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (op_and	<	(is_mem_ptr<T>::value) 
														,	(op_not< (is_mem_func_ptr<T>::value) >::value) 
														>::value ));
};
EXTL_BOOL_TRAIT_DEF_1(is_mem_obj_ptr,is_mem_obj_ptr_impl<T>::value)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef	EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_mem_obj_ptr_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
