/* ///////////////////////////////////////////////////////////////////////
 * File:		critical_section.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.05
 *
 * Brief: critical section object class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_CRITICAL_SECTION_H
#define EXTL_WIN_SYNCH_CRITICAL_SECTION_H

/*!\file critical_section.h
 * \brief critical section object class
 */
#ifndef __cplusplus
#	error critical_section.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../utility/uncopyable.h"

#if defined(EXTL_EXCEPTION_SUPPORT) && \
		defined(EXTL_EXCEPTION_ENABLE)
#	include "../error/win_synch_error.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief critical_section class 
 * \ingroup extl_group_synch
 */
class critical_section : private uncopyable<critical_section>
{
	/// \name Types
	/// @{
	public:
		typedef critical_section		class_type;
		typedef LPCRITICAL_SECTION		handle_type;
		typedef CRITICAL_SECTION		synch_object_type;
	/// @}

	private:
		/// The critical section object
		synch_object_type				m_cs_obj;

	/// \name Constructors
	/// @{
	public:
		explicit_k critical_section()
		: m_cs_obj(initialize_critical_section_())
		{
		}

	public:
		virtual ~critical_section() EXTL_THROW_0()
		{
			::DeleteCriticalSection(&m_cs_obj);
		}
	/// @}

	public:
		/// Enter critical section 
		void enter()
		{
			::EnterCriticalSection(&m_cs_obj);
		}

		/// Try entering critical section 
		e_bool_t try_enter()
		{
		#if(_WIN_WINNT >= 0x0400)
			return (BOOL2bool(::TryEnterCriticalSection(&m_cs_obj)));
		#else
			return e_false_v;
		#endif
		}

		/// Leave critical section 
		void leave()
		{
			::LeaveCriticalSection(&m_cs_obj);
		}

	public:
		/// Returns object handle 
		operator handle_type() const
		{
			return const_cast<handle_type>(&m_cs_obj);
		}
		/// Returns object handle 
		handle_type get_handle() const
		{
			return const_cast<handle_type>(&m_cs_obj);
		}

	private:
		synch_object_type initialize_critical_section_()
		{
			synch_object_type cs_obj;
			::InitializeCriticalSection(&cs_obj);
			return cs_obj;
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_CRITICAL_SECTION_H */
/* //////////////////////////////////////////////////////////////////// */
