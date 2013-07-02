/* ///////////////////////////////////////////////////////////////////////
 * File:		atow.h		
 *
 * Created:		08.03.11				
 * Updated:		08.05.09
 *
 * Brief: ASCII ==> UNICODE
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_ATOW_H
#define EXTL_CONVERSION_ATOW_H

/*!\file atow.h
 * \brief ASCII ==> UNICODE
 * 
 * - atow: conversion function and needs to provide buffer 
 * - a2w: conversion shim and does'nt need to provide buffer 
 *   - Note: It's rather dangerous because the life cycle of it's buffer is so short
 *   - eg: 
 *     - e_wchar_t *p = a2w(pChar);
 *     - wprintf(p);					<== Undefined!
 *     - wprintf(L"%s", a2w(pChar));	<== Undefined!
 *     - wprintf(a2w(pChar));			<== Safe
 *
 */
#ifndef __cplusplus
#	error atow.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include <stdlib.h>
#include "../memory/buffer.h"
#include "../string/prefix.h" /* for std_strlen */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/// atow
EXTL_INLINE e_wchar_t const* atow(e_wchar_t* dest, e_char_t const* src, e_size_t n)
{
	EXTL_ASSERT(src != NULL);
	EXTL_ASSERT(dest != NULL);
	if(dest == NULL) return dest;

	if(0 == n || src == NULL) 
	{
		dest[0] = e_wchar_t('\0');
		return dest;
	}

	if(static_cast<e_size_t>(-1) == ::mbstowcs(dest, src, n))
	{
		dest[0] = e_wchar_t('\0');
	}
	else dest[n - 1] = e_wchar_t('\0');

	return dest;
}
/// atow
EXTL_INLINE e_wchar_t const* atow(e_wchar_t* dest, e_char_t const* src)
{
	EXTL_ASSERT(src != NULL);
	EXTL_ASSERT(dest != NULL);

	return atow(dest, src, src == NULL? 0 : std_strlen(src) + 1);
}

#ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
/// atow
template < e_size_t N >
EXTL_INLINE e_wchar_t const* atow(e_wchar_t (&dest)[N], e_char_t const* src)
{
	EXTL_ASSERT(src != NULL);
	EXTL_ASSERT(dest != NULL);
	return atow(&dest[0], src, N);
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * a2w conversion shim implementaion
 */
template<e_size_t MAX_NUM> /* MAX_NUM: The maximum number of the characters */
class a2w_impl
	: public stack_buffer	<	e_wchar_t
							,	MAX_NUM
							,	typename_type_k memory_traits_selector<e_wchar_t>::memory_traits_type
							>
{
	private:
		typedef stack_buffer	<	e_wchar_t
								,	MAX_NUM
								,	typename_type_k memory_traits_selector<e_wchar_t>::memory_traits_type
								>								base_type;

	public:
		typedef a2w_impl<MAX_NUM>								class_type;
		typedef typename_type_k base_type::size_type			size_type;
		typedef e_char_t										src_type;	
		typedef typename_type_k base_type::value_type			dest_type;
		typedef typename_type_k base_type::pointer				pointer;
	
	public:
		explicit_k a2w_impl(src_type const* src)
			: base_type(std_strlen(src) + 1)
		{
			convert(src);
		}
	public:
		operator dest_type const*() const
		{
			return this->data();
		}
	private:
		void convert(src_type const* src)
		{
			const size_type n = this->size();
			const pointer p = this->data();
			atow(p, src, n);
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

/// a2w conversion shim 
typedef EXTL_NS_DETAIL(a2w_impl)<EXTL_MEMORY_STACK_BUFFER_MAX_SPACE>	a2w;

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_CONVERSION_ATOW_TEST_ENABLE
#	include "unit_test/atow_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_ATOW_H */
/* //////////////////////////////////////////////////////////////////// */
