/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_event.h		
 *
 * Created:		08.03.20				
 * Updated:		09.01.15
 *
 * Brief:		The Event Object
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_EVENT_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_EVENT_H

/*!\file basic_event.h
 * \brief The Event Object
 */
#ifndef __cplusplus
#	error basic_event.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../utility/uncopyable.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief basic_event class 
 *
 * \ingroup extl_group_synch
 */
class basic_event 
	: private uncopyable<basic_event>
{
	/// \name Types
	/// @{
	public:
		typedef basic_event					class_type;
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
		basic_event()
			: m_he(NULL)
		{}
		explicit_k basic_event(bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
			: m_he(NULL)
		{
			create(is_manual_reset, is_initial, psa);
		}
		explicit_k basic_event(char_type const* name, bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
			: m_he(NULL)
		{
			create(name, is_manual_reset, is_initial, psa);
		}
		~basic_event() EXTL_THROW_0()
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
		/// create basic_event - static
		static handle_type create_event(char_type const* name, bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
		{
			handle_type he = ::CreateEvent(psa, is_manual_reset, is_initial, name);
			EXTL_ASSERT_THROW(he != NULL, windows_synch_error("failed to create kernel basic_event object"));
			return he;
		}
		/// create basic_event 
		bool_type create(bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the basic_event object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the basic_event object has been created");

			if (NULL == handle())
			{
				m_he = create_event(NULL, is_manual_reset, is_initial, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}

		/// create basic_event 
		bool_type create(char_type const* name, bool_type is_manual_reset, bool_type is_initial, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the basic_event object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the basic_event object has been created");

			if (NULL == handle())
			{
				m_he = create_event(name, is_manual_reset, is_initial, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// set basic_event 
		bool_type set()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the basic_event object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the basic_event object hasn't been created"));

			if (NULL == handle() || !::SetEvent(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to set basic_event"));
				return e_false_v;
			}
			else return e_true_v;
		}

		/// reset basic_event 
		bool_type reset()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the basic_event object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the basic_event object hasn't been created"));

			if (NULL == handle() || !::ResetEvent(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to reset basic_event"));
				return e_false_v;
			}
			else return e_true_v;
		}
		/// pulse basic_event 
		bool_type pulse()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the basic_event object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the basic_event object hasn't been created"));

			if(NULL == handle() || !::PulseEvent(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to pulse basic_event"));
				return e_false_v;
			}
			else return e_true_v;
		}
	/// @}

	/// \name Attributes 
	/// @{
	public:
		handle_type			handle() const					{ return m_he;	}
		bool_type			is_valid() const
		{
			return ((handle() != NULL) && (handle() != INVALID_HANDLE_VALUE));
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_EVENT_H */
/* //////////////////////////////////////////////////////////////////// */
