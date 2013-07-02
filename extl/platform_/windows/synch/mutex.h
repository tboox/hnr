/* ///////////////////////////////////////////////////////////////////////
 * File:		mutex.h		
 *
 * Created:		08.03.23				
 * Updated:		08.11.26
 *
 * Brief:		The Mutex Object
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_MUTEX_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_MUTEX_H

/*!\file mutex.h
 * \brief The Mutex Object
 */
#ifndef __cplusplus
#	error mutex.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../utility/uncopyable.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief mutex class 
 *
 * \ingroup extl_group_synch
 */
class mutex 
	: private uncopyable<mutex>
{
	/// \name Types
	/// @{
	public:
		typedef mutex						class_type;
		typedef HANDLE						handle_type;
		typedef e_bool_t					bool_type;
		typedef LPSECURITY_ATTRIBUTES		psa_type;
		typedef e_tchar_t					char_type;
	/// @}

	/// \name Members
	/// @{
	private:
		handle_type							m_hm;
	/// @}

	/// \name Constructors
	/// @{
	public:
		mutex()
			: m_hm(NULL)
		{}
		explicit_k mutex(bool_type is_owner, psa_type psa = NULL)
			: m_hm(NULL)
		{
			create(NULL, is_owner, psa);
		}
		explicit_k mutex(char_type const* name, bool_type is_owner, psa_type psa = NULL)
			: m_hm(NULL)
		{
			create(name, is_owner, psa);
		}
		virtual ~mutex() EXTL_THROW_0()
		{
			if(NULL != handle())
			{
				::CloseHandle(handle());
				m_hm = NULL;
			}
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// create mutex object - static
		static handle_type create_mutex(char_type const* name, bool_type is_owner, psa_type psa = NULL)
		{
			handle_type hm = ::CreateMutex(psa, is_owner, name);
			EXTL_ASSERT_THROW(hm != NULL, windows_synch_error("failed to create kernel mutex object"));
			return hm;
		}
		/// create mutex object
		bool_type create(bool_type is_owner, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the mutex object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the mutex object has been created");

			if (NULL == handle())
			{
				m_hm = create_mutex(NULL, is_owner, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// create mutex object
		bool_type create(char_type const* name, bool_type is_owner, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the mutex object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the mutex object has been created");

			if (NULL == handle())
			{
				m_hm = create_mutex(name, is_owner, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// release the mutex object 
		bool_type release()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the mutex object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the mutex object hasn't been created"));

			if(NULL == handle() || !::ReleaseMutex(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to release mutex object"));
				return e_false_v;
			}
			else return e_true_v;
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// gets object handle
		operator			handle_type() const				{ return m_hm;	}
		/// gets object handle
		handle_type			handle() const					{ return m_hm;	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_MUTEX_H */
/* //////////////////////////////////////////////////////////////////// */
