/* ///////////////////////////////////////////////////////////////////////
 * File:		mutex_lock.h		
 *
 * Created:		08.03.21				
 * Updated:		08.05.05
 *
 * Brief: mutex_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_MUTEX_LOCK_H
#define EXTL_WIN_SYNCH_MUTEX_LOCK_H

/*!\file mutex_lock.h
 * \brief mutex_lock class
 */
#ifndef __cplusplus
#	error mutex_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../synch/lock_base.h" 
#include "mutex.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief mutex_lock class 
 * \ingroup extl_group_synch
 */
class mutex_lock
	: public lock_base< mutex_lock >
{
	public:
		typedef lock_base< mutex_lock >			base_type;
		typedef mutex_lock						class_type;
		typedef base_type::size_type			size_type;

	private:
		mutex									m_mutex_obj; 

	public:
		mutex_lock()
		:	base_type(), m_mutex_obj(e_false_v)
			
		{
			EXTL_ASSERT(is_valid());
		}

		~mutex_lock()
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

			/* Waits the mutex object */
			::WaitForSingleObject(m_mutex_obj, INFINITE);
			
		}
		e_bool_t do_trylock()
		{
			EXTL_ASSERT(is_valid());
			/* Try waiting the mutex object for 100 milliseconds */
			return (WAIT_TIMEOUT != ::WaitForSingleObject(m_mutex_obj, 100));
		}
		void do_unlock()
		{
			EXTL_ASSERT(is_valid());
			/* Release the mutex object */
			m_mutex_obj.release();
		}
	private:
		e_bool_t is_valid()
		{
			return ((m_mutex_obj != NULL) && (m_mutex_obj != INVALID_HANDLE_VALUE));
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_SYNCH_LOCK_TEST_ENABLE
#	include "unit_test/mutex_lock_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_MUTEX_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
