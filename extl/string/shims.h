/* ///////////////////////////////////////////////////////////////////////
 * File:		shims.h		
 *
 * Created:		08.06.28				
 * Updated:		08.06.28	
 *
 * Brief: c-style string operation shims
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_SHIMS_H
#define EXTL_STRING_SHIMS_H

/*!\file shims.h
 * \brief c-style string operation shims
 */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/// get the length of the given string 
EXTL_INLINE e_size_t c_strlen_a(e_char_t const* s)
{
	return (s == NULL)? 0 : EXTL_NS_GLOBAL(strlen)(s);
}
/// get the length of the given string 
EXTL_INLINE e_size_t c_strlen_w(e_wchar_t const* s)
{
	return (s == NULL)? 0 : EXTL_NS_GLOBAL(wcslen)(s);
}
/// get the pointer of the given string 
EXTL_INLINE e_char_t const* c_strptr_a(e_char_t const* s)
{
	return s;
}
/// get the pointer of the given string 
EXTL_INLINE e_wchar_t const* c_strptr_w(e_wchar_t const* s)
{
	return s;
}
/// copy 
EXTL_INLINE e_char_t const* c_strcpy_a(e_char_t* dest, e_char_t const* src)
{
	return EXTL_NS_GLOBAL(strcpy)(dest, src);
}
/// copy 
EXTL_INLINE e_wchar_t const* c_strcpy_w(e_wchar_t* dest, e_wchar_t const* src)
{
	return EXTL_NS_GLOBAL(wcscpy)(dest, src);
}
/// compare 
EXTL_INLINE e_int_t c_strcmp_a(e_char_t const* lhs, e_char_t const* rhs)
{
	return EXTL_NS_GLOBAL(strcmp)(lhs, rhs);
}
/// compare 
EXTL_INLINE e_int_t c_strcmp_w(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	return EXTL_NS_GLOBAL(wcscmp)(lhs, rhs);
}

/* ///////////////////////////////////////////////////////////////////////
 * function overload 
 */
#ifdef __cplusplus

/// length 
EXTL_INLINE e_size_t c_strlen(e_char_t const* s)
{
	return c_strlen_a(s);
}
/// length 
EXTL_INLINE e_size_t c_strlen(e_wchar_t const* s)
{
	return c_strlen_w(s);
}
/// get the pointer of the given string 
EXTL_INLINE e_char_t const* c_strptr(e_char_t const* s)
{
	return s;
}
/// get the pointer of the given string 
EXTL_INLINE e_wchar_t const* c_strptr(e_wchar_t const* s)
{
	return s;
}
/// copy 
EXTL_INLINE e_char_t const* c_strcpy(e_char_t* dest, e_char_t const* src)
{
	return c_strcpy_a(dest, src);
}
/// copy 
EXTL_INLINE e_wchar_t const* c_strcpy(e_wchar_t* dest, e_wchar_t const* src)
{
	return c_strcpy_w(dest, src);
}

/// compare 
EXTL_INLINE e_int_t c_strcmp(e_char_t const* lhs, e_char_t const* rhs)
{
	return c_strcmp_a(lhs, rhs);
}
/// compare 
EXTL_INLINE e_int_t c_strcmp(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	return c_strcmp_w(lhs, rhs);
}
/// _vsnprintf/_vsnwprintf 
EXTL_INLINE e_int_t c_vsnprintf(e_char_t* string, e_size_t max_size, e_char_t const* format, va_list arglist)
{
	return e_a_vsnprintf(string, max_size, format, arglist);
}
/// _vsnprintf/_vsnwprintf 
EXTL_INLINE e_int_t c_vsnprintf(e_wchar_t* string, e_size_t max_size, e_wchar_t const* format, va_list arglist)
{
	return e_w_vsnprintf(string, max_size, format, arglist);
}

#endif


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_SHIMS_H */
/* //////////////////////////////////////////////////////////////////// */
