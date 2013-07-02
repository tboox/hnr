/* ///////////////////////////////////////////////////////////////////////
 * File:		traits.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.29
 *
 * Brief: The type traits library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_H
#define EXTL_TYPE_TRAITS_H

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility:
 *
 * The following type traits will not be supported well 
 * if the partial specialization isn't supported:
 *
 * - remove_bounds£ºOnly the trait be supported at VC 6.0, 7.0, 7.1 if the partial specialization isn't supported
 *
 * The traits which cannot be compiled at some compilers normally
 * - is_mem_func_ptr:	The traits need use type definition when the function pointer type is passed at Borland 5.5
 * - is_mem_obj_ptr:	The traits need use type definition when the function pointer type is passed at Borland 5.5
 * - is_const:			Some types cannot be used at same time at Digital Mars, see also is_const_test.h
 * - is_volatile:		Some types cannot be used at same time at Digital Mars, see also is_volatile_test.h
 *
 * The traits which cannot be supported by some compilers
 * - is_union:			It only is supported at VC 8.0,9.0
 * - is_class:			It only is supported at VC 8.0,9.0 because of is_union
 * - is_pod:			It only is supported at VC 8.0,9.0 because of remove_bounds
 * - is_abstract:		It only is supported at VC 8.0,9.0 because of is_class
 * - is_empty:			It only is supported at VC 8.0,9.0 because of is_class
 * - is_polymorphic:	It only is supported at VC 8.0,9.0 because of is_class
 * - has_trivial_constructor:	It only is supported at VC 8.0,9.0 because of is_pod
 * - has_trivial_destructor:	It only is supported at VC 8.0,9.0 because of is_pod
 * - has_virtual_destructor:	It only is supported at VC 8.0,9.0 because of is_pod
 * - has_trivial_copy:			It only is supported at VC 8.0,9.0 because of is_pod
 * - has_trivial_assign:		It only is supported at VC 8.0,9.0 because of is_pod
 *
 * Only the following traits are supported at Watcom 12.0
 *
 * - logical_op
 * - limit_traits 
 * - is_void 
 * - is_int 
 * - is_float
 * - is_arithmetic 
 * - is_signed 
 * - is_unsigned 
 *
 * Only the following traits are supported at Watcom 1.7
 *
 * - logical_op
 * - limit_traits 
 * - is_void 
 * - is_int 
 * - is_float
 * - is_arithmetic 
 * - is_signed 
 * - is_unsigned 
 *
 * - is_ref 
 * - is_same 
 *
 * //////////////////////////////////////////////////////////////////// */

#ifndef __cplusplus
#	error traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "logical_op.h"
#include "limit_traits.h"
#include "is_void.h"
#include "is_int.h"
#include "is_float.h"
#include "is_arithmetic.h"
#include "is_fundamental.h"
#include "is_compound.h"

#ifdef EXTL_TYPE_TRAITS_IF_SUPPORT
#	include "if_.h"
#endif

#ifdef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
#	include "promotion_traits.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "is_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	include "is_array.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#	include "is_same.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT
#	include "is_func_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#	include "is_func.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
#	include "is_mem_func_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#	include "is_mem_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_SUPPORT
#	include "is_mem_obj_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_OBJ_SUPPORT
#	include "is_obj.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	include "is_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#	include "is_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#	include "is_volatile.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#	include "is_cv.h"
#endif

#include "is_signed.h"
#include "is_unsigned.h"

#ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#	include "is_union.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	include "is_class.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT
#	include "is_class_or_union.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
#	include "is_abstract.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_POLYMORPHIC_SUPPORT
#	include "is_polymorphic.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT
#	include "is_empty.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	include "is_scalar.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "is_pod.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#	include "is_convertible.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
#	include "is_enum.h"
#endif

#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_CONSTRUCTOR_SUPPORT
#	include "has_trivial_constructor.h"
#endif

#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_SUPPORT
#	include "has_trivial_destructor.h"
#endif

#ifdef EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_SUPPORT
#	include "has_virtual_destructor.h"
#endif

#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPY_SUPPORT
#	include "has_trivial_copy.h"
#endif

#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGN_SUPPORT
#	include "has_trivial_assign.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	include "add_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#	include "add_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CONST_REF_SUPPORT
#	include "add_const_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_VOLATILE_SUPPORT
#	include "add_volatile.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CV_SUPPORT
#	include "add_cv.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_PTR_SUPPORT
#	include "add_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#	include "remove_bound.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT
#	include "remove_bounds.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#	include "remove_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT
#	include "remove_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT
#	include "remove_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_VOLATILE_SUPPORT
#	include "remove_volatile.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "remove_cv.h"
#endif

#ifdef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_SUPPORT
#	include "func_ptr_traits.h"
#endif

#ifdef EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_SUPPORT
#	include "mem_func_ptr_traits.h"
#endif

#ifdef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	include "call_traits.h"
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
