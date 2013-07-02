/* ///////////////////////////////////////////////////////////////////////
 * File:		multimedia_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.13
 *
 * Brief:		The multimedia_counter class - precision: ms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_MULTIMEDIA_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_MULTIMEDIA_COUNTER_H

/*!\file multimedia_counter.h
 * \brief multimedia_counter class - precision: ms
 */
#ifndef __cplusplus
#	error multimedia_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include <mmsystem.h>

#if !defined(EXTL_COMPILER_IS_GCC) && \
		!defined(EXTL_COMPILER_IS_BORLAND)
#	pragma comment(lib, "WinMM.lib")
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief multimedia_counter class
 *
 * \ingroup extl_group_counter
 */
class multimedia_counter
{
	/// \name Constructors
	/// @{
	public :
		multimedia_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef multimedia_counter		class_type;
#ifdef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t				interval_type;	
#else
		typedef e_uint32_t				interval_type;	
#endif
		typedef DWORD					size_type;	
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
inline multimedia_counter::multimedia_counter()
	: m_start(0), m_stop(0)
{
}
inline void multimedia_counter::start()
{
	m_start = ::timeGetTime();
}

inline void multimedia_counter::stop()
{
	m_stop = ::timeGetTime();
}
inline multimedia_counter::interval_type multimedia_counter::count() const
{
	return static_cast<interval_type>(m_stop - m_start);
}
inline multimedia_counter::interval_type multimedia_counter::s() const
{
	return count() / interval_type(1000);
}
inline multimedia_counter::interval_type multimedia_counter::ms() const
{
	return count();
}
inline multimedia_counter::interval_type multimedia_counter::us() const
{
	return count() * interval_type(1000);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_MULTIMEDIA_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
