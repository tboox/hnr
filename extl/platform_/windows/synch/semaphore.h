/* ///////////////////////////////////////////////////////////////////////
 * File:		semaphore.h		
 *
 * Created:		08.03.23				
 * Updated:		08.05.05
 *
 * Brief:		The Semaphore Object
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYNCH_SEMAPHORE_H
#define EXTL_PLATFORM_WINDOWS_SYNCH_SEMAPHORE_H

/*!\file semaphore.h
 * \brief semaphore object class
 */
#ifndef __cplusplus
#	error semaphore.h need be supported by c++.
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

/*!\brief semaphore class 
 *
 * \ingroup extl_group_synch
 */
class semaphore 
	: private uncopyable<semaphore>
{
	/// \name Types
	/// @{
	public:
		typedef semaphore					class_type;
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
		semaphore()
			: m_hs(NULL)
		{}
		explicit_k semaphore(size_type initial_n, size_type max_n, psa_type psa = NULL)
			: m_hs(NULL)
		{
			create(initial_n, max_n, psa);
		}
		explicit_k semaphore(char_type const* name, size_type initial_n, size_type max_n, psa_type psa = NULL)
			: m_hs(NULL)
		{
			create(name, initial_n, max_n, psa);
		}
		virtual ~semaphore() EXTL_THROW_0()
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
		/// create semaphore object - static
		static handle_type create_semaphore(char_type const* name, size_type initial_n, size_type max_n, psa_type psa = NULL)
		{
			handle_type hs = ::CreateSemaphore(psa, initial_n, max_n, name);
			EXTL_ASSERT_THROW(hs != NULL, windows_synch_error("Failed to create kernel semaphore object"));
			return hs;
		}
		/// create semaphore object
		void create(size_type initial_n, size_type max_n, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the semaphore object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the semaphore object has been created");

			if (NULL == handle())
			{
				m_hs = create_semaphore(NULL, initial_n, max_n, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// create semaphore object
		void create(char_type const* name, size_type initial_n, size_type max_n, psa_type psa = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL == handle(), "the semaphore object has been created");
			EXTL_ASSERT_THROW(NULL == handle(), "the semaphore object has been created");

			if (NULL == handle())
			{
				m_hs = create_semaphore(name, initial_n, max_n, psa);
				return (NULL != handle());
			}
			return e_false_v;
		}
		/// release the semaphore object 
		bool_type release(size_type n, size_type* pprev_n = NULL)
		{
			EXTL_MESSAGE_ASSERT(NULL != handle(), "the semaphore object hasn't been created");
			EXTL_ASSERT_THROW(NULL != handle(), windows_synch_error("the semaphore object hasn't been created"));

			if(NULL == handle() || !::ReleaseSemaphore(handle(), n, pprev_n))
			{
				EXTL_THROW_E(windows_synch_error("failed to release semaphore object"));
				return e_false_v;
			}
			else return e_true_v;
		}
	/// @}
		
	/// \name Accessors
	/// @{
	public:
		/// gets object handle
		operator			handle_type() const				{ return m_hs;	}
		/// gets object handle
		handle_type			handle() const					{ return m_hs;	}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYNCH_SEMAPHORE_H */
/* //////////////////////////////////////////////////////////////////// */
