/* ///////////////////////////////////////////////////////////////////////
 * File:		systemtime_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.06
 *
 * Brief: systemtime_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_SYSTEM_TIME_COUNTER_H
#define EXTL_PLATFORM_WIN_SYSTEM_TIME_COUNTER_H

/*!\file systemtime_counter.h
 * \brief systemtime_counter class - precision: ms
 */
#ifndef __cplusplus
#	error systemtime_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief systemtime_counter class
 * \ingroup extl_group_counter
 */
class systemtime_counter
{
	/// \name Constructors
	/// @{
	public :
		systemtime_counter();
		~systemtime_counter();
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
	/// @}

	/// \name Members
	/// @{
	private:
		size_type m_begin;
		size_type m_end;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline systemtime_counter::systemtime_counter()
:m_begin(0), m_end(0)
{
}

inline systemtime_counter::~systemtime_counter()
{
}
inline void systemtime_counter::begin()
{
	::GetSystemTimeAsFileTime(reinterpret_cast<LPFILETIME>(&m_begin));
}

inline void systemtime_counter::end()
{
	::GetSystemTimeAsFileTime(reinterpret_cast<LPFILETIME>(&m_end));
}
inline systemtime_counter::interval_type systemtime_counter::count() const
{
	EXTL_ASSERT(m_end >= m_begin);
	return static_cast<interval_type>(m_end - m_begin);
}
inline systemtime_counter::interval_type systemtime_counter::seconds() const
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
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_SYSTEMTIME_COUNTER_TEST_ENABLE
#	include "unit_test/systemtime_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_SYSTEM_TIME_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
