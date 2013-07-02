/* ///////////////////////////////////////////////////////////////////////
 * File:		help_functions.h		
 *
 * Created:		08.03.10				
 * Updated:		08.04.14	
 *
 * Brief: Memory helpful functions
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_HELP_FUNCTIONS_H
#define EXTL_MEMORY_HELP_FUNCTIONS_H

/*!\file help_functions.h
 * \brief Memory helpful functions
 */
#ifndef __cplusplus
#	error help_functions.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#	include "../prefix.h"
#	include "../type/traits/is_void.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "../type/traits/is_pod.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Memory block operations
 */

/// mem_copy 
EXTL_INLINE void const* mem_copy(void* dest, void const* src, e_size_t size)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);
	return ::memcpy(dest, src, size);
}

/// mem_cmp 
EXTL_INLINE e_int_t mem_cmp(void const* lhs, void const* rhs, e_size_t size)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);

	return ::memcmp(lhs, rhs, size); 
}

/// mem_move 
EXTL_INLINE void const* mem_move(void* dest, void const* src, e_size_t size)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);

	return ::memmove(dest, src, size);
}

/// mem_fill 
EXTL_INLINE void const* mem_fill(void* dest, e_int_t const& value, e_size_t size)
{
	EXTL_ASSERT(NULL != dest);
	return ::memset(dest, value, size);
}

/// mem_fill_0 
EXTL_INLINE void const* mem_fill_0(void* dest, e_size_t size)
{
	EXTL_ASSERT(NULL != dest);
	return ::memset(dest, 0, size);
}
/* ///////////////////////////////////////////////////////////////////////
 * POD memory block operations
 */
/// pod_copy_n 
template < typename_param_k D, typename_param_k S >
EXTL_INLINE D const* pod_copy_n(D* dest, S const* src, e_size_t n)
{
#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
	EXTL_MUST_BE_POD(D);
	EXTL_MUST_BE_POD(S);
#endif
	EXTL_MUST_NOT_BE_VOID(D);
	EXTL_MUST_NOT_BE_VOID(S);

	return static_cast<D const*>(mem_copy(dest, src, n * sizeof(D)));
}

/// non_pod_copy_n 
template < typename_param_k D, typename_param_k S >
EXTL_INLINE D const* non_pod_copy_n(D* dest, S const* src, e_size_t n)
{
	D* ret = dest;
	for(; 0 != n; ++dest, ++src, --n)
    {
        *dest = *src;
    }
	return ret;
}
/// pod_cmp_n 
template < typename_param_k D, typename_param_k S >
EXTL_INLINE e_int_t pod_cmp_n(D const* lhs, S const* rhs, e_size_t n)
{
#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
	EXTL_MUST_BE_POD(D);
	EXTL_MUST_BE_POD(S);
#endif
	EXTL_MUST_NOT_BE_VOID(D);
	EXTL_MUST_NOT_BE_VOID(S);

	EXTL_ASSERT(0 != n);
	for(e_size_t i = 0; i < n; ++i, ++lhs, ++rhs)
	{
		if(*lhs != *rhs)
		{
			return (*lhs < *rhs)? -1 : + 1;
		}
	}
	return 0;
}
/// pod_cmp_n 
EXTL_INLINE e_int_t pod_cmp_n(e_char_t const* lhs, e_char_t const* rhs, e_size_t n)
{
	return mem_cmp(lhs, rhs, n * sizeof(e_char_t)); 
}

/// non_pod_cmp_n 
template < typename_param_k D, typename_param_k S >
EXTL_INLINE e_int_t non_pod_cmp_n(D const* lhs, S const* rhs, e_size_t n)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	EXTL_ASSERT(0 != n);
	for(e_size_t i = 0; i < n; ++i, ++lhs, ++rhs)
	{
		if(*lhs != *rhs)
		{
			return (*lhs < *rhs)? -1 : + 1;
		}
	}
	return 0;
}
/// pod_move_n 
template < typename_param_k D, typename_param_k S >
EXTL_INLINE D const* pod_move_n(D* dest, S const* src, e_size_t n)
{
#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
	EXTL_MUST_BE_POD(D);
	EXTL_MUST_BE_POD(S);
#endif

	EXTL_MUST_NOT_BE_VOID(D);
	EXTL_MUST_NOT_BE_VOID(S);

	return static_cast<D const*>(mem_move(dest, src, n * sizeof(D)));
}
/// non_pod_move_n 
template < typename_param_k D, typename_param_k S >
EXTL_INLINE D const* non_pod_move_n(D* dest, S const* src, e_size_t n)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);
	
	return non_pod_copy_n(dest, src, n);
}

/// pod_fill_n 
template < typename_param_k D, typename_param_k V >
EXTL_INLINE D const* pod_fill_n(D* dest, V const& value, e_size_t n)
{
#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
	EXTL_MUST_BE_POD(D);
	EXTL_MUST_BE_POD(V);
#endif
	EXTL_MUST_NOT_BE_VOID(D);

	EXTL_ASSERT(0 != n);

	D* ret = dest;
	for(; 0 != n; ++dest, --n)
    {
        *dest = value;
    }
	return ret;
}
/// pod_fill_n: Optimizatiion 
EXTL_INLINE e_char_t const* pod_fill_n(e_char_t* dest, e_char_t const& value, e_size_t n)
{
	return static_cast<e_char_t const*>(mem_fill(dest, value, n * sizeof(e_char_t)));
}
/// non_pod_fill_n 
template < typename_param_k D, typename_param_k V >
EXTL_INLINE D const* non_pod_fill_n(D* dest, V const& value, e_size_t n)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(0 != n);

	D* ret = dest;
	for(; 0 != n; ++dest, --n)
    {
        *dest = value;
    }
	return ret;
}

/// pod_fill_n 
template < typename_param_k D >
EXTL_INLINE D const* pod_fill_0_n(D* dest, e_size_t n)
{
#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
	EXTL_MUST_BE_POD(D);
#endif
	EXTL_MUST_NOT_BE_VOID(D);

	return static_cast<D const*>(mem_fill_0(dest, n * sizeof(D)));
}

/// non_pod_fill_0
template < typename_param_k D >
EXTL_INLINE D const* non_pod_fill_0_n(D* dest, e_size_t n)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(0 != n);

	D* ret = dest;
	for(; 0 != n; ++dest, --n)
    {
        *dest = D();
    }
	return ret;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_MEMORY_HELP_FUNCTIONS_TEST_ENABLE
#	include "unit_test/help_functions_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_HELP_FUNCTIONS_H */
/* //////////////////////////////////////////////////////////////////// */
