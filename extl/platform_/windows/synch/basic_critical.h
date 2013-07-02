/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_critical.h		
 *
 * Created:		08.03.20				
 * Updated:		08.11.26
 *
 * Brief:		The Critical Section
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_CRITICAL_SECTION_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_CRITICAL_SECTION_H

/*!\file basic_critical.h
 * \brief The Critical Section
 */
#ifndef __cplusplus
#	error basic_critical.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../utility/uncopyable.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief basic_critical class 
 * 
 * \ingroup extl_group_synch
 */
class basic_critical
	: private uncopyable<basic_critical>
{
	/// \name Types
	/// @{
	public:
		typedef basic_critical						class_type;
		typedef LPCRITICAL_SECTION					handle_type;
		typedef CRITICAL_SECTION					critical_type;
		typedef e_bool_t							bool_type;
	/// @}

	/// \name Members
	/// @{
	private:
		critical_type								m_cs;
	///@}

	/// \name Constructors
	/// @{
	public:
		basic_critical()
			: m_cs(initialize_critical_section())
		{
		}
		~basic_critical() EXTL_THROW_0()
		{
			::DeleteCriticalSection(&m_cs);
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialize critical section
		static critical_type initialize_critical_section()
		{
			critical_type cs;
			::InitializeCriticalSection(&cs);
			return cs;
		}
		/// enter critical section 
		void enter()
		{
			::EnterCriticalSection(handle());
		}

		/// try entering critical section 
		bool_type try_enter()
		{
		#if(_WINDOWS_WINNT >= 0x0400)
			return (BOOL2bool(::TryEnterCriticalSection(handle())));
		#else
			return e_false_v;
		#endif
		}

		/// leave critical section 
		void leave()
		{
			::LeaveCriticalSection(handle());
		}
	/// @}

	/// \name Accessors 
	/// @{
	public:
		/// gets object handle
		handle_type			handle() const					{ return const_cast<handle_type>(&m_cs);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_CRITICAL_SECTION_H */
/* //////////////////////////////////////////////////////////////////// */
