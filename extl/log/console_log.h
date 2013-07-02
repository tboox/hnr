/* ///////////////////////////////////////////////////////////////////////
 * File:		console_log.h		
 *
 * Created:		08.06.08				
 * Updated:		08.06.08
 *
 * Brief: console_log class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_LOG_CONSOLE_LOG_H
#define EXTL_LOG_CONSOLE_LOG_H

/*!\file console_log.h
 * \brief console_log class
 */
#ifndef __cplusplus
#	error console_log.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "console_report_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief console_log class
 *
 * \param The character type
 * \param RECORD_MAX_SIZE The maximum size of the record string 
 * \ingroup extl_group_log
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template<	typename_param_k C
		,	e_size_t RECORD_MAX_SIZE = EXTL_LOG_RECORD_MAX_SIZE 
		>
#else
template<	typename_param_k C
		,	e_size_t RECORD_MAX_SIZE 
		>
#endif
struct basic_console_log
	: public log_base<C, console_report_traits, RECORD_MAX_SIZE>
{
};

typedef basic_console_log<e_char_t, EXTL_LOG_RECORD_MAX_SIZE>		console_log_a;
typedef basic_console_log<e_wchar_t, EXTL_LOG_RECORD_MAX_SIZE>		console_log_w;
typedef basic_console_log<e_tchar_t, EXTL_LOG_RECORD_MAX_SIZE>		console_log;
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_LOG_CONSOLE_LOG_H */
/* //////////////////////////////////////////////////////////////////// */
