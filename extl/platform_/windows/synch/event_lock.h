/* ///////////////////////////////////////////////////////////////////////
 * File:		event_lock.h		
 *
 * Created:		08.03.21				
 * Updated:		09.01.12
 *
 * Brief: event_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_EVENT_LOCK_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_EVENT_LOCK_H

/*!\file event_lock.h
 * \brief event_lock class
 */
#ifndef __cplusplus
#	error event_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../synch/lock_base.h" 
#include "basic_event.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief event_lock class 
 * 
 * \ingroup extl_group_synch
 */
class event_lock
	: public lock_base<event_lock>
{
	/// \name Types
	/// @{
	public:
		typedef lock_base<event_lock>			base_type;
		typedef event_lock						class_type;
		typedef base_type::size_type			size_type;
		typedef base_type::bool_type			bool_type;
		typedef basic_event						event_type;
	/// @}

	/// \name Members
	private:
		event_type								m_event;
	/// @}

	/// \name Constructors
	/// @{
	public:
		event_lock()
			: base_type()
			, m_event(e_false_v, e_true_v)			/* reset event automaticly */
		{
			EXTL_ASSERT(is_valid());
		}
		~event_lock()
		{
			// note: cannot unlock in the ~base()
			// because the destructor of m_event will be called before ~base()
			if (base_type::is_locked())
				base_type::unlock();
		}
	/// @}

	/// \name Implementions
	/// @{
	public:
		void do_lock()
		{
			EXTL_ASSERT(is_valid());

			// waits the event object 
			::WaitForSingleObject(event().handle(), INFINITE);
			
		}
		bool_type do_trylock()
		{
			EXTL_ASSERT(is_valid());

			// try waiting the event object for 100 milliseconds 
			return (WAIT_TIMEOUT != ::WaitForSingleObject(event().handle(), 100));
		}
		void do_unlock()
		{
			EXTL_ASSERT(is_valid());
			// sets the event object 
			event().set();
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		event_type&			event()				{ return m_event;	}
		event_type const&	event() const		{ return m_event;	}

		bool_type			is_valid() const	{ return event().is_valid();	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_EVENT_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
