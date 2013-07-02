/* ///////////////////////////////////////////////////////////////////////
 * File:		mutex_lock.h		
 *
 * Created:		08.03.21				
 * Updated:		09.01.12
 *
 * Brief:		the mutex_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WINDOWS_SYNCH_MUTEX_LOCK_H
#define EXTL_WINDOWS_SYNCH_MUTEX_LOCK_H

/*!\file mutex_lock.h
 * \brief mutex_lock class
 */
#ifndef __cplusplus
#	error mutex_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../synch/lock_base.h" 
#include "basic_mutex.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief mutex_lock class 
 *
 * \ingroup extl_group_synch
 */
class mutex_lock
	: public lock_base<mutex_lock>
{
	/// \name Types
	/// @{
	public:
		typedef lock_base<mutex_lock>			base_type;
		typedef mutex_lock						class_type;
		typedef base_type::size_type			size_type;
		typedef base_type::bool_type			bool_type;
		typedef basic_mutex						mutex_type;
	/// @}

	/// \name Members
	/// @{
	private:
		mutex_type								m_mutex; 
	/// @}

	/// \name Constructors
	/// @{
	public:
		mutex_lock()
			: base_type()
			, m_mutex(e_false_v)
		{
			EXTL_ASSERT(is_valid());
		}
		~mutex_lock()
		{
			// note: cannot unlock in the ~base()
			// because the destructor of m_mutex will be called before ~base()
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
			// waits the mutex object 
			::WaitForSingleObject(mutex().handle(), INFINITE);
			
		}
		bool_type do_trylock()
		{
			EXTL_ASSERT(is_valid());
			// try waiting the mutex object for 100 milliseconds 
			return (WAIT_TIMEOUT != ::WaitForSingleObject(mutex().handle(), 100));
		}
		void do_unlock()
		{
			EXTL_ASSERT(is_valid());
			// release the mutex object 
			mutex().release();
		}
	/// @}

	/// \name Attributes
	/// @{
	private:
		mutex_type&			mutex()				{ return m_mutex;	}
		mutex_type const&	mutex() const		{ return m_mutex;	}

		bool_type			is_valid() const	{ return mutex().is_valid();	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WINDOWS_SYNCH_MUTEX_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
