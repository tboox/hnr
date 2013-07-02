/* ///////////////////////////////////////////////////////////////////////
 * File:		event_lock.h		
 *
 * Created:		08.03.21				
 * Updated:		08.05.05
 *
 * Brief: event_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_EVENT_LOCK_H
#define EXTL_WIN_SYNCH_EVENT_LOCK_H

/*!\file event_lock.h
 * \brief event_lock class
 */
#ifndef __cplusplus
#	error event_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../synch/lock_base.h" 
#include "event.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief event_lock class 
 * \ingroup extl_group_synch
 */
class event_lock
	: public lock_base< event_lock >
{
	public:
		typedef lock_base< event_lock >			base_type;
		typedef event_lock						class_type;
		typedef base_type::size_type			size_type;

	private:
		event									m_event_obj;

	public:
		event_lock()
		:	m_event_obj(e_false_v, e_true_v),			/* reset event automaticly */
			base_type()
		{
			EXTL_ASSERT(is_valid());
		}

		~event_lock()
		{
			if(base_type::is_locked())
			{
				base_type::unlock();
			}
		}

	public:
		void do_lock()
		{
			EXTL_ASSERT(is_valid());

			/* Waits the event object */
			::WaitForSingleObject(m_event_obj, INFINITE);
			
		}
		e_bool_t do_trylock()
		{
			EXTL_ASSERT(is_valid());

			/* Try waiting the event object for 100 milliseconds */
			return (WAIT_TIMEOUT != ::WaitForSingleObject(m_event_obj, 100));
		}
		void do_unlock()
		{
			EXTL_ASSERT(is_valid());
			/* Sets the event object */
			m_event_obj.set_event();
		}
	private:
		e_bool_t is_valid()
		{
			return ((m_event_obj != NULL) && (m_event_obj != INVALID_HANDLE_VALUE));
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_SYNCH_LOCK_TEST_ENABLE
#	include "unit_test/event_lock_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_EVENT_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
