/* ///////////////////////////////////////////////////////////////////////
 * File:		file_log.h		
 *
 * Created:		08.06.08				
 * Updated:		08.06.08
 *
 * Brief: file_log class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_LOG_FILE_LOG_H
#define EXTL_LOG_FILE_LOG_H

/*!\file file_log.h
 * \brief file_log class
 */
#ifndef __cplusplus
#	error file_log.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "file_report_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template <typename_param_k T>
struct file_log_traits{};

EXTL_TEMPLATE_SPECIALISATION
struct file_log_traits<e_char_t>
{
	typedef FILE*		handle_type;
	typedef e_char_t	char_type;

	static handle_type open(char_type const* filename, char_type const* flag)
	{
		return e_a_fopen(filename, flag);
	}

	static char_type const* default_flag()
	{
		return "w";
	}
};

EXTL_TEMPLATE_SPECIALISATION
struct file_log_traits<e_wchar_t>
{
	typedef FILE*		handle_type;
	typedef e_wchar_t	char_type;

	static handle_type open(char_type const* filename, char_type const* flag)
	{
	/* DMC: _fwopen will collapse to unicode character set */
	#if defined(EXTL_COMPILER_IS_DMC) && defined(EXTL_UNICODE)
		return e_w_fsopen(filename, flag, 1);
	#else
		return e_w_fopen(filename, flag);
	#endif
	}
	static char_type const* default_flag()
	{
		return L"w";
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
/*!\brief file_log class
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
class basic_file_log
	: public log_base<C, file_report_traits, RECORD_MAX_SIZE>
{
	/// \name Types
	/// @{
	public:
		typedef log_base<C, file_report_traits, RECORD_MAX_SIZE>	base_type;
		typedef file_report_traits									report_traits_type;
		typedef basic_file_log<C, RECORD_MAX_SIZE>					class_type;
		typedef C													char_type;
		typedef EXTL_NS_DETAIL(file_log_traits)<C>					file_log_traits_type;
		typedef FILE*												handle_type;
	/// @}

	private:
		/// The file handle
		handle_type													m_hfile;

#ifdef EXTL_COMPILER_IS_VECTORC
	public:
#else
	private:
#endif
		static char_type const* default_flag()
		{
			return file_log_traits_type::default_flag();
		}

	/// \name Constructors
	/// @{
	public:
		basic_file_log()
			: base_type()
		{
		}
		basic_file_log(char_type const* filename, char_type const* flag = default_flag())
			: base_type(report_traits_type(open(filename, flag)))
		{
		}
		~basic_file_log()
		{
			close();
		}
	/// @}

	/// \name Opens and closes the file log
	/// @{
	public:
		handle_type open(char_type const* filename, char_type const* flag = default_flag())
		{
			EXTL_ASSERT(NULL != filename);
			EXTL_ASSERT(NULL != flag);

			m_hfile = file_log_traits_type::open(filename, flag);
			return m_hfile;
		}
		void close()
		{
			if(NULL != m_hfile)
			{
				fclose(m_hfile);
				m_hfile = NULL;
			}
		}
	/// @}
};

typedef basic_file_log<e_char_t, EXTL_LOG_RECORD_MAX_SIZE>	file_log_a;
typedef basic_file_log<e_wchar_t, EXTL_LOG_RECORD_MAX_SIZE>	file_log_w;
typedef basic_file_log<e_tchar_t, EXTL_LOG_RECORD_MAX_SIZE>	file_log;
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_LOG_FILE_LOG_H */
/* //////////////////////////////////////////////////////////////////// */
