/* ///////////////////////////////////////////////////////////////////////
 * File:		event.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.05
 *
 * Brief: event object class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_EVENT_H
#define EXTL_WIN_SYNCH_EVENT_H

/*!\file event.h
 * \brief event object class
 */
#ifndef __cplusplus
#	error event.h need be supported by c++.
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

/*!\brief event class 
 * \ingroup extl_group_synch
 */
class event : private uncopyable<event>
{
	/// \name Types
	/// @{
	public:
		typedef event				class_type;
		typedef HANDLE				handle_type;
		typedef HANDLE				synch_object_type;
	/// @}

	private:
		/// The event object
		synch_object_type			m_event_obj;

	/// \name Constructors
	/// @{
	public:
		event()
			: m_event_obj(NULL)
		{
		}
		explicit_k event(e_bool_t bManualreset, e_bool_t bInitialState,
							LPSECURITY_ATTRIBUTES psa = NULL)
		: m_event_obj(create_event_(psa, bManualreset, bInitialState, NULL))
		{
		}
		explicit_k event(e_tchar_t const* szName, e_bool_t bManualreset, 
							e_bool_t bInitialState, LPSECURITY_ATTRIBUTES psa = NULL)
		: m_event_obj(create_event_(psa, bManualreset, bInitialState, szName))
		{
		}
		virtual ~event() EXTL_THROW_0()
		{
			if(NULL != m_event_obj)
			{
				::CloseHandle(m_event_obj);
				m_event_obj = NULL;
			}
		}
	/// @}
	public:
		/// Sets the event 
		e_bool_t set_event()
		{
			EXTL_ASSERT(NULL != m_event_obj);

			if(!::SetEvent(m_event_obj))
			{
				EXTL_THROW_E(win_synch_error("SetEvent operation failed"));
				return e_false_v;
			}
			else return e_true_v;
		}

		/// Resets the event 
		e_bool_t reset_event()
		{
			EXTL_ASSERT(NULL != m_event_obj);

			if(!::ResetEvent(m_event_obj))
			{
				EXTL_THROW_E(win_synch_error("reset_event operation failed"));
				return e_false_v;
			}
			else return e_true_v;
		}
		/// Pulses the event 
		e_bool_t pulse_event()
		{
			EXTL_ASSERT(NULL != m_event_obj);

			if(!::PulseEvent(m_event_obj))
			{
				EXTL_THROW_E(win_synch_error("PulseEvent operation failed"));
				return e_false_v;
			}
			else return e_true_v;
		}
	public:
		/// Returns object handle 
		operator handle_type() const
		{
			return m_event_obj;
		}
		/// Returns object handle
		handle_type get_handle() const
		{
			return m_event_obj;
		}

		/// Create event 
		void create(e_bool_t bManualreset, e_bool_t bInitialState,
							LPSECURITY_ATTRIBUTES psa = NULL)
		{
			m_event_obj = create_event_(psa, bManualreset, bInitialState, NULL);
		}

		/// Create event 
		void create(e_tchar_t const* szName, e_bool_t bManualreset, 
							e_bool_t bInitialState, LPSECURITY_ATTRIBUTES psa = NULL)
		{
			m_event_obj = create_event_(psa, bManualreset, bInitialState, szName);
		}


	private:
		synch_object_type create_event_(LPSECURITY_ATTRIBUTES psa, e_bool_t bManualreset, e_bool_t bInitialState, e_tchar_t const* pszName)
		{
			synch_object_type event_obj = ::CreateEvent(psa, bManualreset, bInitialState, pszName);
			EXTL_ASSERT_THROW(event_obj != NULL, win_synch_error("Failed to create kernel event object"));
			return event_obj;
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_EVENT_H */
/* //////////////////////////////////////////////////////////////////// */
