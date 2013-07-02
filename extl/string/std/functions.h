/* ///////////////////////////////////////////////////////////////////////
 * File:		functions.h		
 *
 * Created:		08.03.10					
 * Updated:		08.04.14	
 *
 * Brief: std string operation
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_STD_FUNCTIONS_H
#define EXTL_STRING_STD_FUNCTIONS_H

/*!\file functions.h
 * \brief std string operation
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include <string.h>
#include <stdarg.h>

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/// get the length of the given string 
EXTL_INLINE e_size_t std_strlen_a(e_char_t const* s)
{
	return (s == NULL)? 0 : EXTL_NS_GLOBAL(strlen)(s);
}
/// get the length of the given string 
EXTL_INLINE e_size_t std_strlen_w(e_wchar_t const* s)
{
	return (s == NULL)? 0 : EXTL_NS_GLOBAL(wcslen)(s);
}
/// copy 
EXTL_INLINE e_char_t const* std_strcpy_a(e_char_t* dest, e_char_t const* src)
{
	return EXTL_NS_GLOBAL(strcpy)(dest, src);
}
/// copy 
EXTL_INLINE e_wchar_t const* std_strcpy_w(e_wchar_t* dest, e_wchar_t const* src)
{
	return EXTL_NS_GLOBAL(wcscpy)(dest, src);
}
/// compare 
EXTL_INLINE e_int_t std_strcmp_a(e_char_t const* lhs, e_char_t const* rhs)
{
	return EXTL_NS_GLOBAL(strcmp)(lhs, rhs);
}
/// compare 
EXTL_INLINE e_int_t std_strcmp_w(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	return EXTL_NS_GLOBAL(wcscmp)(lhs, rhs);
}

/* ///////////////////////////////////////////////////////////////////////
 * function overload 
 */
#ifdef __cplusplus

/// length 
EXTL_INLINE e_size_t std_strlen(e_char_t const* s)
{
	return std_strlen_a(s);
}
/// length 
EXTL_INLINE e_size_t std_strlen(e_wchar_t const* s)
{
	return std_strlen_w(s);
}
/// copy 
EXTL_INLINE e_char_t const* std_strcpy(e_char_t* dest, e_char_t const* src)
{
	return std_strcpy_a(dest, src);
}
/// copy 
EXTL_INLINE e_wchar_t const* std_strcpy(e_wchar_t* dest, e_wchar_t const* src)
{
	return std_strcpy_w(dest, src);
}

/// compare 
EXTL_INLINE e_int_t std_strcmp(e_char_t const* lhs, e_char_t const* rhs)
{
	return std_strcmp_a(lhs, rhs);
}
/// compare 
EXTL_INLINE e_int_t std_strcmp(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	return std_strcmp_w(lhs, rhs);
}
/// _vsnprintf/_vsnwprintf 
EXTL_INLINE e_int_t std_vsnprintf(e_char_t* string, e_size_t max_size, e_char_t const* format, va_list arglist)
{
	return e_a_vsnprintf(string, max_size, format, arglist);
}
/// _vsnprintf/_vsnwprintf 
EXTL_INLINE e_int_t std_vsnprintf(e_wchar_t* string, e_size_t max_size, e_wchar_t const* format, va_list arglist)
{
	return e_w_vsnprintf(string, max_size, format, arglist);
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_STD_FUNCTIONS_H */
/* //////////////////////////////////////////////////////////////////// */
