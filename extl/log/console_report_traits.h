/* ///////////////////////////////////////////////////////////////////////
 * File:		console_report_traits.h		
 *
 * Created:		08.06.08				
 * Updated:		08.06.08
 *
 * Brief: console_report_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_LOG_CONSOLE_REPORT_TRAITS_H
#define EXTL_LOG_CONSOLE_REPORT_TRAITS_H

/*!\file console_report_traits.h
 * \brief console_report_traits class
 */
#ifndef __cplusplus
#	error console_report_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "log_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief console_report_traits class
 *
 * \ingroup extl_group_log
 */
struct console_report_traits
{
	/// Reports the given string
	void operator()(e_char_t const* record_str)
	{
		EXTL_ASSERT(NULL != record_str);
		if(NULL != record_str) e_a_printf(record_str);
	}
	/// Reports the given string
	void operator()(e_wchar_t const* record_str)
	{
		EXTL_ASSERT(NULL != record_str);
		if(NULL != record_str) e_w_printf(record_str);
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_LOG_CONSOLE_REPORT_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */

