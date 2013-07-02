/* ///////////////////////////////////////////////////////////////////////
 * File:		suppress_unused.h		
 *
 * Created:		08.02.20				
 * Updated:		08.05.05	
 *
 * Brief: Suppress unused compiler warning
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_SUPPRESS_UNUSED_H
#define EXTL_UTILITY_SUPPRESS_UNUSED_H

/*!\file suppress_unused.h
 * \brief Suppress unused compiler warning
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#if 0 /* unused */
	template < typename_param_k T >
	inline void suppress_unused_func(T const volatile &){}

#	ifdef EXTL_CDECL_SUPPORT
	template < typename_param_k R >
	inline void suppress_unused_func(R (EXTL_CDECL *)()){}

	template < typename_param_k R, typename_param_k T0 >
	inline void suppress_unused_func(R (EXTL_CDECL *)(T0)){}
#	endif

#	ifdef EXTL_FASTCALL_SUPPORT
	template < typename_param_k R >
	inline void suppress_unused_func(R (EXTL_FASTCALL *)()){}

	template < typename_param_k R, typename_param_k T0 >
	inline void suppress_unused_func(R (EXTL_FASTCALL *)(T0)){}
#	endif

#	ifdef EXTL_STDCALL_SUPPORT
	template < typename_param_k R >
	inline void suppress_unused_func(R (EXTL_STDCALL *)()){}

	template < typename_param_k R, typename_param_k T0 >
	inline void suppress_unused_func(R (EXTL_STDCALL *)(T0)){}
#	endif

#	define EXTL_SUPPRESS_UNUSED(x)	EXTL_NS(suppress_unused_func)(x)

#elif defined(EXTL_COMPILER_IS_WATCOM)
#	define EXTL_SUPPRESS_UNUSED(x)	((void)(x))

#elif defined(__cplusplus) 
#	define EXTL_SUPPRESS_UNUSED(x)	(static_cast<void>(x))

#elif 0
#	define EXTL_SUPPRESS_UNUSED(x)	((void)(x))

#else /* unused */
#	define EXTL_SUPPRESS_UNUSED(x)	
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_SUPPRESS_UNUSED_H */
/* //////////////////////////////////////////////////////////////////// */
