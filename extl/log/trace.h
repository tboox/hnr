/* ///////////////////////////////////////////////////////////////////////
 * File:		trace.h		
 *
 * Created:		08.06.08				
 * Updated:		08.06.08
 *
 * Brief: trace class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_LOG_TRACE_H
#define EXTL_LOG_TRACE_H

/*!\file trace.h
 * \brief trace class
 */
#ifndef __cplusplus
#	error trace.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "file_log.h"
#include "console_log.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#ifdef EXTL_TRACE_FILENAME_ENABLE
#	define EXTL_TRACE_FILENAME(trace)	trace.report_a("file: %s ", EXTL_FILENAME);
#else
#	define EXTL_TRACE_FILENAME(trace)
#endif

#ifdef EXTL_TRACE_LINENUM_ENABLE
#	define EXTL_TRACE_LINENUM(trace)	trace.report_a("line: %d ", EXTL_LINENUM);
#else
#	define EXTL_TRACE_LINENUM(trace)
#endif

#ifdef EXTL_TRACE_FUNCNAME_ENABLE
#	define EXTL_TRACE_FUNCNAME(trace)	trace.report_a("func: %s ", EXTL_CURRENT_FUNCTION);
#else
#	define EXTL_TRACE_FUNCNAME(trace)
#endif

#define EXTL_TRACE_RETURN(trace)		trace.report_a("\n");

/// Custom trace helper
#define EXTL_TRACE_(trace)				\
EXTL_TRACE_RETURN(trace)				\
EXTL_TRACE_LINENUM(trace)				\
EXTL_TRACE_FILENAME(trace)				\
EXTL_TRACE_FUNCNAME(trace)				\
EXTL_TRACE_RETURN(trace)				\
trace.report

#define EXTL_TRACE_A_(trace)			\
EXTL_TRACE_RETURN(trace)				\
EXTL_TRACE_LINENUM(trace)				\
EXTL_TRACE_FILENAME(trace)				\
EXTL_TRACE_FUNCNAME(trace)				\
EXTL_TRACE_RETURN(trace)				\
trace.report_a

#define EXTL_TRACE_W_(trace)			\
EXTL_TRACE_RETURN(trace)				\
EXTL_TRACE_LINENUM(trace)				\
EXTL_TRACE_FILENAME(trace)				\
EXTL_TRACE_FUNCNAME(trace)				\
EXTL_TRACE_RETURN(trace)				\
trace.report_w

/// Custom trace helper
#define EXTL_TRACE_2_(trace)			\
EXTL_TRACE_RETURN(trace)				\
trace.report

#define EXTL_TRACE_A_2_(trace)			\
EXTL_TRACE_RETURN(trace)				\
trace.report_a

#define EXTL_TRACE_W_2_(trace)			\
EXTL_TRACE_RETURN(trace)				\
trace.report_w

/*!Trace
 * \note EXTL_TRACE is not non-atomic
 *  \code
	e.g. 
	for (; ; ) EXTL_TRACE(_T("...")); // is incorrect
	for (; ; ) 
	{
		EXTL_TRACE(_T("..."));	// is correct
	}
 * \endcode
 */
/// @{
#ifndef EXTL_TRACE_DISABLE
#	define EXTL_TRACE					EXTL_TRACE_(EXTL_NS(g_trace))
#	define EXTL_TRACEA					EXTL_TRACE_A_(EXTL_NS(g_trace))
#	define EXTL_TRACEW					EXTL_TRACE_W_(EXTL_NS(g_trace))
#else
#	define EXTL_TRACE
#	define EXTL_TRACEA
#	define EXTL_TRACEW
#endif
/// @}

/// Unit-testing report
#define EXTL_TEST_TRACE					EXTL_TRACE_2_(EXTL_NS(g_unittest_trace))
#define EXTL_TEST_TRACEA				EXTL_TRACE_A_2_(EXTL_NS(g_unittest_trace))
#define EXTL_TEST_TRACEW				EXTL_TRACE_W_2_(EXTL_NS(g_unittest_trace))
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

#if defined(EXTL_TRACE_FILE)
/* file trace */
static file_log								g_trace(EXTL_LOG_FILE_TRACE_FILENAME);

#elif defined(EXTL_TRACE_CONSOLE)
/* console trace */
static console_log							g_trace;
#else
#	error Unknown trace.
#endif

/* Unit-testing trace */
static file_log								g_unittest_trace(EXTL_LOG_TEST_FILENAME);
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_LOG_TRACE_H */
/* //////////////////////////////////////////////////////////////////// */
