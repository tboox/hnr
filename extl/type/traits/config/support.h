/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Type Traits Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_CONFIG_SUPPORT_H
#define EXTL_TYPE_TRAITS_CONFIG_SUPPORT_H

#ifndef EXTL_TYPE_TRAITS_CONFIG_H
#	error This file must be included of extl\type\traits\config\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_TYPE_TRAITS_SUPPORT
#	undef EXTL_TYPE_TRAITS_SUPPORT
#endif

#if defined(__cplusplus) && \
	defined(EXTL_TEMPLATE_SUPPORT) && \
		defined(EXTL_TEMPLATE_SPEC_SUPPORT)
#	define EXTL_TYPE_TRAITS_SUPPORT
#endif

/* is_ref */
#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		!EXTL_WORKAROUND_WATCOM(<, 0x1270) 
#	define EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#endif

/* is_array */
#ifdef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#endif

#ifndef EXTL_COMPILER_IS_WATCOM
#	define EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT
#endif

/* is_same */
#ifdef EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)
#	define EXTL_TYPE_TRAITS_IS_SAME_SUPPORT
#endif

/* if_ */
#ifdef EXTL_TYPE_TRAITS_IF_SUPPORT
#	undef EXTL_TYPE_TRAITS_IF_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT)
#	define EXTL_TYPE_TRAITS_IF_SUPPORT
#endif

/* promotion_traits */
#ifdef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
#	undef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IF_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_IS_SAME_SUPPORT)
#	define EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
#endif

/* type_buffer
 * eg: only support VC 6.0,7.0,7.1
 */
#ifdef EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT
#	undef EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1300)
#	define EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT
#endif

/* remove_ref */
#ifdef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#endif

/* remove_ptr */
#ifdef EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT
#endif

/* remove_bound */
#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#endif

#if (defined(EXTL_TEMPLATE_PARTIAL_SPEC_ARRAY_TYPE_SUPPORT) && !defined(EXTL_COMPILER_IS_VECTORC)) || \
			(defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT) && defined(EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT))
#	define EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#endif

/* remove_bounds */
#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_BOUND_SUPPORT
#	define EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT
#endif

/* remove_const */
#ifdef EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT
#endif

/* remove_volatile */
#ifdef EXTL_TYPE_TRAITS_REMOVE_VOLATILE_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_VOLATILE_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_REMOVE_VOLATILE_SUPPORT
#endif

/* remove_cv */
#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	undef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#endif

/* is_func_ptr */
#ifdef EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT
#endif

#if !defined(EXTL_COMPILER_IS_WATCOM)
#	define EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT
#endif

/* is_func */
#ifdef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_FUNC_PTR_SUPPORT) || \
			!defined(EXTL_COMPILER_IS_WATCOM)
#	define EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT
#endif

/* is_mem_func_ptr */
#ifdef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
#endif

#if !defined(EXTL_COMPILER_IS_BORLAND) && \
		!defined(EXTL_COMPILER_IS_WATCOM) && \
			!defined(EXTL_COMPILER_IS_VECTORC) /* 暂时不 */
#	define EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT
#endif

/* is_mem_ptr */
#ifdef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#endif

#if !defined(EXTL_COMPILER_IS_WATCOM)
#	define EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#endif

/* is_mem_obj_ptr */
#ifdef EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_MEM_FUNC_PTR_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT)
#	define EXTL_TYPE_TRAITS_IS_MEM_OBJ_PTR_SUPPORT
#endif
 
/* is_mem_ptr */
#ifdef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#endif

#if !defined(EXTL_COMPILER_IS_WATCOM)
#	define EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT
#endif

/* is_obj */
#ifdef EXTL_TYPE_TRAITS_IS_OBJ_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_OBJ_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_FUNC_SUPPORT)
#	define EXTL_TYPE_TRAITS_IS_OBJ_SUPPORT
#endif

/* is_ptr */
#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#endif

/* is_const */
#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#endif

/* is_volatile */
#ifdef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT
#endif

/* is_cv */
#ifdef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_CONST_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_VOLATILE_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_CV_SUPPORT
#endif

/* is_scalar */
#ifdef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_PTR_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_MEM_PTR_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT
#endif

/* is_union */
#ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#endif

#ifdef EXTL_IS_UNION_
#	undef EXTL_IS_UNION_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#	define EXTL_IS_UNION_(T)	__is_union(T)
#endif

/* is_class */
#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#endif

#ifdef EXTL_TYPE_TRAITS_IS_UNION_SUPPORT
#	define EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#endif

/* is_class_or_union */
#ifdef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT
#endif

#if !(defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER <= 1200) && \
		!defined(EXTL_COMPILER_IS_BORLAND) && \
			!defined(EXTL_COMPILER_IS_VECTORC) && \
				!defined(EXTL_COMPILER_IS_WATCOM) 
#	define EXTL_TYPE_TRAITS_IS_CLASS_OR_UNION_SUPPORT
#endif

/* is_abstract */
#ifdef EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	define EXTL_TYPE_TRAITS_IS_ABSTRACT_SUPPORT
#endif

/* is_polymorphic */
#ifdef EXTL_TYPE_TRAITS_IS_POLYMORPHIC_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_POLYMORPHIC_SUPPORT
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	define EXTL_TYPE_TRAITS_IS_POLYMORPHIC_SUPPORT
#endif

/* is_empty */
#ifdef EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT
#endif

#ifdef EXTL_IS_EMPTY_
#	undef EXTL_IS_EMPTY_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_IS_EMPTY_(T)	__is_empty(T)
#endif

#if defined(EXTL_IS_EMPTY_) && \
		defined(EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_EMPTY_SUPPORT
#endif

/* is_pod */
#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#endif

#ifdef EXTL_IS_POD_
#	undef EXTL_IS_POD_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_IS_POD_(T)	__is_pod(T)
#endif

#if	defined(EXTL_IS_POD_) && \
		defined(EXTL_TYPE_TRAITS_REMOVE_BOUNDS_SUPPORT)
#	define EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#endif

/* is_convertible  */
#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_BORLAND) /* 暂时不 */
#	define EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#endif

/* is_enum  */
#ifdef EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
#	undef EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_IS_ARRAY_SUPPORT) && \
				defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) 
#	define EXTL_TYPE_TRAITS_IS_ENUM_SUPPORT
#endif

/* add_ref */
#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	undef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
		( defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) )
#	define EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#endif

/* add_const */
#ifdef EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#	undef EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
		( defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) )
#	define EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#endif

/* add_const_ref */
#ifdef EXTL_TYPE_TRAITS_ADD_CONST_REF__SUPPORT
#	undef EXTL_TYPE_TRAITS_ADD_CONST_REF__SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_ADD_REF_SUPPORT) 
#	define EXTL_TYPE_TRAITS_ADD_CONST_REF_SUPPORT
#endif

/* add_volatile */
#ifdef EXTL_TYPE_TRAITS_ADD_VOLATILE_SUPPORT
#	undef EXTL_TYPE_TRAITS_ADD_VOLATILE_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
		( defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) )
#	define EXTL_TYPE_TRAITS_ADD_VOLATILE_SUPPORT
#endif

/* add_cv */
#ifdef EXTL_TYPE_TRAITS_ADD_CV_SUPPORT
#	undef EXTL_TYPE_TRAITS_ADD_CV_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
		( defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) )
#	define EXTL_TYPE_TRAITS_ADD_CV_SUPPORT
#endif

/* add_ptr */
#ifdef EXTL_TYPE_TRAITS_ADD_PTR_SUPPORT
#	undef EXTL_TYPE_TRAITS_ADD_PTR_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT) || \
		( defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
			defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) )
#	define EXTL_TYPE_TRAITS_ADD_PTR_SUPPORT
#endif

/* has_trivial_constructor */
#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_CONSTRUCTOR_SUPPORT
#	undef EXTL_TYPE_TRAITS_HAS_TRIVIAL_CONSTRUCTOR_SUPPORT
#endif

#ifdef EXTL_HAS_TRIVIAL_CONSTRUCTOR_
#	undef EXTL_HAS_TRIVIAL_CONSTRUCTOR_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_HAS_TRIVIAL_CONSTRUCTOR_(T)	__has_trivial_constructor(T)
#endif

#if	defined(EXTL_HAS_TRIVIAL_CONSTRUCTOR_) && \
		defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
#	define EXTL_TYPE_TRAITS_HAS_TRIVIAL_CONSTRUCTOR_SUPPORT
#endif

/* has_trivial_destructor */
#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_SUPPORT
#	undef EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_SUPPORT
#endif

#ifdef EXTL_HAS_TRIVIAL_DESTRUCTOR_
#	undef EXTL_HAS_TRIVIAL_DESTRUCTOR_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_HAS_TRIVIAL_DESTRUCTOR_(T)	__has_trivial_destructor(T)
#endif

#if	defined(EXTL_HAS_TRIVIAL_DESTRUCTOR_) && \
		defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
#	define EXTL_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_SUPPORT
#endif

/* has_virtual_destructor */
#ifdef EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_SUPPORT
#	undef EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_SUPPORT
#endif

#ifdef EXTL_HAS_VIRTUAL_DESTRUCTOR_
#	undef EXTL_HAS_VIRTUAL_DESTRUCTOR_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_HAS_VIRTUAL_DESTRUCTOR_(T)	__has_virtual_destructor(T)
#endif

#if	defined(EXTL_HAS_VIRTUAL_DESTRUCTOR_)
#	define EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_SUPPORT
#endif

/* has_trivial_copy */
#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPY_SUPPORT
#	undef EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPY_SUPPORT
#endif

#ifdef EXTL_HAS_TRIVIAL_COPY_
#	undef EXTL_HAS_TRIVIAL_COPY_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_HAS_TRIVIAL_COPY_(T)	__has_trivial_copy(T)
#endif

#if	defined(EXTL_HAS_TRIVIAL_COPY_) && \
		defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
#	define EXTL_TYPE_TRAITS_HAS_TRIVIAL_COPY_SUPPORT
#endif

/* has_trivial_assign */
#ifdef EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGN_SUPPORT
#	undef EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGN_SUPPORT
#endif

#ifdef EXTL_HAS_TRIVIAL_ASSIGN_
#	undef EXTL_HAS_TRIVIAL_ASSIGN_
#endif

#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER > 1310
#	define EXTL_HAS_TRIVIAL_ASSIGN_(T)	__has_trivial_assign(T)
#endif

#if	defined(EXTL_HAS_TRIVIAL_ASSIGN_) && \
		defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
#	define EXTL_TYPE_TRAITS_HAS_TRIVIAL_ASSIGN_SUPPORT
#endif

/* func_ptr_traits */
#ifdef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_SUPPORT
#	undef EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_FUNC_PTR_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_FUNC_PTR_TRAITS_SUPPORT
#endif

/* mem_func_ptr_traits */
#ifdef EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_SUPPORT
#	undef EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_SUPPORT
#endif

#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_MEM_FUNC_PTR_SUPPORT) || \
		defined(EXTL_TYPE_TRAITS_TYPE_BUFFER_SUPPORT)
#	define EXTL_TYPE_TRAITS_MEM_FUNC_PTR_TRAITS_SUPPORT
#endif

/* call_traits */
#ifdef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	undef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#endif

#if defined(EXTL_TYPE_TRAITS_ADD_CONST_REF_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_ADD_REF_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_REMOVE_CONST_SUPPORT)
#	define EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_TRAITS_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
