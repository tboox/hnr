/* ///////////////////////////////////////////////////////////////////////
 * File:		clock_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: clock_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CLOCK_COUNTER_H
#define EXTL_CLOCK_COUNTER_H

/*!\file clock_counter.h
 * \brief clock_counter class - precision: ms
 */
#ifndef __cplusplus
#	error clock_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include <time.h>

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief clock_counter class
 * 
 * \ingroup extl_group_counter
 */
class clock_counter
{
	/// \name Constructors
	/// @{
	public :
		clock_counter();
		~clock_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef clock_counter		class_type;
		typedef e_uint32_t			interval_type;	
		typedef clock_t				size_type;	
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
inline clock_counter::clock_counter()
:m_begin(0), m_end(0)
{
}

inline clock_counter::~clock_counter()
{
}
inline void clock_counter::begin()
{
	m_begin = clock();
}

inline void clock_counter::end()
{
	m_end = clock();
}
inline clock_counter::interval_type clock_counter::count() const
{
	EXTL_ASSERT(m_end >= m_begin);
	return static_cast<interval_type>(m_end - m_begin);
}
inline clock_counter::interval_type clock_counter::seconds() const
{
	return count() / interval_type(1000);
}
inline clock_counter::interval_type clock_counter::ms() const
{
	return count();
}
inline clock_counter::interval_type clock_counter::us() const
{
	return count() * interval_type(1000);
}

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_CLOCK_COUNTER_TEST_ENABLE
#	include "unit_test/clock_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CLOCK_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
