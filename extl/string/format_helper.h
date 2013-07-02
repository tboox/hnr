/* ///////////////////////////////////////////////////////////////////////
 * File:		format_helper.h		
 *
 * Created:		08.04.30				
 * Updated:		08.04.30
 *
 * Brief: The helpful macros of formating string 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_FORMAT_HELPER_H
#define EXTL_STRING_FORMAT_HELPER_H

/*!\file format_helper.h
 * \brief The helpful macros of formating string 
 */

#ifndef __cplusplus
#	error format_helper.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h"
#include "../type/typedef.h"
#include "../utility/suppress_unused.h"
#include "../string/std/functions.h" /* for std_vsnprintf */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Format string  
 */

/// \name macros
/// @{
#define EXTL_FORMAT_HELPER(string, max_size, format)								\
do{																					\
va_list arglist;																	\
va_start(arglist, format);															\
EXTL_NS(std_vsnprintf)(string, max_size, format, arglist);							\
va_end(arglist);																	\
}while (0)																			

#define EXTL_FORMAT_HELPER_2(string, max_size, format, result_size)					\
do{																					\
va_list arglist;																	\
va_start(arglist, format);															\
result_size = EXTL_NS(std_vsnprintf)(string, max_size, format, arglist);			\
va_end(arglist);																	\
}while (0)																			
/// @}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_FORMAT_HELPER_H */
/* //////////////////////////////////////////////////////////////////// */
