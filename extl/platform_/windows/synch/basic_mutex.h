/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_mutex.h		
 *
 * Created:		08.03.23				
 * Updated:		08.11.26
 *
 * Brief:		The Mutex Object
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_MUTEX_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_MUTEX_H

/*!\file basic_mutex.h
 * \brief The Mutex Object
 */
#ifndef __cplusplus
#	error basic_mutex.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../utility/uncopyable.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief basic_mutex class 
 *
 * \ingroup extl_group_synch
 */
class basic_mutex 
	: private uncopyable<basic_mutex>
{
	/// \name Types
	/// @{
	public:
		typedef basic_mutex					class_type;
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
		basic_mutex()
			: m_hm(NULL)
		{}
		explicit_k basic_mutex(bool_type is_owner, psa_type psa = NULL)
			: m_hm(NULL)
		{
			create(NULL, is_owner, psa);
		}
		explicit_k basic_mutex(char_type const* name, bool_type is_owner, psa_type psa = NULL)
			: m_hm(NULL)
		{
			create(name, is_owner, psa);
		}
		~basic_mutex() EXTL_THROW_0()
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
		/// create basic_mutex object - static
		static handle_type create_mutex(char_type const* name, bool_type is_owner, psa_type psa = NULL)
		{
			handle_type hm = ::CreateMutex(psa, is_owner, name);
			EXTL_ASSERT_THROW(hm != NULL, windows_synch_error("failed to create kernel basic_mutex object"));
			return hm;
		}
		/// create basic_mutex object
		bool_type create(bool_type is_owner, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the basic_mutex object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the basic_mutex object has been created");

			if (NULL == handle())
			{
				m_hm = create_mutex(NULL, is_owner, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// create basic_mutex object
		bool_type create(char_type const* name, bool_type is_owner, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the basic_mutex object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the basic_mutex object has been created");

			if (NULL == handle())
			{
				m_hm = create_mutex(name, is_owner, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// release the basic_mutex object 
		bool_type release()
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the basic_mutex object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the basic_mutex object hasn't been created"));

			if(NULL == handle() || !::ReleaseMutex(handle()))
			{
				EXTL_THROW_E(windows_synch_error("failed to release basic_mutex object"));
				return e_false_v;
			}
			else return e_true_v;
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		handle_type			handle() const					{ return m_hm;	}
		bool_type			is_valid() const
		{
			return ((handle() != NULL) && (handle() != INVALID_HANDLE_VALUE));
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_MUTEX_H */
/* //////////////////////////////////////////////////////////////////// */
