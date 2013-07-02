/* ///////////////////////////////////////////////////////////////////////
 * File:		threadtimes_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: threadtimes_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_THREAD_TIMES_COUNTER_H
#define EXTL_PLATFORM_WIN_THREAD_TIMES_COUNTER_H

/*!\file threadtimes_counter.h
 * \brief threadtimes_counter class - precision: ms
 */
#ifndef __cplusplus
#	error threadtimes_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief threadtimes_counter class
 * \ingroup extl_group_counter
 */
class threadtimes_counter
{
	/// \name Constructors
	/// @{
	public :
		threadtimes_counter();
		~threadtimes_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef threadtimes_counter		class_type;
#ifdef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t				interval_type;		
		typedef e_uint64_t				size_type;			
#else
		typedef e_uint32_t				interval_type;		
		typedef e_uint32_t				size_type;			
#endif
	/// @}

	/// \name Operations
	/// @{
	public:
		inline void begin();
		inline void end();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		// Kernel + User 
		inline interval_type count() const;				
		inline interval_type seconds() const;			
		inline interval_type ms() const;				
		inline interval_type us() const;				

		// Kernel 
		inline interval_type kernel_count() const;	
		inline interval_type kernel_seconds() const;
		inline interval_type kernel_ms() const;		
		inline interval_type kernel_us() const;			

		// User 
		inline interval_type user_count() const;		
		inline interval_type user_seconds() const;		
		inline interval_type user_ms() const;			
		inline interval_type user_us() const;		
	/// @}

	private:
		inline HANDLE thread_handle() const;

	/// \name Members
	/// @{
	private:
		size_type m_kernel_begin;
		size_type m_kernel_end;

		size_type m_user_begin;
		size_type m_user_end;

		HANDLE m_ht;	//!< Thread Handle 
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline threadtimes_counter::threadtimes_counter()
:	m_kernel_begin(0), m_kernel_end(0), 
	m_user_begin(0), m_user_end(0),
	m_ht(thread_handle())
{
}
inline threadtimes_counter::~threadtimes_counter()
{
}
inline HANDLE threadtimes_counter::thread_handle() const
{
	HANDLE ht = ::GetCurrentThread();
	EXTL_ASSERT(ht != NULL);
	return ht;
}
inline void threadtimes_counter::begin()
{
	FILETIME	creation_time;
	FILETIME	exit_time;

	::GetThreadTimes(m_ht, &creation_time, &exit_time, \
		reinterpret_cast<LPFILETIME>(&m_kernel_begin), reinterpret_cast<LPFILETIME>(&m_user_begin));
}
inline void threadtimes_counter::end()
{
	FILETIME	creation_time;
	FILETIME	exit_time;

	::GetThreadTimes(m_ht, &creation_time, &exit_time, \
		reinterpret_cast<LPFILETIME>(&m_kernel_end), reinterpret_cast<LPFILETIME>(&m_user_end));
}
/* Kernel */
inline threadtimes_counter::interval_type threadtimes_counter::kernel_count() const
{
	EXTL_ASSERT(m_kernel_end >= m_kernel_begin);
	return static_cast<interval_type>(m_kernel_end - m_kernel_begin);
}
inline threadtimes_counter::interval_type threadtimes_counter::kernel_seconds() const
{
	return kernel_count() / interval_type(10000000);
}
inline threadtimes_counter::interval_type threadtimes_counter::kernel_ms() const
{
	return kernel_count() / interval_type(10000);
}
inline threadtimes_counter::interval_type threadtimes_counter::kernel_us() const
{
	return kernel_count() / interval_type(10);
}
/* User */
inline threadtimes_counter::interval_type threadtimes_counter::user_count() const
{
	EXTL_ASSERT(m_user_end >= m_user_begin);
	return static_cast<interval_type>(m_user_end - m_user_begin);
}
inline threadtimes_counter::interval_type threadtimes_counter::user_seconds() const
{
	return user_count() / interval_type(10000000);
}
inline threadtimes_counter::interval_type threadtimes_counter::user_ms() const
{
	return user_count() / interval_type(10000);
}
inline threadtimes_counter::interval_type threadtimes_counter::user_us() const
{
	return user_count() / interval_type(10);
}
/* Kernel + User */
inline threadtimes_counter::interval_type threadtimes_counter::count() const
{
	return kernel_count() + user_count();
}
inline threadtimes_counter::interval_type threadtimes_counter::seconds() const
{
	return count() / interval_type(10000000);
}
inline threadtimes_counter::interval_type threadtimes_counter::ms() const
{
	return count() / interval_type(10000);
}
inline threadtimes_counter::interval_type threadtimes_counter::us() const
{
	return count() / interval_type(10);
}

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_THREADTIMES_COUNTER_TEST_ENABLE
#	include "unit_test/threadtimes_counter_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_THREAD_TIMES_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
