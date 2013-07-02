/* ///////////////////////////////////////////////////////////////////////
 * File:		file_report_traits.h		
 *
 * Created:		08.06.08				
 * Updated:		08.06.08
 *
 * Brief: file_report_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_LOG_FILE_REPORT_TRAITS_H
#define EXTL_LOG_FILE_REPORT_TRAITS_H

/*!\file file_report_traits.h
 * \brief file_report_traits class
 */
#ifndef __cplusplus
#	error file_report_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "log_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief file_report_traits class
 *
 * \ingroup extl_group_log
 */
class file_report_traits
{
	/// \name Types
	/// @{
	public:
		typedef file_report_traits		class_type;
		typedef FILE*					handle_type;
	/// @}

	private:
		/// The file handle
		handle_type						m_hfile;

	/// \name Constructors
	/// @{
	public:
		file_report_traits()
			: m_hfile(NULL)
		{
		}
		file_report_traits(handle_type fh)
			: m_hfile(fh)
		{
		}
	/// @}

	public:
		/// Reports the given string
		void operator()(e_char_t const* record_str)
		{
			EXTL_ASSERT(NULL != m_hfile && NULL != record_str);
			if(NULL != m_hfile && NULL != record_str) 
			{
				e_a_fprintf(m_hfile, record_str);
				fflush(m_hfile);
			}
		}
		/// Reports the given string
		void operator()(e_wchar_t const* record_str)
		{
			EXTL_ASSERT(NULL != m_hfile && NULL != record_str);
			if(NULL != m_hfile && NULL != record_str) 
			{
				e_w_fprintf(m_hfile, record_str);
				fflush(m_hfile);
			}
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_LOG_FILE_REPORT_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */

