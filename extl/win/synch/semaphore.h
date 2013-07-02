/* ///////////////////////////////////////////////////////////////////////
 * File:		semaphore.h		
 *
 * Created:		08.03.23				
 * Updated:		08.05.05
 *
 * Brief: semaphore object class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_SYNCH_SEMAPHORE_H
#define EXTL_WIN_SYNCH_SEMAPHORE_H

/*!\file semaphore.h
 * \brief semaphore object class
 */
#ifndef __cplusplus
#	error semaphore.h need be supported by c++.
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

/*!\brief semaphore class 
 * \ingroup extl_group_synch
 */
class semaphore : private uncopyable<semaphore>
{
	/// \name Types
	/// @{
	public:
		typedef semaphore			class_type;
		typedef HANDLE				handle_type;
		typedef HANDLE				synch_object_type;
		typedef	LONG				size_type;
	/// @}

	private:
		/// The semaphore object
		synch_object_type					m_semaphore_obj;

	/// \name Constructors
	/// @{
	public:
		semaphore()
			: m_semaphore_obj(NULL)
		{}
		explicit_k semaphore(size_type nInitialCount, size_type nMaxCount,
							LPSECURITY_ATTRIBUTES psa = NULL)
		: m_semaphore_obj(create_semaphore_(psa, nInitialCount, nMaxCount, NULL))
		{
		}
		explicit_k semaphore(e_tchar_t const* szName, size_type nInitialCount, 
								size_type nMaxCount, LPSECURITY_ATTRIBUTES psa = NULL)
		: m_semaphore_obj(create_semaphore_(psa, nInitialCount, nMaxCount, szName))
		{
		}
	public:
		virtual ~semaphore() EXTL_THROW_0()
		{
			if(NULL != m_semaphore_obj)
			{
				::CloseHandle(m_semaphore_obj);
				m_semaphore_obj = NULL;
			}
		}
	/// @}

	public:
		/// Release the semaphore object 
		e_bool_t release(size_type n, size_type* lpPrevCount = NULL)
		{
			EXTL_ASSERT(NULL != m_semaphore_obj);

			if(!::ReleaseSemaphore(m_semaphore_obj, n, lpPrevCount))
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
			return m_semaphore_obj;
		}
		/// Returns object handle 
		handle_type get_handle() const
		{
			return m_semaphore_obj;
		}

		/// Create semaphore object
		void create(size_type nInitialCount, size_type nMaxCount,
							LPSECURITY_ATTRIBUTES psa = NULL)
		{
			m_semaphore_obj = create_semaphore_(psa, nInitialCount, nMaxCount, NULL);
		}
		/// Create semaphore object
		void create(e_tchar_t const* szName, size_type nInitialCount, 
								size_type nMaxCount, LPSECURITY_ATTRIBUTES psa = NULL)
		{
			m_semaphore_obj = create_semaphore_(psa, nInitialCount, nMaxCount, szName);
		}

	private:
		synch_object_type create_semaphore_(LPSECURITY_ATTRIBUTES psa, size_type nInitialCount, size_type nMaxCount, e_tchar_t const* pszName)
		{
			synch_object_type semaphore_obj = ::CreateSemaphore(psa, nInitialCount, nMaxCount, pszName);
			EXTL_ASSERT_THROW(semaphore_obj != NULL, win_synch_error("Failed to create kernel semaphore object"));
			return semaphore_obj;
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_SYNCH_SEMAPHORE_H */
/* //////////////////////////////////////////////////////////////////// */
