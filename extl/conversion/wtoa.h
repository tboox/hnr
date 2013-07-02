/* ///////////////////////////////////////////////////////////////////////
 * File:		wtoa.h		
 *
 * Created:		08.03.11				
 * Updated:		08.05.09
 *
 * Brief: UNICODE ==> ASCII
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_WTOA_H
#define EXTL_CONVERSION_WTOA_H

/*!\file wtoa.h
 * \brief UNICODE ==> ASCII
 * 
 * - wtoa: conversion function and needs to provide buffer 
 * - w2a: conversion shim and does'nt need to provide buffer 
 *   - Note: It's rather dangerous because the life cycle of it's buffer is so short
 *   - eg: 
 *     - e_char_t *p = w2a(pChar);
 *     - printf(p);					<== Undefined!
 *     - printf(L"%s", w2a(pChar));	<== Undefined!
 *     - printf(w2a(pChar));			<== Safe
 *
 */
#ifndef __cplusplus
#	error wtoa.h need be supported by c++.
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

/// wtoa
EXTL_INLINE e_char_t const* wtoa(e_char_t* dest, e_wchar_t const* src, e_size_t n)
{
	EXTL_ASSERT(src != NULL);
	EXTL_ASSERT(dest != NULL);

	if(dest == NULL) return dest;

	if(0 == n || src == NULL) 
	{
		dest[0] = e_wchar_t('\0');
		return dest;
	}

	if(static_cast<e_size_t>(-1) == ::wcstombs(dest, src, n))
	{
		dest[0] = e_wchar_t('\0');
	}
	else dest[n - 1] = e_wchar_t('\0');

	return dest;
}
/// wtoa
EXTL_INLINE e_char_t const* wtoa(e_char_t* dest, e_wchar_t const* src)
{
	EXTL_ASSERT(src != NULL);
	EXTL_ASSERT(dest != NULL);

	return wtoa(dest, src, std_strlen(src) + 1);
}

#ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
/// wtoa
template < e_size_t N >
EXTL_INLINE e_char_t const* wtoa(e_char_t (&dest)[N], e_wchar_t const* src)
{
	EXTL_ASSERT(src != NULL);
	EXTL_ASSERT(dest != NULL);

	return wtoa(&dest[0], src, N);
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * w2a conversion shim implementaion
 */
template<e_size_t MAX_NUM> /* MAX_NUM: The maximum number of the characters */
class w2a_impl
	: public stack_buffer	<	e_char_t
							,	MAX_NUM
							,	typename_type_k memory_traits_selector<e_char_t>::memory_traits_type
							>
{
	private:
		typedef stack_buffer	<	e_char_t
								,	MAX_NUM
								,	typename_type_k memory_traits_selector<e_char_t>::memory_traits_type
								>								base_type;

	public:
		typedef w2a_impl<MAX_NUM>								class_type;
		typedef typename_type_k base_type::size_type			size_type;
		typedef e_wchar_t										src_type;	
		typedef typename_type_k base_type::value_type			dest_type;
		typedef typename_type_k base_type::pointer				pointer;
	
	public:
		explicit_k w2a_impl(src_type const* src)
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

			wtoa(p, src, n);
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

/// w2a conversion shim 
typedef EXTL_NS_DETAIL(w2a_impl)<EXTL_MEMORY_STACK_BUFFER_MAX_SPACE>	w2a;

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_CONVERSION_WTOA_TEST_ENABLE
#	include "unit_test/wtoa_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_WTOA_H */
/* //////////////////////////////////////////////////////////////////// */
