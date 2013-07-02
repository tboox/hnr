/* ///////////////////////////////////////////////////////////////////////
 * File:		atomic_functions.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.05
 *
 * Brief: atomic operation functions 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_H
#define EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_H

/*!\file atomic_functions.h
 * \brief atomic_functions class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Atomic interger type 
 */
#if defined(_M_IX86)
typedef e_sint32_t     e_atomic_int_t;
#elif defined(_M_IA64)
typedef e_sint64_t     e_atomic_int_t;
#else 
#	error Not valid for processors other than Intel.
#endif /* _M_IX86 || _M_IA64 */

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

/* Call convention */
#ifdef EXTL_WIN_ATOMIC_FNS_CALLCONV
#	undef EXTL_WIN_ATOMIC_FNS_CALLCONV
#endif

#define EXTL_WIN_ATOMIC_FNS_CALLCONV	WINAPI

/* Declaration and implemetation  */
#ifdef EXTL_WIN_ATOMIC_FNS_DECL_
#	undef EXTL_WIN_ATOMIC_FNS_DECL_
#endif

#ifdef EXTL_WIN_ATOMIC_FNS_IMPL_
#	undef EXTL_WIN_ATOMIC_FNS_IMPL_
#endif

/* The atomic operations in assembly code are not supported now temporarily */
#if 0 /* EXTL_INLINE_ASM_SUPPORT */
#	ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
#		define EXTL_WIN_ATOMIC_FNS_DECL_(type)	EXTL_INLINE type EXTL_WIN_ATOMIC_FNS_CALLCONV
#		define EXTL_WIN_ATOMIC_FNS_IMPL_(type)	EXTL_INLINE __declspec(naked) type EXTL_WIN_ATOMIC_FNS_CALLCONV
#	else
#		define EXTL_WIN_ATOMIC_FNS_DECL_(type)	type EXTL_WIN_ATOMIC_FNS_CALLCONV
#		define EXTL_WIN_ATOMIC_FNS_IMPL_(type)	static __declspec(naked) type EXTL_WIN_ATOMIC_FNS_CALLCONV
#	endif
#else
#	define EXTL_WIN_ATOMIC_FNS_DECL_(type)	EXTL_INLINE type EXTL_WIN_ATOMIC_FNS_CALLCONV
#	define EXTL_WIN_ATOMIC_FNS_IMPL_(type)	EXTL_INLINE type EXTL_WIN_ATOMIC_FNS_CALLCONV
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Function declaration 
 */
/// Atomic increment 
EXTL_WIN_ATOMIC_FNS_DECL_(void) atomic_inc(e_atomic_int_t volatile* p);
/// Atomic decrement 
EXTL_WIN_ATOMIC_FNS_DECL_(void) atomic_dec(e_atomic_int_t volatile* p); 

/// Atomic pre-increment(++i) 
EXTL_WIN_ATOMIC_FNS_DECL_(e_atomic_int_t) atomic_preinc(e_atomic_int_t volatile* p); 
/// Atomic pre-decrement(--i) 
EXTL_WIN_ATOMIC_FNS_DECL_(e_atomic_int_t) atomic_predec(e_atomic_int_t volatile* p); 

/// Atomic post-increment(i++) 
EXTL_WIN_ATOMIC_FNS_DECL_(e_atomic_int_t) atomic_postinc(e_atomic_int_t volatile* p); 
/// Atomic post-decrement(i++) 
EXTL_WIN_ATOMIC_FNS_DECL_(e_atomic_int_t) atomic_postdec(e_atomic_int_t volatile* p); 

/// Atomic write 
EXTL_WIN_ATOMIC_FNS_DECL_(e_atomic_int_t) atomic_write(e_atomic_int_t volatile* p, e_atomic_int_t n); 
/// Atomic read 
EXTL_WIN_ATOMIC_FNS_DECL_(e_atomic_int_t) atomic_read(e_atomic_int_t volatile const* p); 

/* ///////////////////////////////////////////////////////////////////////
 * Function implementation 
 */

/* The atomic operations in assembly code are not supported now temporarily */
#if 0 /* EXTL_INLINE_ASM_SUPPORT */
#else

/* Atomic increment */
EXTL_WIN_ATOMIC_FNS_IMPL_(void) atomic_inc(e_atomic_int_t volatile* p)
{
#if defined(_M_IX86)
    EXTL_NS_GLOBAL(InterlockedIncrement)((LPLONG)p);
#elif defined(_M_IA64)
    EXTL_NS_GLOBAL(InterlockedIncrement64)((LONGLONG*)p);
#else 
#	error Not valid for processors other than Intel
#endif
}

/* Atomic decrement */
EXTL_WIN_ATOMIC_FNS_IMPL_(void) atomic_dec(e_atomic_int_t volatile* p)
{
#if defined(_M_IX86)
    EXTL_NS_GLOBAL(InterlockedDecrement)((LPLONG)p);
#elif defined(_M_IA64)
    EXTL_NS_GLOBAL(InterlockedDecrement64)((LONGLONG*)p);
#else 
#	error Not valid for processors other than Intel
#endif 
}

/* Atomic pre-increment */
EXTL_WIN_ATOMIC_FNS_IMPL_(e_atomic_int_t) atomic_preinc(e_atomic_int_t volatile* p)
{
#if defined(_M_IX86)
    return EXTL_NS_GLOBAL(InterlockedIncrement)((LPLONG)p);
#elif defined(_M_IA64)
    return EXTL_NS_GLOBAL(InterlockedDecrement64)((LONGLONG*)p);
#else 
#	error Not valid for processors other than Intel
#endif
}

/* Atomic pre-decrement */
EXTL_WIN_ATOMIC_FNS_IMPL_(e_atomic_int_t) atomic_predec(e_atomic_int_t volatile* p)
{
#if defined(_M_IX86)
    return EXTL_NS_GLOBAL(InterlockedDecrement)((LPLONG)p);
#elif defined(_M_IA64)
    return EXTL_NS_GLOBAL(InterlockedDecrement64)((LONGLONG*)p);
#else
#	error Not valid for processors other than Intel
#endif
}

/* Atomic post-increment */
EXTL_WIN_ATOMIC_FNS_IMPL_(e_atomic_int_t) atomic_postinc(e_atomic_int_t volatile* p)
{
	e_atomic_int_t pre = *p;

#if defined(_M_IX86)
    EXTL_NS_GLOBAL(InterlockedIncrement)((LPLONG)p);
#elif defined(_M_IA64)
    EXTL_NS_GLOBAL(InterlockedDecrement64)((LONGLONG*)p);
#else 
#	error Not valid for processors other than Intel
#endif
	return pre;
}

/* Atomic post-decrement */
EXTL_WIN_ATOMIC_FNS_IMPL_(e_atomic_int_t) atomic_postdec(e_atomic_int_t volatile* p)
{
	e_atomic_int_t pre = *p;

#if defined(_M_IX86)
    EXTL_NS_GLOBAL(InterlockedDecrement)((LPLONG)p);
#elif defined(_M_IA64)
    EXTL_NS_GLOBAL(InterlockedDecrement64)((LONGLONG*)p);
#else
#	error Not valid for processors other than Intel
#endif
	return pre;
}

/* Atomic write */
EXTL_WIN_ATOMIC_FNS_IMPL_(e_atomic_int_t) atomic_write(e_atomic_int_t volatile* p, e_atomic_int_t n)
{
#if defined(_M_IX86)
    return EXTL_NS_GLOBAL(InterlockedExchange)((LPLONG)p, n);
#elif defined(_M_IA64)
    return EXTL_NS_GLOBAL(InterlockedExchange64)((LONGLONG*)p, n);
#else 
#	error Not valid for processors other than Intel
#endif
}

/* Atomic read */
EXTL_WIN_ATOMIC_FNS_IMPL_(e_atomic_int_t) atomic_read(e_atomic_int_t volatile const* p)
{
    return *p;
}
#endif /* EXTL_INLINE_ASM_SUPPORT */

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_WIN_ATOMIC_FNS_CALLCONV
#undef EXTL_WIN_ATOMIC_FNS_DECL_
#undef EXTL_WIN_ATOMIC_FNS_IMPL_

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_SYNCH_ATOMIC_FUNCTIONS_TEST_ENABLE
#	include "unit_test/atomic_functions_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_ATOMIC_FUNCTIONS_H */
/* //////////////////////////////////////////////////////////////////// */
