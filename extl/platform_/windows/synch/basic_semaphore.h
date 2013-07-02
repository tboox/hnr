/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_semaphore.h		
 *
 * Created:		08.03.23				
 * Updated:		08.05.05
 *
 * Brief:		The Semaphore Object
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_SEMAPHORE_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_SEMAPHORE_H

/*!\file basic_semaphore.h
 * \brief basic_semaphore object class
 */
#ifndef __cplusplus
#	error basic_semaphore.h need be supported by c++.
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

/*!\brief basic_semaphore class 
 *
 * \ingroup extl_group_synch
 */
class basic_semaphore 
	: private uncopyable<basic_semaphore>
{
	/// \name Types
	/// @{
	public:
		typedef basic_semaphore				class_type;
		typedef HANDLE						handle_type;
		typedef	LONG						size_type;
		typedef e_bool_t					bool_type;
		typedef LPSECURITY_ATTRIBUTES		psa_type;
		typedef e_tchar_t					char_type;
	/// @}

	/// \name Members
	/// @{
	private:
		handle_type							m_hs;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_semaphore()
			: m_hs(NULL)
		{}
		explicit_k basic_semaphore(size_type initial_n, size_type max_n, psa_type psa = NULL)
			: m_hs(NULL)
		{
			create(initial_n, max_n, psa);
		}
		explicit_k basic_semaphore(char_type const* name, size_type initial_n, size_type max_n, psa_type psa = NULL)
			: m_hs(NULL)
		{
			create(name, initial_n, max_n, psa);
		}
		~basic_semaphore() EXTL_THROW_0()
		{
			if(NULL != handle())
			{
				::CloseHandle(handle());
				m_hs = NULL;
			}
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// create basic_semaphore object - static
		static handle_type create_semaphore(char_type const* name, size_type initial_n, size_type max_n, psa_type psa = NULL)
		{
			handle_type hs = ::CreateSemaphore(psa, initial_n, max_n, name);
			EXTL_ASSERT_THROW(NULL != hs, windows_synch_error("failed to create kernel basic_semaphore object"));
			return hs;
		}
		/// create basic_semaphore object
		bool_type create(size_type initial_n, size_type max_n, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the basic_semaphore object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the basic_semaphore object has been created");

			if (NULL == handle())
			{
				m_hs = create_semaphore(NULL, initial_n, max_n, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// create basic_semaphore object
		bool_type create(char_type const* name, size_type initial_n, size_type max_n, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the basic_semaphore object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the basic_semaphore object has been created");

			if (NULL == handle())
			{
				m_hs = create_semaphore(name, initial_n, max_n, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// release the basic_semaphore object 
		bool_type release(size_type n, size_type* pprev_n = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the basic_semaphore object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the basic_semaphore object hasn't been created"));

			if(NULL == handle() || !::ReleaseSemaphore(handle(), n, pprev_n))
			{
				EXTL_THROW_E(windows_synch_error("failed to release basic_semaphore object"));
				return e_false_v;
			}
			else return e_true_v;
		}
	/// @}
		
	/// \name Accessors
	/// @{
	public:
		handle_type			handle() const					{ return m_hs;	}
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
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_BASIC_SEMAPHORE_H */
/* //////////////////////////////////////////////////////////////////// */
