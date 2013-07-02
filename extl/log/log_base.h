/* ///////////////////////////////////////////////////////////////////////
 * File:		log_base.h		
 *
 * Created:		08.06.07				
 * Updated:		08.06.07
 *
 * Brief: log_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_LOG_LOGBASE_H
#define EXTL_LOG_LOGBASE_H

/*!\file log_base.h
 * \brief log_base class
 */
#ifndef __cplusplus
#	error log_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include <stdlib.h>
#include "../config/config.h" 
#include "../type/typedef.h"
#include "../platform/utility/assert.h"
#include "../string/format_helper.h"
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_LOG_RECORD_MAX_SIZE	512

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	typename_param_k S
		,	typename_param_k D
		>
struct convert_traits
{
	typedef e_size_t	size_type;

	static e_char_t const* convert(e_char_t* dest, e_char_t const* /*src*/, size_type /*n*/)
	{
		return dest;
	}
	static e_wchar_t const* convert(e_wchar_t* dest, e_wchar_t const* /*src*/, size_type /*n*/)
	{
		return dest;
	}
};

EXTL_TEMPLATE_SPECIALISATION
struct convert_traits<e_char_t, e_wchar_t>
{
	typedef e_char_t	src_type;
	typedef e_wchar_t	dest_type;
	typedef e_size_t	size_type;

	static dest_type const* convert(dest_type* dest, src_type const* src, size_type n)
	{
		if(dest == NULL) return dest;
		if(0 == n || src == NULL) 
		{
			dest[0] = dest_type('\0');
			return dest;
		}

		if(static_cast<e_size_t>(-1) == ::mbstowcs(dest, src, n))
		{
			dest[0] = dest_type('\0');
		}
		else dest[n - 1] = dest_type('\0');

		return dest;
	}
};

EXTL_TEMPLATE_SPECIALISATION
struct convert_traits<e_wchar_t, e_char_t>
{
	typedef e_wchar_t	src_type;
	typedef e_char_t	dest_type;
	typedef e_size_t	size_type;

	static dest_type const* convert(dest_type* dest, src_type const* src, size_type n)
	{
		if(dest == NULL) return dest;
		if(0 == n || src == NULL) 
		{
			dest[0] = dest_type('\0');
			return dest;
		}

		if(static_cast<e_size_t>(-1) == ::wcstombs(dest, src, n))
		{
			dest[0] = dest_type('\0');
		}
		else dest[n - 1] = dest_type('\0');

		return dest;
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

/*!\brief log_base class
 *
 * \param The character type
 * \param RT The report traits type
 *
 * \ingroup extl_group_log
 */
template<	typename_param_k C
		,	typename_param_k RT
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t RECORD_MAX_SIZE = EXTL_LOG_RECORD_MAX_SIZE
#else
		,	e_size_t RECORD_MAX_SIZE
#endif
		>
class log_base
	: protected RT
{
	/// \name Types
	/// @{
	public:
		typedef C										char_type;
		typedef log_base<C, RT, RECORD_MAX_SIZE>		class_type;
		typedef RT										report_traits_type;
	/// @}

	protected:
		/// The record string
		char_type										m_record[RECORD_MAX_SIZE + 1];

	/// \name Constructors
	/// @{
	public:
		log_base()
		{}
		log_base(report_traits_type rt)
			: report_traits_type(rt)
		{}
		~log_base()
		{}
	/// @}

	public:
		/// Reports the given format string
		void EXTL_CDECL report(char_type const* format_str, ...)
		{
			EXTL_ASSERT(NULL != format_str);
			EXTL_FORMAT_HELPER(m_record, RECORD_MAX_SIZE, format_str);
			report_traits_type::operator()(m_record);
		}
		/// Reports the given format string
		void EXTL_CDECL report_a(e_char_t const* format_str, ...)
		{
			EXTL_ASSERT(NULL != format_str);
			e_char_t buffer[RECORD_MAX_SIZE];
			EXTL_FORMAT_HELPER(buffer, RECORD_MAX_SIZE, format_str);
			EXTL_NS_DETAIL(convert_traits)<e_char_t, char_type>::convert(m_record, buffer, RECORD_MAX_SIZE);
			report_traits_type::operator()(m_record);
		}
		/// Reports the given format string
		void EXTL_CDECL report_w(e_wchar_t const* format_str, ...)
		{
			EXTL_ASSERT(NULL != format_str);
			e_wchar_t buffer[RECORD_MAX_SIZE];
			EXTL_FORMAT_HELPER(buffer, RECORD_MAX_SIZE, format_str);
			EXTL_NS_DETAIL(convert_traits)<e_wchar_t, char_type>::convert(m_record, buffer, RECORD_MAX_SIZE);
			report_traits_type::operator()(m_record);
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_LOG_LOGBASE_H */
/* //////////////////////////////////////////////////////////////////// */

