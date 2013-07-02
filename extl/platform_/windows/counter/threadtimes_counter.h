/* ///////////////////////////////////////////////////////////////////////
 * File:		threadtimes_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.13
 *
 * Brief:		The threadtimes_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_THREAD_TIMES_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_THREAD_TIMES_COUNTER_H

/*!\file threadtimes_counter.h
 * \brief threadtimes_counter class - precision: ms
 */
#ifndef __cplusplus
#	error threadtimes_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief threadtimes_counter class
 *
 * \ingroup extl_group_counter
 */
class threadtimes_counter
{
	/// \name Constructors
	/// @{
	public :
		threadtimes_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef threadtimes_counter		class_type;
		typedef HANDLE					handle_type;
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
		inline void						start();
		inline void						stop();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		// Kernel + User 
		inline interval_type	count() const;				
		inline interval_type	s() const;			
		inline interval_type	ms() const;				
		inline interval_type	us() const;				

		// Kernel 
		inline interval_type	kernel_count() const;	
		inline interval_type	kernel_s() const;
		inline interval_type	kernel_ms() const;		
		inline interval_type	kernel_us() const;			

		// User 
		inline interval_type	user_count() const;		
		inline interval_type	user_s() const;		
		inline interval_type	user_ms() const;			
		inline interval_type	user_us() const;		
	/// @}

	private:
		inline handle_type		thread_handle() const;

	/// \name Members
	/// @{
	private:
		size_type				m_kernel_start;
		size_type				m_kernel_stop;

		size_type				m_user_start;
		size_type				m_user_stop;

		handle_type				m_ht;	//!< Thread Handle 
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline threadtimes_counter::threadtimes_counter()
	: m_kernel_start(0)
	, m_kernel_stop(0) 
	, m_user_start(0)
	, m_user_stop(0)
	, m_ht(thread_handle())
{
}
inline threadtimes_counter::
handle_type threadtimes_counter::thread_handle() const
{
	handle_type ht = ::GetCurrentThread();
	EXTL_ASSERT(ht != NULL);
	return ht;
}
inline void threadtimes_counter::start()
{
	FILETIME	creation_time;
	FILETIME	exit_time;

	::GetThreadTimes(m_ht, &creation_time, &exit_time, \
		reinterpret_cast<LPFILETIME>(&m_kernel_start), reinterpret_cast<LPFILETIME>(&m_user_start));
}
inline void threadtimes_counter::stop()
{
	FILETIME	creation_time;
	FILETIME	exit_time;

	::GetThreadTimes(m_ht, &creation_time, &exit_time, \
		reinterpret_cast<LPFILETIME>(&m_kernel_stop), reinterpret_cast<LPFILETIME>(&m_user_stop));
}
/* Kernel */
inline threadtimes_counter::interval_type threadtimes_counter::kernel_count() const
{
	EXTL_ASSERT(m_kernel_stop >= m_kernel_start);
	return static_cast<interval_type>(m_kernel_stop - m_kernel_start);
}
inline threadtimes_counter::interval_type threadtimes_counter::kernel_s() const
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
	EXTL_ASSERT(m_user_stop >= m_user_start);
	return static_cast<interval_type>(m_user_stop - m_user_start);
}
inline threadtimes_counter::interval_type threadtimes_counter::user_s() const
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
inline threadtimes_counter::interval_type threadtimes_counter::s() const
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
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_THREAD_TIMES_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
