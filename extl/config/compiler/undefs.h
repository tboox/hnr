/* ///////////////////////////////////////////////////////////////////////
 * File:		undefs.h		
 *
 * Created:		08.02.02				
 * Updated:		08.04.14
 *
 * Brief: undefine compiler marco
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef  EXTL_CONFIG_COMPILER_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Workaround
 */
#ifdef EXTL_WORKAROUND_BORLAND
#	undef EXTL_WORKAROUND_BORLAND	
#endif

#ifdef EXTL_WORKAROUND_INTEL
#	undef EXTL_WORKAROUND_INTEL	
#endif

#ifdef EXTL_WORKAROUND_GCC
#	undef EXTL_WORKAROUND_GCC	
#endif

#ifdef EXTL_WORKAROUND_GCC_MINOR
#	undef EXTL_WORKAROUND_GCC_MINOR	
#endif

#ifdef EXTL_WORKAROUND_MSVC
#	undef EXTL_WORKAROUND_MSVC	
#endif

#ifdef EXTL_WORKAROUND_DMC
#	undef EXTL_WORKAROUND_DMC	
#endif

#ifdef EXTL_WORKAROUND_WATCOM
#	undef EXTL_WORKAROUND_WATCOM	
#endif

#ifdef EXTL_WORKAROUND_VECTORC
#	undef EXTL_WORKAROUND_VECTORC	
#endif

#define EXTL_WORKAROUND_BORLAND(cmp, ver)	(0)
#define EXTL_WORKAROUND_INTEL(cmp, ver)		(0)
#define EXTL_WORKAROUND_GCC(cmp, ver)		(0)
#define EXTL_WORKAROUND_GCC_MINOR(cmp, ver)	(0)
#define EXTL_WORKAROUND_MSVC(cmp, ver)		(0)
#define EXTL_WORKAROUND_DMC(cmp, ver)		(0)
#define EXTL_WORKAROUND_WATCOM(cmp, ver)	(0)
#define EXTL_WORKAROUND_VECTORC(cmp, ver)	(0)
/* ///////////////////////////////////////////////////////////////////////
 * Interger 
 */

/* 8-bit */
#ifdef EXTL_8BIT_INT_SUPPORT
#	undef EXTL_8BIT_INT_SUPPORT
#endif 

#ifdef EXTL_SI08_BASE_TYPE
#	undef EXTL_SI08_T_BASE_TYPE
#endif 

#ifdef EXTL_UI08_BASE_TYPE
#	undef EXTL_UI08_BASE_TYPE
#endif 

#ifdef EXTL_08BIT_INT_IS___int8
#	undef EXTL_08BIT_INT_IS___int8
#endif 

/* 16-bit */
#ifdef EXTL_16BIT_INT_SUPPORT
#	undef EXTL_16BIT_INT_SUPPORT
#endif 

#ifdef EXTL_SI16_BASE_TYPE
#	undef EXTL_SI16_BASE_TYPE
#endif
#ifdef EXTL_UI16_BASE_TYPE
#	undef EXTL_UI16_BASE_TYPE
#endif 

#ifdef EXTL_16BIT_INT_IS___int16
#	undef EXTL_16BIT_INT_IS___int16
#endif 

/* 32-bit */
#ifdef EXTL_32BIT_INT_SUPPORT
#	undef EXTL_32BIT_INT_SUPPORT
#endif 

#ifdef EXTL_SI32_BASE_TYPE
#	undef EXTL_SI32_BASE_TYPE
#endif 
#ifdef EXTL_UI32_BASE_TYPE
#	undef EXTL_UI32_BASE_TYPE
#endif 

#ifdef EXTL_32BIT_INT_IS___int32
#	undef EXTL_32BIT_INT_IS___int32
#endif 

/* 64-bit */
#ifdef EXTL_64BIT_INT_SUPPORT
#	undef EXTL_64BIT_INT_SUPPORT
#endif 

#ifdef EXTL_SI64_BASE_TYPE
#	undef EXTL_SI64_BASE_TYPE
#endif

#ifdef EXTL_UI64_BASE_TYPE
#	undef EXTL_UI64_BASE_TYPE
#endif

#ifdef EXTL_64BIT_INT_IS___int64
#	undef EXTL_64BIT_INT_IS___int64
#endif 

#ifdef EXTL_64BIT_INT_IS_long_long
#	undef EXTL_64BIT_INT_IS_long_long
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * Class member constants support
 */
#ifdef EXTL_MEMBER_CONSTANT_SUPPORT
#	undef EXTL_MEMBER_CONSTANT_SUPPORT
#endif

#ifdef EXTL_MEMBER_CONSTANT_64BIT_SUPPORT
#	undef EXTL_MEMBER_CONSTANT_64BIT_SUPPORT
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Namespace support
 */
#ifdef EXTL_NAMESPACE_SUPPORT
#	undef EXTL_NAMESPACE_SUPPORT
#endif

#ifdef EXTL_STD_NAMESPACE
#	undef EXTL_STD_NAMESPACE
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Template support
 */
#ifdef EXTL_TEMPLATE_SUPPORT
#	undef EXTL_TEMPLATE_SUPPORT
#endif

/* Class member template function support */
#ifdef EXTL_MEMBER_TEMPLATE_FUNCTION_SUPPORT
#	undef EXTL_MEMBER_TEMPLATE_FUNCTION_SUPPORT
#endif

/* Class member template function overload discriminated support */
#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
#	undef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
#endif

/* Class member template constructor support */
#ifdef EXTL_MEMBER_TEMPLATE_CTOR_SUPPORT
#	undef EXTL_MEMBER_TEMPLATE_CTOR_SUPPORT
#endif

/* Class member template constructor overload discriminated support */
#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
#	undef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
#endif

/* Template specialization support */
#ifdef EXTL_TEMPLATE_SPEC_SUPPORT
#	undef EXTL_TEMPLATE_SPEC_SUPPORT
#endif

/* Template specialization syntax support: template<> */
#ifdef EXTL_TEMPLATE_SPEC_SYNTAX_SUPPORT
#	undef EXTL_TEMPLATE_SPEC_SYNTAX_SUPPORT
#endif

/* Template partial specialization support */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
#	undef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
#endif

/* Template partial specialization with array type support */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_ARRAY_TYPE_SUPPORT
#	undef EXTL_TEMPLATE_PARTIAL_SPEC_ARRAY_TYPE_SUPPORT
#endif

/* Template partial specialization about function pointer support */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_FUNC_PTR_SUPPORT
#	undef EXTL_TEMPLATE_PARTIAL_SPEC_FUNC_PTR_SUPPORT
#endif

/* Template partial specialization about member function pointer support */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_MEM_FUNC_PTR_SUPPORT
#	undef EXTL_TEMPLATE_PARTIAL_SPEC_MEM_FUNC_PTR_SUPPORT
#endif

/* Template partial specialization with function calling convention support */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_WITH_FUNC_CALL_CONV_SUPPORT
#	undef EXTL_TEMPLATE_PARTIAL_SPEC_WITH_FUNC_CALL_CONV_SUPPORT
#endif

/* Distinguishes different function calling convention in template partial specialization support
 * CDECL, FASTCALL and STDCALL are different function calling convention
 */
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_DISTINGUISH_DIFFERENT_FUNC_CALL_CONV_SUPPORT	
#	undef EXTL_TEMPLATE_PARTIAL_SPEC_DISTINGUISH_DIFFERENT_FUNC_CALL_CONV_SUPPORT	
#endif

/* Template class default argument support */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
#	undef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
#endif

/* Member template class support */
#ifdef EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT
#	undef EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT
#endif

/* Member template friend support */
#ifdef EXTL_MEMBER_TEMPLATE_FRIEND_SUPPORT
#	undef EXTL_MEMBER_TEMPLATE_FRIEND_SUPPORT
#endif

/* Function template non-type parameter support eg:template <typename T, int N> */
#ifdef EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT
#	undef EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT
#endif

/* template non-type default parameter dependent support
 * e.g.
 * 
	template<	int N = 1	
			,	typename T	= class1<N>	//<=
			>
 */
#ifdef EXTL_TEMPLATE_NON_TYPE_DEFAULT_PARAM_DEPENDENT_SUPPORT
#	undef EXTL_TEMPLATE_NON_TYPE_DEFAULT_PARAM_DEPENDENT_SUPPORT
#endif

/* Template type required in template function argument list */
#ifdef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
#	undef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
#endif

/* Some compilers just generate one instantiation of function templates whose
 * template parameters don't appear in the function parameter list
 * e.g.
	template <int N>
	func1()	{ printf("%d\n", N);	}

	template <typename T>
	func2()	{ printf("%s\n", typeid(T).name());	}

	int main()
	{
		func1<1>();
		func1<2>();
		func2<int>();
		func2<double>();

 * If it is supported, the output is: 1 2 int double
 * otherwise, the output is: 2 2 double double
 */
#ifdef EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT
#	undef EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT
#endif

/* Member function as template param support */
#ifdef EXTL_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
#	undef EXTL_MEM_FUNC_AS_TEMPLATE_PARAM_SUPPORT
#endif

/* template<typenam T, T N> support */
#ifdef EXTL_TEMPLATE_TYPENAME_T_T_N_SUPPORT
#	undef EXTL_TEMPLATE_TYPENAME_T_T_N_SUPPORT
#endif

/* Template template support
 * e.g.
 *
	template<typename T>
	struct class_1{};

	template<template<typename T> class class_temp = class_1 >
	struct class_2{};
 *
 */
#ifdef EXTL_TEMPLATE_TEMPLATE_SUPPORT
#	undef EXTL_TEMPLATE_TEMPLATE_SUPPORT
#endif

/* Template specialization within template classes support */
#ifdef EXTL_TEMPLATE_SPEC_WITHIN_TEMPLATE_CLASS_SUPPORT
#	undef EXTL_TEMPLATE_SPEC_WITHIN_TEMPLATE_CLASS_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Native bool support
 */
#ifdef EXTL_NATIVE_BOOL_SUPPORT
#	undef EXTL_NATIVE_BOOL_SUPPORT
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * wchar_t support
 */
#ifdef EXTL_NATIVE_WCHAR_T_SUPPORT
#	undef EXTL_NATIVE_WCHAR_T_SUPPORT
#endif 

#ifdef EXTL_TYPEDEF_WCHAR_T_SUPPORT
#	undef EXTL_TYPEDEF_WCHAR_T_SUPPORT
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * Current function name
 */
#ifdef EXTL_CURRENT_FUNCTION
#	undef EXTL_CURRENT_FUNCTION
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Static array size determination support
 */
#ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
#	undef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * #pragma message support
 */
#ifdef EXTL_PRAGMA_MESSAGE_SUPPORT
#	undef EXTL_PRAGMA_MESSAGE_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * #pragma once support
 */
#ifdef EXTL_PRAGMA_ONCE_SUPPORT
#	undef EXTL_PRAGMA_ONCE_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Member constant initialization support
 */
#ifdef EXTL_MEMBER_CONST_INIT_SUPPORT
#	undef EXTL_MEMBER_CONST_INIT_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Inline assembly support
 */
#ifdef EXTL_INLINE_ASM_SUPPORT
#	undef EXTL_INLINE_ASM_SUPPORT
#endif

#ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
#	undef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Inline support
 */
#ifdef EXTL_C99_INLINE
#	undef EXTL_C99_INLINE
#endif

#ifdef EXTL_CUSTOM_C_INLINE
#	undef EXTL_CUSTOM_C_INLINE
#endif

/* ///////////////////////////////////////////////////////////////////////
 * cv-qualified void specialization support
 */
#ifdef EXTL_CV_VOID_SPEC_SUPPORT
#	undef EXTL_CV_VOID_SPEC_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * cv-qualified specialization support
 */
#ifdef EXTL_CV_SPEC_SUPPORT
#	undef EXTL_CV_SPEC_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Call convention support
 */
#ifdef EXTL_CDECL_SUPPORT
#	undef EXTL_CDECL_SUPPORT
#endif

#ifdef EXTL_FASTCALL_SUPPORT
#	undef EXTL_FASTCALL_SUPPORT
#endif

#ifdef EXTL_STDCALL_SUPPORT
#	undef EXTL_STDCALL_SUPPORT
#endif

#ifdef EXTL_CDECL
#	undef EXTL_CDECL
#endif

#ifdef EXTL_FASTCALL
#	undef EXTL_FASTCALL
#endif

#ifdef EXTL_STDCALL	
#	undef EXTL_STDCALL	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Ellipsis in function testing support 
 * eg: void func(...);
 */
#ifdef EXTL_ELLIPSIS_IN_FUNC_TESTING_SUPPORT
#	undef EXTL_ELLIPSIS_IN_FUNC_TESTING_SUPPORT	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Ellipsis in template partial specializtion about function testing support 
 * eg: template <typename T> struct type<void (*)(...)>
 */
#ifdef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT
#	undef EXTL_ELLIPSIS_IN_TEMPLATE_PARTIAL_SPEC_FUNC_TESTING_SUPPORT	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Keywords support 
 */

/* typename eg: template < typename T > or template < class T > */
#ifdef EXTL_TYPENAME_PARAM_KEYWORD_SUPPORT
#	undef EXTL_TYPENAME_PARAM_KEYWORD_SUPPORT	
#endif

/* typename typename eg: typedef typename template_class<T>::type type; */
#ifdef EXTL_TYPENAME_TYPE_KEYWORD_SUPPORT
#	undef EXTL_TYPENAME_TYPE_KEYWORD_SUPPORT	
#endif

/* typename eg: template< class A = typename template_class<T>::type > */
#ifdef EXTL_TYPENAME_TYPE_DEF_KEYWORD_SUPPORT
#	undef EXTL_TYPENAME_TYPE_DEF_KEYWORD_SUPPORT	
#endif

/* typename qualifier in constructor initialiser lists */
#ifdef EXTL_TYPENAME_TYPE_MIL_KEYWORD_SUPPORT
#	undef EXTL_TYPENAME_TYPE_MIL_KEYWORD_SUPPORT	
#endif

/* typename eg: typename template_class<T>::type func(); */
#ifdef EXTL_TYPENAME_TYPE_RET_KEYWORD_SUPPORT
#	undef EXTL_TYPENAME_TYPE_RET_KEYWORD_SUPPORT	
#endif

/* template eg: typedef A::template a<T>::type type; */
#ifdef EXTL_TEMPLATE_QUAL_KEYWORD_SUPPORT
#	undef EXTL_TEMPLATE_QUAL_KEYWORD_SUPPORT	
#endif

/* mutable */
#ifdef EXTL_MUTABLE_KEYWORD_SUPPORT
#	undef EXTL_MUTABLE_KEYWORD_SUPPORT	
#endif

/* explicit */
#ifdef EXTL_EXPLICIT_KEYWORD_SUPPORT
#	undef EXTL_EXPLICIT_KEYWORD_SUPPORT	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Exception support
 */
#ifdef EXTL_EXCEPTION_SUPPORT
#	undef EXTL_EXCEPTION_SUPPORT
#endif

/* Exception signature support (eg: void func() throw(e1, e2, ...);) */
#ifdef EXTL_EXCEPTION_SIGNATURE_SUPPORT
#	undef EXTL_EXCEPTION_SIGNATURE_SUPPORT
#endif

/* throw std::bad_alloc() support */
#ifdef EXTL_THROW_BAD_ALLOC_SUPPORT
#	undef EXTL_THROW_BAD_ALLOC_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Return void support 
 * eg: return (void)0;
 */
#ifdef EXTL_RETURN_VOID_SUPPORT
#	undef EXTL_RETURN_VOID_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Member pointer as bool return support 
 * eg: int (class_type::*) func(){return &class_type::member;}
 * if(func()){...}
 */

#ifdef EXTL_MEM_PTR_AS_BOOL_RET_SUPPORT
#	undef EXTL_MEM_PTR_AS_BOOL_RET_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * 64-bit interger format output support 
 * eg: printf("%I64d", ...);
 */

#ifdef EXTL_PRINTF_I64_FORMAT_SUPPORT
#	undef EXTL_PRINTF_I64_FORMAT_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Named return value optimization support 
 */
#ifdef EXTL_NRVO_SUPPORT
#	undef EXTL_NRVO_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Property support 
 * Note: Compiler extensibity
 */
#ifdef EXTL_PROPERTY_SUPPORT
#	undef EXTL_PROPERTY_SUPPORT
#endif

#ifdef EXTL_PROPERTY_GET
#	undef EXTL_PROPERTY_GET
#endif

#ifdef EXTL_PROPERTY_SET
#	undef EXTL_PROPERTY_SET
#endif

#ifdef EXTL_PROPERTY_GETSET
#	undef EXTL_PROPERTY_GETSET
#endif

/* ///////////////////////////////////////////////////////////////////////
 * CRTP support 
 * eg: class derived_class : public base_class< derived_class > {};
 */
#ifdef EXTL_CRTP_SUPPORT
#	undef EXTL_CRTP_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * EBO(empty base optimization) support 
 */

/* EBO1:
 * empty_child - empty_base
 */
#ifdef EXTL_EBO_FORM_1_SUPPORT
#	undef EXTL_EBO_FORM_1_SUPPORT
#endif

/* EBO2:
 * non_empty_child - empty_base
 */
#ifdef EXTL_EBO_FORM_2_SUPPORT
#	undef EXTL_EBO_FORM_2_SUPPORT
#endif

/* EBO3:
 * empty_child - empty_base2 - empty_base1
 */
#ifdef EXTL_EBO_FORM_3_SUPPORT
#	undef EXTL_EBO_FORM_3_SUPPORT
#endif


/* EBO4:
 * non_empty_child - empty_base2 - empty_base1
 */
#ifdef EXTL_EBO_FORM_4_SUPPORT
#	undef EXTL_EBO_FORM_4_SUPPORT
#endif

/* EBO5:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						empty_base2
 */
#ifdef EXTL_EBO_FORM_5_SUPPORT
#	undef EXTL_EBO_FORM_5_SUPPORT
#endif

/* EBO6:
 *							empty_base1
 *						/	
 * non_empty_child	-
 *						\
 *							empty_base2
 */
#ifdef EXTL_EBO_FORM_6_SUPPORT
#	undef EXTL_EBO_FORM_6_SUPPORT
#endif

/* EBO7:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						non_empty_base2
 */
#ifdef EXTL_EBO_FORM_7_SUPPORT
#	undef EXTL_EBO_FORM_7_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * EDO(empty derived optimization) support 
 */

/* EDO1:
 * empty_child - empty_base
 */
#ifdef EXTL_EDO_FORM_1_SUPPORT
#	undef EXTL_EDO_FORM_1_SUPPORT
#endif

/* EDO2:
 * empty_child_template - empty_base
 */
#ifdef EXTL_EDO_FORM_2_SUPPORT
#	undef EXTL_EDO_FORM_2_SUPPORT
#endif

/* EDO3:
 * empty_child - non_empty_base
 */
#ifdef EXTL_EDO_FORM_3_SUPPORT
#	undef EXTL_EDO_FORM_3_SUPPORT
#endif


/* EDO4:
 * empty_child_template - non_empty_base
 */
#ifdef EXTL_EDO_FORM_4_SUPPORT
#	undef EXTL_EDO_FORM_4_SUPPORT
#endif

/* EDO5:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						empty_base2
 */
#ifdef EXTL_EDO_FORM_5_SUPPORT
#	undef EXTL_EDO_FORM_5_SUPPORT
#endif

/* EDO6:
 *								empty_base1
 *							/	
 * empty_child_template	-
 *							\
 *								empty_base2
 */
#ifdef EXTL_EDO_FORM_6_SUPPORT
#	undef EXTL_EDO_FORM_6_SUPPORT
#endif

/* EDO7:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						non_empty_base2
 */
#ifdef EXTL_EDO_FORM_7_SUPPORT
#	undef EXTL_EDO_FORM_7_SUPPORT
#endif

/* EDO8:
 *								empty_base1
 *							/	
 * empty_child_template	-
 *							\
 *								non_empty_base2
 */
#ifdef EXTL_EDO_FORM_8_SUPPORT
#	undef EXTL_EDO_FORM_8_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * c++0x support 
 */
#ifdef EXTL_0x_RVALUE_REFERENCE_SUPPORT
#	undef EXTL_0x_RVALUE_REFERENCE_SUPPORT
#endif

#ifdef EXTL_0x_VARIADIC_TEMPLATE_SUPPORT
#	undef EXTL_0x_VARIADIC_TEMPLATE_SUPPORT
#endif

#ifdef EXTL_0x_STATIC_ASSERT_SUPPORT
#	undef EXTL_0x_STATIC_ASSERT_SUPPORT
#endif

#ifdef EXTL_0x_RIGHT_ANGLE_BRACKET_SUPPORT
#	undef EXTL_0x_RIGHT_ANGLE_BRACKET_SUPPORT
#endif

#ifdef EXTL_0x_INLINE_NAMESPACE_SUPPORT
#	undef EXTL_0x_INLINE_NAMESPACE_SUPPORT
#endif

/* ///////////////////////////////////////////////////////////////////////
 * type alias friend support 
 * e.g.
 * typedef class_type<T>	friend_type;
 * friend					friend_type;
 */
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
#	undef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
#endif
