/* ///////////////////////////////////////////////////////////////////////
 * File:		highperformance_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.06
 *
 * Brief: highperformance_counter class - precision: us
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_HIGH_PERFORMANCE_COUNTER_H
#define EXTL_PLATFORM_WIN_HIGH_PERFORMANCE_COUNTER_H

/*!\file highperformance_counter.h
 * \brief highperformance_counter class - precision: us
 */
#ifndef __cplusplus
#	error high_performance_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../type/traits/limit_traits.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief highperformance_counter class
 * \ingroup extl_group_counter
 */
class highperformance_counter
{
	/// \name Constructors
	/// @{
	public :
		highperformance_counter();
		~highperformance_counter();
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
		inline void begin();
		inline void end();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		inline interval_type count() const;		
		inline interval_type seconds() const;	
		inline interval_type ms() const;		
		inline interval_type us() const;		

		inline size_type frequency() const;		
	/// @}

	/// \name Members
	/// @{
	private:
		size_type m_begin;
		size_type m_end;
		size_type m_frequency;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline highperformance_counter::highperformance_counter()
:m_begin(0), m_end(0), m_frequency(frequency())
{
}

inline highperformance_counter::~highperformance_counter()
{
}
inline highperformance_counter::size_type highperformance_counter::frequency() const
{
	size_type frequency;
    BOOL bRet = ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	EXTL_ASSERT((bRet == TRUE) && (frequency != 0)); 
    return frequency;
}
inline void highperformance_counter::begin()
{
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_begin));
}
inline void highperformance_counter::end()
{
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_end));
}
inline highperformance_counter::interval_type highperformance_counter::count() const
{
	EXTL_ASSERT(m_end >= m_begin);
	return static_cast<interval_type>(m_end - m_begin);
}
inline highperformance_counter::interval_type highperformance_counter::seconds() const
{
	return count() / m_frequency;
}
inline highperformance_counter::interval_type highperformance_counter::ms() const
{
	interval_type result = 0;
	interval_type count = count();

#ifdef EXTL_64BIT_INT_SUPPORT
	if(count < (EXTL_LIMIT_TRAITS_UINT64_MAX / 1000))	/* Prevent overflow */
#else
	if(count < (EXTL_LIMIT_TRAITS_UINT32_MAX / 1000))	/* Prevent overflow */
#endif
	{
		/* Prevent truncation error */
		result = (count * interval_type(1000)) / m_frequency;
	}
	else
	{
		result = (count / m_frequency) * interval_type(1000);
	}
	return result;
}
inline highperformance_counter::interval_type highperformance_counter::us() const
{
	interval_type result = 0;
	interval_type count = count();
	
#ifdef EXTL_64BIT_INT_SUPPORT
	if(count < (EXTL_LIMIT_TRAITS_UINT64_MAX / 1000000))	/* Prevent overflow */
#else
	if(count < (EXTL_LIMIT_TRAITS_UINT64_MAX / 1000000))	/* Prevent overflow */
#endif
	{
		/* Prevent truncation error */
		result = (count * interval_type(1000000)) / m_frequency;
	}
	else
	{
		result = (count / m_frequency) * interval_type(1000000);
	}
	return result;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_HIGHPERFORMANCE_COUNTER_TEST_ENABLE
#	include "unit_test/highperformance_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_HIGH_PERFORMANCE_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
