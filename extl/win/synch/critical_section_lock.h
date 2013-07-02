/* ///////////////////////////////////////////////////////////////////////
 * File:		critical_section_lock.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.05
 *
 * Brief: critical_section_lock class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_CRITICAL_SECTION_LOCK_H
#define EXTL_WIN_SYNCH_CRITICAL_SECTION_LOCK_H

/*!\file critical_section_lock.h
 * \brief critical_section_lock class
 */
#ifndef __cplusplus
#	error critical_section_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../synch/lock_base.h" 
#include "critical_section.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief critical_section_lock class 
 * \ingroup extl_group_synch
 */
class critical_section_lock
	: public lock_base< critical_section_lock >
{
	public:
		typedef lock_base< critical_section_lock >	base_type;
		typedef critical_section_lock				class_type;
		typedef base_type::size_type				size_type;

	private:
		critical_section							m_cs_obj; 

	public:
		critical_section_lock()
		{
		}

		~critical_section_lock()
		{
			if(base_type::is_locked())
			{
				base_type::unlock();
			}
		}

	public:
		void do_lock()
		{
			m_cs_obj.enter();
		}
		e_bool_t do_trylock()
		{
			return m_cs_obj.try_enter();
		}
		void do_unlock()
		{
			m_cs_obj.leave();
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_SYNCH_LOCK_TEST_ENABLE
#	include "unit_test/critical_section_lock_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_CRITICAL_SECTION_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
