/* ///////////////////////////////////////////////////////////////////////
 * File:		highperformance_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.06
 *
 * Brief:		The highperformance_counter class - precision: us
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_HIGH_PERFORMANCE_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_HIGH_PERFORMANCE_COUNTER_H

/*!\file highperformance_counter.h
 * \brief highperformance_counter class - precision: us
 */
#ifndef __cplusplus
#	error high_performance_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../../type/traits/limit_traits.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief highperformance_counter class
 *
 * \ingroup extl_group_counter
 */
class highperformance_counter
{
	/// \name Constructors
	/// @{
	public :
		highperformance_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef highperformance_counter		class_type;
#ifdef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t					interval_type;	
		typedef e_uint64_t					size_type;		
#else
		typedef e_uint32_t					interval_type;	
		typedef e_uint32_t					size_type;		
#endif
	/// @}

	/// \name Operations
	/// @{
	public:
		inline void							start();
		inline void							stop();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		inline interval_type				count() const;		
		inline interval_type				s() const;	
		inline interval_type				ms() const;		
		inline interval_type				us() const;		

		inline size_type					frequency() const;		
	/// @}

	/// \name Members
	/// @{
	private:
		size_type							m_start;
		size_type							m_stop;
		size_type							m_frequency;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline highperformance_counter::highperformance_counter()
	: m_start(0), m_stop(0), m_frequency(frequency())
{
}
inline highperformance_counter::size_type highperformance_counter::frequency() const
{
	size_type frequency;
    BOOL ret = ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	EXTL_ASSERT((ret == TRUE) && (frequency != 0)); 
	EXTL_SUPPRESS_UNUSED(ret);
    return frequency;
}
inline void highperformance_counter::start()
{
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_start));
}
inline void highperformance_counter::stop()
{
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_stop));
}
inline highperformance_counter::interval_type highperformance_counter::count() const
{
	EXTL_ASSERT(m_stop >= m_start);
	return static_cast<interval_type>(m_stop - m_start);
}
inline highperformance_counter::interval_type highperformance_counter::s() const
{
	return count() / m_frequency;
}
inline highperformance_counter::interval_type highperformance_counter::ms() const
{
	interval_type result = 0;
	interval_type n = count();

#ifdef EXTL_64BIT_INT_SUPPORT
	if (n < (EXTL_LIMIT_TRAITS_UINT64_MAX / 1000))	// prevent overflow 
#else
	if (n < (EXTL_LIMIT_TRAITS_UINT32_MAX / 1000))	// prevent overflow 
#endif
	{
		//prevent truncation error 
		result = (n * interval_type(1000)) / m_frequency;
	}
	else
	{
		result = (n / m_frequency) * interval_type(1000);
	}
	return result;
}
inline highperformance_counter::interval_type highperformance_counter::us() const
{
	interval_type result = 0;
	interval_type n = count();
	
#ifdef EXTL_64BIT_INT_SUPPORT
	if(n < (EXTL_LIMIT_TRAITS_UINT64_MAX / 1000000))	// prevent overflow 
#else
	if(n < (EXTL_LIMIT_TRAITS_UINT64_MAX / 1000000))	// prevent overflow 
#endif
	{
		// prevent truncation error 
		result = (n * interval_type(1000000)) / m_frequency;
	}
	else
	{
		result = (n / m_frequency) * interval_type(1000000);
	}
	return result;
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_HIGH_PERFORMANCE_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
