/* ///////////////////////////////////////////////////////////////////////
 * File:		semaphore_lock.h		
 *
 * Created:		08.03.21				
 * Updated:		08.05.05
 *
 * Brief: semaphore_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_SEMAPHORE_LOCK_H
#define EXTL_WIN_SYNCH_SEMAPHORE_LOCK_H

/*!\file semaphore_lock.h
 * \brief semaphore_lock class
 */
#ifndef __cplusplus
#	error semaphore_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../synch/lock_base.h" 
#include "semaphore.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief semaphore_lock class 
 * \ingroup extl_group_synch
 */
class semaphore_lock
	: public lock_base< semaphore_lock >
{
	public:
		typedef lock_base< semaphore_lock >			base_type;
		typedef semaphore_lock						class_type;
		typedef base_type::size_type				size_type;

	private:
		semaphore									m_semaphore_obj; 

	public:
		semaphore_lock()
		:	base_type(), m_semaphore_obj(1, 1)/* Only one semaphore */
			
		{
			EXTL_ASSERT(is_valid());
		}

		~semaphore_lock()
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
			/* Waits the semaphore object */
			::WaitForSingleObject(m_semaphore_obj, INFINITE);
			
		}
		e_bool_t do_trylock()
		{
			EXTL_ASSERT(is_valid());
			/* Try waiting the semaphore object for 100 milliseconds */
			return (WAIT_TIMEOUT != ::WaitForSingleObject(m_semaphore_obj, 100));
		}
		void do_unlock()
		{
			EXTL_ASSERT(is_valid());
			/* Release the semaphore object */
			m_semaphore_obj.release(1);
		}
	private:
		e_bool_t is_valid()
		{
			return ((m_semaphore_obj != NULL) && (m_semaphore_obj != INVALID_HANDLE_VALUE));
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_SYNCH_LOCK_TEST_ENABLE
#	include "unit_test/semaphore_lock_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_SEMAPHORE_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
