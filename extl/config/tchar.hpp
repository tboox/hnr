/* ///////////////////////////////////////////////////////////////////////
 * File:		tchar.hpp
 *
 * Created:		08.04.28
 * Updated:		08.04.28
 *
 * Brief: Generic International Text Function Macros
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONFIG_TCHAR_H
#define EXTL_CONFIG_TCHAR_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

#ifndef EXTL_CONFIG_COMPILER_H
#	error This file must be depended on compiler\config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unicode character-set
 */
#if defined(EXTL_UNICODE) || defined(UNICODE) || defined(_UNICODE)

#	ifndef EXTL_UNICODE
#		define EXTL_UNICODE
#	endif

#	ifndef UNICODE
#		define UNICODE
#	endif

#	ifndef _UNICODE
#		define _UNICODE
#	endif

#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include <stdio.h>
#include <ctype.h> /* for isdigit */
#include <wchar.h>

/* ///////////////////////////////////////////////////////////////////////
 * _T() macro
 */
#ifdef _T
#	undef _T
#endif 

#ifdef EXTL_UNICODE
#	define _T(s)	L ## s
#else
#	define _T(s)	s
#endif

/* ///////////////////////////////////////////////////////////////////////
 * char
 */
#define e_a_printf				printf
#define e_a_fprintf				fprintf

#define e_a_sprintf				sprintf
#define e_a_vsnprintf			_vsnprintf

#define e_a_fopen				fopen
#define e_a_fsopen				_fsopen

/* ctype-functions */
#define e_a_isdigit				isdigit
#define e_a_isalpha				isalpha

/* ///////////////////////////////////////////////////////////////////////
 * wchar
 */
#define e_w_printf				wprintf
#define e_w_fprintf				fwprintf

#define e_w_sprintf				swprintf
#define e_w_vsnprintf			_vsnwprintf


#define e_w_fopen				_wfopen
#define e_w_fsopen				_wfsopen

/* ctype-functions */
#define e_w_isdigit				iswdigit
#define e_w_isalpha				iswalpha

/* ///////////////////////////////////////////////////////////////////////
 * tchar
 */
#ifndef EXTL_UNICODE

/* format functions */
#	define e_t_printf			e_a_printf
#	define e_t_fprintf			e_a_fprintf

#	define e_t_sprintf			e_a_sprintf
#	define e_t_vsnprintf		e_a_vsnprintf

/* file operations */
#	define e_t_fopen			e_a_fopen
#	define e_t_fsopen			e_a_fsopen

/* ctype-functions */
#	define e_t_isdigit			e_a_isdigit
#	define e_t_isalpha			e_a_isalpha

#else

/* format functions */
#	define e_t_printf			e_w_printf
#	define e_t_fprintf			e_w_fprintf

#	define e_t_sprintf			e_w_sprintf
#	define e_t_vsnprintf		e_w_vsnprintf

/* file operations */
#	define e_t_fopen			e_w_fopen
#	define e_t_fsopen			e_w_fsopen

/* ctype-functions */
#	define e_t_isdigit			e_w_isdigit
#	define e_t_isalpha			e_w_isalpha

#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_TCHAR_H */
/* //////////////////////////////////////////////////////////////////// */
