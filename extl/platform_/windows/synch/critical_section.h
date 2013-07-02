/* ///////////////////////////////////////////////////////////////////////
 * File:		critical_section.h		
 *
 * Created:		08.03.20				
 * Updated:		08.11.26
 *
 * Brief:		The Critical Section
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_CRITICAL_SECTION_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_CRITICAL_SECTION_H

/*!\file critical_section.h
 * \brief The Critical Section
 */
#ifndef __cplusplus
#	error critical_section.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../utility/uncopyable.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE


/*!\brief critical_section class 
 * 
 * \ingroup extl_group_synch
 */
class critical_section
	: private uncopyable<critical_section>
{
	/// \name Types
	/// @{
	public:
		typedef critical_section			class_type;
		typedef LPCRITICAL_SECTION			handle_type;
		typedef CRITICAL_SECTION			crsec_type;
		typedef e_bool_t					bool_type;
	/// @}

	/// \name Members
	/// @{
	private:
		crsec_type							m_cs;
	///@}

	/// \name Constructors
	/// @{
	public:
		critical_section()
			: m_cs(initialize_critical_section())
		{
		}
		virtual ~critical_section() EXTL_THROW_0()
		{
			::DeleteCriticalSection(&m_cs);
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialize critical section
		static crsec_type initialize_critical_section()
		{
			crsec_type cs;
			::InitializeCriticalSection(&cs);
			return cs;
		}
		/// enter critical section 
		void enter()
		{
			::EnterCriticalSection(&m_cs);
		}

		/// try entering critical section 
		bool_type try_enter()
		{
		#if(_WIN_WINNT >= 0x0400)
			return (BOOL2bool(::TryEnterCriticalSection(&m_cs)));
		#else
			return e_false_v;
		#endif
		}

		/// leave critical section 
		void leave()
		{
			::LeaveCriticalSection(&m_cs);
		}
	/// @}

	/// \name Accessors 
	/// @{
	public:
		/// gets object handle
		operator			handle_type() const				{ return const_cast<handle_type>(&m_cs);	}
		/// gets object handle
		handle_type			handle() const					{ return const_cast<handle_type>(&m_cs);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_CRITICAL_SECTION_H */
/* //////////////////////////////////////////////////////////////////// */
