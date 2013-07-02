/* ///////////////////////////////////////////////////////////////////////
 * File:		critical_lock.h		
 *
 * Created:		08.03.20				
 * Updated:		09.01.20
 *
 * Brief:		critical_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WINDOWS_SYNCH_CRITICAL_SECTION_LOCK_H
#define EXTL_WINDOWS_SYNCH_CRITICAL_SECTION_LOCK_H

/*!\file critical_lock.h
 * \brief critical_lock class
 */
#ifndef __cplusplus
#	error critical_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../synch/lock_base.h" 
#include "basic_critical.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief critical_lock class 
 *
 * \ingroup extl_group_synch
 */
class critical_lock
	: public lock_base<critical_lock>
{
	/// \name Types
	/// @{
	public:
		typedef lock_base<critical_lock>			base_type;
		typedef critical_lock						class_type;
		typedef base_type::size_type				size_type;
		typedef base_type::bool_type				bool_type;
		typedef basic_critical						critical_type;
	/// @}

	/// \name Members
	/// @{
	private:
		critical_type								m_cs; 
	/// @}

	/// \name Constructors
	/// @{
	public:
		critical_lock()
			: base_type()
			, m_cs()
		{}
		~critical_lock()
		{
			// note: cannot unlock in the ~base()
			// because the destructor of m_cs will be called before ~base()
			if (base_type::is_locked())
				base_type::unlock();
		}
	/// @}

	/// \name Implemention
	/// @{
	public:
		void		do_lock()		{ m_cs.enter();				}
		bool_type	do_trylock()	{ return m_cs.try_enter();	}
		void		do_unlock()		{ m_cs.leave();				}
	/// @}

	/// \name Attributes
	/// @{
	public:
		critical_type&			critical()				{ return m_cs;	}
		critical_type const&	critical() const		{ return m_cs;	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WINDOWS_SYNCH_CRITICAL_SECTION_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
