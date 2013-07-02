/* ///////////////////////////////////////////////////////////////////////
 * File:		semaphore_lock.h		
 *
 * Created:		08.03.21				
 * Updated:		09.01.12
 *
 * Brief:		the semaphore_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WINDOWS_SYNCH_SEMAPHORE_LOCK_H
#define EXTL_WINDOWS_SYNCH_SEMAPHORE_LOCK_H

/*!\file semaphore_lock.h
 * \brief semaphore_lock class
 */
#ifndef __cplusplus
#	error semaphore_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../synch/lock_base.h" 
#include "basic_semaphore.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief semaphore_lock class 
 * \ingroup extl_group_synch
 */
class semaphore_lock
	: public lock_base<semaphore_lock>
{
	/// \name Types
	/// @{
	public:
		typedef lock_base<semaphore_lock>			base_type;
		typedef semaphore_lock						class_type;
		typedef base_type::size_type				size_type;
		typedef base_type::bool_type				bool_type;
		typedef basic_semaphore						semaphore_type;
	/// @}

	/// \name Members
	/// @{
	private:
		semaphore_type								m_semaphore; 
	/// @}

	/// \name Constructors
	/// @{
	public:
		semaphore_lock()
			: base_type()
			, m_semaphore(1, 1)	// only one semaphore 
		{
			EXTL_ASSERT(is_valid());
		}
		~semaphore_lock()
		{
			// note: cannot unlock in the ~base()
			// because the destructor of m_semaphore will be called before ~base()
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
			// waits the semaphore object 
			::WaitForSingleObject(semaphore().handle(), INFINITE);
			
		}
		bool_type do_trylock()
		{
			EXTL_ASSERT(is_valid());
			// try waiting the semaphore object for 100 milliseconds 
			return (WAIT_TIMEOUT != ::WaitForSingleObject(semaphore().handle(), 100));
		}
		void do_unlock()
		{
			EXTL_ASSERT(is_valid());
			//release the semaphore object 
			semaphore().release(1);
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		semaphore_type&			semaphore()				{ return m_semaphore;	}
		semaphore_type const&	semaphore() const		{ return m_semaphore;	}

		bool_type				is_valid() const		{ return semaphore().is_valid();	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WINDOWS_SYNCH_SEMAPHORE_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
