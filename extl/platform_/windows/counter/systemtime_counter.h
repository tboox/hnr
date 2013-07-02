/* ///////////////////////////////////////////////////////////////////////
 * File:		systemtime_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.13
 *
 * Brief:		The systemtime_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_SYSTEM_TIME_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_SYSTEM_TIME_COUNTER_H

/*!\file systemtime_counter.h
 * \brief systemtime_counter class - precision: ms
 */
#ifndef __cplusplus
#	error systemtime_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief systemtime_counter class
 *
 * \ingroup extl_group_counter
 */
class systemtime_counter
{
	/// \name Constructors
	/// @{
	public :
		systemtime_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef systemtime_counter		class_type;

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
		inline interval_type			count() const;			
		inline interval_type			s() const;		
		inline interval_type			ms() const;			
		inline interval_type			us() const;	
	/// @}

	/// \name Members
	/// @{
	private:
		size_type						m_start;
		size_type						m_stop;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline systemtime_counter::systemtime_counter()
	: m_start(0), m_stop(0)
{
}

inline void systemtime_counter::start()
{
	::GetSystemTimeAsFileTime(reinterpret_cast<LPFILETIME>(&m_start));
}

inline void systemtime_counter::stop()
{
	::GetSystemTimeAsFileTime(reinterpret_cast<LPFILETIME>(&m_stop));
}
inline systemtime_counter::interval_type systemtime_counter::count() const
{
	EXTL_ASSERT(m_stop >= m_start);
	return static_cast<interval_type>(m_stop - m_start);
}
inline systemtime_counter::interval_type systemtime_counter::s() const
{
	return count() / interval_type(10000000);
}
inline systemtime_counter::interval_type systemtime_counter::ms() const
{
	return count() / interval_type(10000);
}
inline systemtime_counter::interval_type systemtime_counter::us() const
{
	return count() / interval_type(10);
}


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_SYSTEM_TIME_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
