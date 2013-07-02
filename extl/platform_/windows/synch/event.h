/* ///////////////////////////////////////////////////////////////////////
 * File:		event.h		
 *
 * Created:		08.03.20				
 * Updated:		08.11.26
 *
 * Brief:		The Event Object
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_EVENT_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_EVENT_H

/*!\file event.h
 * \brief The Event Object
 */
#ifndef __cplusplus
#	error event.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../utility/uncopyable.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief event class 
 *
 * \ingroup extl_group_synch
 */
class event 
	: private uncopyable<event>
{
	/// \name Types
	/// @{
	public:
		typedef event						class_type;
		typedef HANDLE						handle_type;
		typedef e_bool_t					bool_type;
		typedef LPSECURITY_ATTRIBUTES		psa_type;
		typedef e_tchar_t					char_type;
	/// @}

	/// \name Members
	/// @{
	private:
		handle_type							m_he;
	/// @}

	/// \name Constructors
	/// @{
	public:
		event()
			: m_he(NULL)
		{}
		explicit_k event(bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
			: m_he(NULL)
		{
			create(is_manual_reset, is_initial, psa);
		}
		explicit_k event(char_type const* name, bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
			: m_he(NULL)
		{
			create(name, is_manual_reset, is_initial, psa);
		}
		virtual ~event() EXTL_THROW_0()
		{
			if(NULL != handle())
			{
				::CloseHandle(handle());
				m_he = NULL;
			}
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// create event - static
		static handle_type create_event(char_type const* name, bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
		{
			handle_type he = ::CreateEvent(psa, is_manual_reset, is_initial, name);
			EXTL_ASSERT_THROW(hm != NULL, windows_synch_error("failed to create kernel event object"));
			return he;
		}
		/// create event 
		bool_type create(bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the event object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the event object has been created");

			if (NULL == handle())
			{
				m_he = create_event(NULL, is_manual_reset, is_initial, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}

		/// create event 
		bool_type create(char_type const* name, bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the event object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the event object has been created");

			if (NULL == handle())
			{
				m_he = create_event(name, is_manual_reset, is_initial, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// set event 
		bool_type set()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the event object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the event object hasn't been created"));

			if (NULL == handle() || !::SetEvent(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to set event"));
				return e_false_v;
			}
			else return e_true_v;
		}

		/// reset event 
		bool_type reset()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the event object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the event object hasn't been created"));

			if (NULL == handle() || !::ResetEvent(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to reset event"));
				return e_false_v;
			}
			else return e_true_v;
		}
		/// pulse event 
		bool_type pulse()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the event object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the event object hasn't been created"));

			if(NULL == handle() || !::PulseEvent(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to pulse event"));
				return e_false_v;
			}
			else return e_true_v;
		}
	/// @}

	/// \name Accessors 
	/// @{
	public:
		/// gets object handle
		operator			handle_type() const				{ return m_he;	}
		/// gets object handle
		handle_type			handle() const					{ return m_he;	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_EVENT_H */
/* //////////////////////////////////////////////////////////////////// */
