/* ///////////////////////////////////////////////////////////////////////
 * File:		suffix.h		
 *
 * Created:		08.02.02					
 * Updated:		08.04.14	
 *
 * Brief: The suffix file of configuration
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONFIG_SUFFIX_H
#define EXTL_CONFIG_SUFFIX_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

#ifndef EXTL_CONFIG_COMPILER_H
#	error This file must be depended on compiler\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * The detection of template 
 */
#if defined(__cplusplus) && !defined(EXTL_TEMPLATE_SUPPORT)
#	error Template support not detected
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Specialisation of template 
 */
#ifdef EXTL_TEMPLATE_SPECIALISATION
#	undef EXTL_TEMPLATE_SPECIALISATION
#endif

#ifdef EXTL_TEMPLATE_SPEC_SYNTAX_SUPPORT
#	define EXTL_TEMPLATE_SPECIALISATION		template<>
#else
#	define EXTL_TEMPLATE_SPECIALISATION
#endif

/* ///////////////////////////////////////////////////////////////////////
 * The detection of the 64-bit interger 
 */
#if !defined(EXTL_64BIT_INT_SUPPORT)
#	error 64-bit is not supported correctlly.
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * The config of namespace
 */
#include "namespace.h"


/* ///////////////////////////////////////////////////////////////////////
 * Reference for compatible C language
 */
#ifdef __cplusplus
#	define _r				&
#	define const_ref		const&
#else 
#	define _r	
#	define const_ref		const
#endif


/* ///////////////////////////////////////////////////////////////////////
 * Inline supported
 */
#if defined(__cplusplus)
#	define EXTL_INLINE					  inline
#else 
#	if defined(EXTL_C99_INLINE)
#		define EXTL_INLINE                inline
#	elif defined(EXTL_CUSTOM_C_INLINE)
#		define EXTL_INLINE                EXTL_CUSTOM_C_INLINE
#	else 
#		define EXTL_INLINE                static
#	endif 
#endif 

/* //////////////////////////////////////////////////////////////////// */
/* Calling convention */
#ifndef	EXTL_CDECL
#	define EXTL_CDECL
#endif

#ifndef EXTL_FASTCALL
#	ifdef EXTL_FASTCALL_SUPPORT
#		error EXTL_FASTCALL must be defined, when EXTL_FASTCALL_SUPPORT is defined.
#	else
#		define EXTL_FASTCALL
#	endif
#endif

#ifndef EXTL_STDCALL
#	ifdef EXTL_STDCALL_SUPPORT
#		error EXTL_STDCALL must be defined, when EXTL_STDCALL_SUPPORT is defined.
#	else
#		define EXTL_STDCALL
#	endif
#endif

/* //////////////////////////////////////////////////////////////////// */
/* The initialization of static member const  */
#ifdef __cplusplus
#	ifdef EXTL_MEMBER_CONST_INIT_SUPPORT
#		define EXTL_STATIC_MEMBER_CONST(type, assignment) static const type assignment
#	else
#		define EXTL_STATIC_MEMBER_CONST(type, assignment) enum { assignment }
#	endif
#else
#	define EXTL_STATIC_MEMBER_CONST(type, assignment)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Keywords 
 * explicit_k				explicit
 * mutable_k				mutable
 * template_qual_k			template eg: typedef A::template a<T>::type type;
 * typename_param_k			typename eg: template < typename T > or template < class T >
 * typename_type_k			typename typename eg: typedef typename template_class<T>::type type;
 * typename_type_def_k		typename eg: template< class A = typename template_class<T>::type >
 * typename_type_mil_k		typename qualifier in constructor initialiser lists
 * typename_type_ret_k		typename eg: typename template_class<T>::type func();
 * //////////////////////////////////////////////////////////////////// */

/* Force all keyword to be supported(used to test) */
#ifdef EXTL_FORCE_ALL_KEYWORD_SUPPORT

#	ifndef EXTL_EXPLICIT_KEYWORD_SUPPORT
#		define EXTL_EXPLICIT_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_MUTABLE_KEYWORD_SUPPORT
#		define EXTL_MUTABLE_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_TEMPLATE_QUAL_KEYWORD_SUPPORT
#		define EXTL_TEMPLATE_QUAL_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_TYPENAME_PARAM_KEYWORD_SUPPORT
#		define EXTL_TYPENAME_PARAM_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_TYPENAME_TYPE_KEYWORD_SUPPORT
#		define EXTL_TYPENAME_TYPE_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_TYPENAME_TYPE_DEF_KEYWORD_SUPPORT
#		define EXTL_TYPENAME_TYPE_DEF_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_TYPENAME_TYPE_MIL_KEYWORD_SUPPORT
#		define EXTL_TYPENAME_TYPE_MIL_KEYWORD_SUPPORT
#	endif

#	ifndef EXTL_TYPENAME_TYPE_RET_KEYWORD_SUPPORT
#		define EXTL_TYPENAME_TYPE_RET_KEYWORD_SUPPORT
#	endif

#endif


/* Keywords */
#ifdef EXTL_EXPLICIT_KEYWORD_SUPPORT
#	define explicit_k			explicit
#else
#	define explicit_k	
#endif

#ifdef EXTL_MUTABLE_KEYWORD_SUPPORT
#	define mutable_k			mutable
#else
#	define mutable_k	
#endif

#ifdef EXTL_TEMPLATE_QUAL_KEYWORD_SUPPORT
#	define template_qual_k		template
#else
#	define template_qual_k	
#endif

#ifdef EXTL_TYPENAME_PARAM_KEYWORD_SUPPORT
#	define typename_param_k		typename
#else
#	define typename_param_k		class 
#endif

#ifdef EXTL_TYPENAME_TYPE_KEYWORD_SUPPORT
#	define typename_type_k		typename
#else
#	define typename_type_k	
#endif

#ifdef EXTL_TYPENAME_TYPE_DEF_KEYWORD_SUPPORT
#	define typename_type_def_k	typename
#else
#	define typename_type_def_k	
#endif

#ifdef EXTL_TYPENAME_TYPE_MIL_KEYWORD_SUPPORT
#	define typename_type_mil_k	typename
#else
#	define typename_type_mil_k	
#endif

#ifdef EXTL_TYPENAME_TYPE_RET_KEYWORD_SUPPORT
#	define typename_type_ret_k	typename
#else
#	define typename_type_ret_k	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Exception signature 
 */
#if defined(__cplusplus) && \
		!defined(EXTL_EXCEPTION_SPECIFICATIONS_DISABLE) && \
			defined(EXTL_EXCEPTION_SIGNATURE_SUPPORT)

#	define EXTL_THROW										throw
#	define EXTL_THROW_0()									throw ()
#	define EXTL_THROW_1(e1)									throw (e1)
#	define EXTL_THROW_2(e1, e2)								throw (e1, e2)
#	define EXTL_THROW_3(e1, e2, e3)							throw (e1, e2, e3)
#	define EXTL_THROW_4(e1, e2, e3, e4)						throw (e1, e2, e3, e4)
#	define EXTL_THROW_5(e1, e2, e3, e4, e5)					throw (e1, e2, e3, e4, e5)
#	define EXTL_THROW_6(e1, e2, e3, e4, e5, e6)				throw (e1, e2, e3, e4, e5, e6)
#	define EXTL_THROW_7(e1, e2, e3, e4, e5, e6, e7)			throw (e1, e2, e3, e4, e5, e6, e7)
#	define EXTL_THROW_8(e1, e2, e3, e4, e5, e6, e7, e8)		throw (e1, e2, e3, e4, e5, e6, e7, e8)

#else 
#	define EXTL_THROW
#	define EXTL_THROW_0()
#	define EXTL_THROW_1(e1)
#	define EXTL_THROW_2(e1, e2)
#	define EXTL_THROW_3(e1, e2, e3)
#	define EXTL_THROW_4(e1, e2, e3, e4)
#	define EXTL_THROW_5(e1, e2, e3, e4, e5)
#	define EXTL_THROW_6(e1, e2, e3, e4, e5, e6)
#	define EXTL_THROW_7(e1, e2, e3, e4, e5, e6, e7)
#	define EXTL_THROW_8(e1, e2, e3, e4, e5, e6, e7, e8)
   
#endif 

/* ///////////////////////////////////////////////////////////////////////
 * Exception assert
 * Throws the given exception when the condition is false
 */
#if defined(EXTL_EXCEPTION_ENABLE) && \
		defined(EXTL_EXCEPTION_SUPPORT)
#	define EXTL_THROW_E(e)							throw e
#	define EXTL_ASSERT_THROW(condition, exception)	if(!(condition)) EXTL_THROW_E(exception);
#else
#	define EXTL_THROW_E(e)							
#	define EXTL_ASSERT_THROW(condition, exception)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Exception catch 
 */
#if defined(EXTL_EXCEPTION_ENABLE) && \
		defined(EXTL_EXCEPTION_SUPPORT)

#define EXTL_TRY			try {
#define EXTL_CATCH(x)		} catch (x) {
#define EXTL_CATCH_ALL		} catch (...) {
#define EXTL_CATCH_END		}

#else

#define EXTL_TRY			{{
#define EXTL_CATCH(x)		} if (0) {
#define EXTL_CATCH_ALL		} if (0) {
#define EXTL_CATCH_END		}}

#endif
/* ///////////////////////////////////////////////////////////////////////
 * Template param friend
 * 
	template< typename T >
	class some_class
	{
			EXTL_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T);
		private:
			m_value;	// some_class<T>::m_value visible to T
	};
 *
 */
#define EXTL_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)	friend T

/* ///////////////////////////////////////////////////////////////////////
 * Boundary alignment
 */
#define EXTL_ALIGN(size, boundary)	((size + (boundary - 1)) & ~(boundary - 1))

/* ///////////////////////////////////////////////////////////////////////
 * Line number & File name
 */
#define EXTL_LINENUM	__LINE__
#define EXTL_FILENAME	__FILE__

/* ///////////////////////////////////////////////////////////////////////
 * Explicit function template arguments
 *
 * Some compilers(vc6.0 ...) just generate one instantiation of function templates whose
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
 *
 * To fix it, write:
	template <int N>
	func1(EXTL_EXPLICIT_TEMPLATE_NON_TYPE(int, N))	{ printf("%d\n", N);	}

	template <typename T>
	func2(EXTL_EXPLICIT_TEMPLATE_TYPE(T))	{ printf("%s\n", typeid(T).name());	}
 *
 * the output is: 1 2 int double
 */
#if !defined(EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT)
#	define EXTL_EXPLICIT_TEMPLATE_TYPE(t)						EXTL_NS(type_wrap)<t>* = 0
#	define EXTL_APPEND_EXPLICIT_TEMPLATE_TYPE(t)				, EXTL_EXPLICIT_TEMPLATE_TYPE(t)
#else
#	define EXTL_EXPLICIT_TEMPLATE_TYPE(t)
#	define EXTL_APPEND_EXPLICIT_TEMPLATE_TYPE(t)
#endif

#if !defined(EXTL_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS_SUPPORT) && \
		defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT)
#	define EXTL_EXPLICIT_TEMPLATE_NON_TYPE(t, v)				EXTL_NS(non_type_wrap)<t, v>* = 0
#	define EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)			, EXTL_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#else
#	define EXTL_EXPLICIT_TEMPLATE_NON_TYPE(t, v)		
#	define EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)	
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_SUFFIX_H */
/* //////////////////////////////////////////////////////////////////// */
