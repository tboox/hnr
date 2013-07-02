/* ///////////////////////////////////////////////////////////////////////
 * File:		mutex.h		
 *
 * Created:		08.03.23				
 * Updated:		08.05.05
 *
 * Brief: mutex object class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_MUTEX_H
#define EXTL_WIN_SYNCH_MUTEX_H

/*!\file mutex.h
 * \brief mutex object class
 */
#ifndef __cplusplus
#	error mutex.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../utility/uncopyable.h"

#if defined(EXTL_EXCEPTION_SUPPORT) && \
		defined(EXTL_EXCEPTION_ENABLE)
#	include "../error/win_synch_error.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief mutex class 
 * \ingroup extl_group_synch
 */
class mutex : private uncopyable<mutex>
{
	/// \name Types
	/// @{
	public:
		typedef mutex				class_type;
		typedef HANDLE				handle_type;
		typedef HANDLE				synch_object_type;
	/// @}

	private:
		/// The mutex object
		synch_object_type			m_mutex_obj;

	/// \name Constructors
	/// @{
	public:
		mutex()
			: m_mutex_obj(NULL)
		{
		}
		explicit_k mutex(e_bool_t bInitialOwner,
							LPSECURITY_ATTRIBUTES psa = NULL)
		: m_mutex_obj(create_mutex_(psa, bInitialOwner, NULL))
		{
		}
		explicit_k mutex(e_tchar_t const* szName, e_bool_t bInitialOwner, LPSECURITY_ATTRIBUTES psa = NULL)
		: m_mutex_obj(create_mutex_(psa, bInitialOwner, szName))
		{
		}

	public:
		virtual ~mutex() EXTL_THROW_0()
		{
			if(NULL != m_mutex_obj)
			{
				::CloseHandle(m_mutex_obj);
				m_mutex_obj = NULL;
			}
		}
	/// @}

	public:
		/// Release the mutex object 
		e_bool_t release()
		{
			EXTL_ASSERT(NULL != m_mutex_obj);

			if(!::ReleaseMutex(m_mutex_obj))
			{
				EXTL_THROW_E(win_synch_error("ReleaseMutex operation failed"));
				return e_false_v;
			}
			else return e_true_v;
		}
	public:
		/// Returns object handle 
		operator handle_type() const
		{
			return m_mutex_obj;
		}
		/// Returns object handle 
		handle_type get_handle() const
		{
			return m_mutex_obj;
		}

		/// Create mutex object
		void create(e_bool_t bInitialOwner,
							LPSECURITY_ATTRIBUTES psa = NULL)
		{
			m_mutex_obj = create_mutex_(psa, bInitialOwner, NULL);
		}
		/// Create mutex object
		void create(e_tchar_t const* szName, e_bool_t bInitialOwner, LPSECURITY_ATTRIBUTES psa = NULL)
		{
			m_mutex_obj = create_mutex_(psa, bInitialOwner, szName);
		}

	private:
		synch_object_type create_mutex_(LPSECURITY_ATTRIBUTES psa, e_bool_t bInitialOwner, e_tchar_t const* pszName)
		{
			synch_object_type mutex_obj = ::CreateMutex(psa, bInitialOwner, pszName);
			EXTL_ASSERT_THROW(mutex_obj != NULL, win_synch_error("Failed to create kernel mutex object"));
			return mutex_obj;
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_MUTEX_H */
/* //////////////////////////////////////////////////////////////////// */
