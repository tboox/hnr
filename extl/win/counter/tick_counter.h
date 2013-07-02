/* ///////////////////////////////////////////////////////////////////////
 * File:		tick_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: tick_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_TICK_COUNTER_H
#define EXTL_PLATFORM_WIN_TICK_COUNTER_H

/*!\file tick_counter.h
 * \brief tick_counter class - precision: ms
 */
#ifndef __cplusplus
#	error tick_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief tick_counter class
 * \ingroup extl_group_counter
 */
class tick_counter
{
	/// \name Constructors
	/// @{
	public :
		tick_counter();
		~tick_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef tick_counter		class_type;

#ifdef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t			interval_type;	
#else
		typedef e_uint32_t			interval_type; 
#endif
		typedef DWORD				size_type;	
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
inline tick_counter::tick_counter()
:m_begin(0), m_end(0)
{
}

inline tick_counter::~tick_counter()
{
}
inline void tick_counter::begin()
{
	m_begin = ::GetTickCount();
}

inline void tick_counter::end()
{
	m_end = ::GetTickCount();
}
inline tick_counter::interval_type tick_counter::count() const
{
	EXTL_ASSERT(m_end >= m_begin);
	return static_cast<interval_type>(m_end - m_begin);
}
inline tick_counter::interval_type tick_counter::seconds() const
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
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_TICK_COUNTER_TEST_ENABLE
#	include "unit_test/tick_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_TICK_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
