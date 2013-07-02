/* ///////////////////////////////////////////////////////////////////////
 * File:		tick_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.09
 *
 * Brief:		The tick_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_TICK_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_TICK_COUNTER_H

/*!\file tick_counter.h
 * \brief tick_counter class - precision: ms
 */
#ifndef __cplusplus
#	error tick_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief tick_counter class
 *
 * \ingroup extl_group_counter
 */
class tick_counter
{
	/// \name Constructors
	/// @{
	public :
		tick_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef tick_counter		class_type;
		typedef DWORD				size_type;
#ifdef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t			interval_type;	
#else
		typedef e_uint32_t			interval_type; 
#endif
	/// @}

	/// \name Members
	/// @{
	private:
		size_type					m_start;
		size_type					m_stop;
	/// @}

	/// \name Operations
	/// @{
	public:
		inline void					start();
		inline void					stop();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		inline interval_type		count() const;		
		inline interval_type		s() const;	
		inline interval_type		ms() const;		
		inline interval_type		us() const;		
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline tick_counter::tick_counter()
	: m_start(0), m_stop(0)
{
}
inline void tick_counter::start()
{
	m_start = ::GetTickCount();
}
inline void tick_counter::stop()
{
	m_stop = ::GetTickCount();
}
inline tick_counter::interval_type tick_counter::count() const
{
	EXTL_ASSERT(m_stop >= m_start);
	return static_cast<interval_type>(m_stop - m_start);
}
inline tick_counter::interval_type tick_counter::s() const
{
	return count() / interval_type(1000);
}
inline tick_counter::interval_type tick_counter::ms() const
{
	return count();
}
inline tick_counter::interval_type tick_counter::us() const
{
	return count() * interval_type(1000);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_TICK_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
