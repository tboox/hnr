/* ///////////////////////////////////////////////////////////////////////
 * File:		rdtsc_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.13
 *
 * Brief:		The rdtsc_counter class - precision: cpu clock count
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WINDOWS_RDTSC_COUNTER_H
#define EXTL_PLATFORM_WINDOWS_RDTSC_COUNTER_H

/*!\file rdtsc_counter.h
 * \brief rdtsc_counter class - precision: cpu clock count
 */
#ifndef __cplusplus
#	error rdtsc_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifndef EXTL_WINDOWS_COUNTER_RDTSC_COUNTER_SUPPORT
#	error rdtsc_counter.h is not supported by current compiler.
#endif

// 'rdtsc' : no return value 
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER ==1200)
#	pragma warning(disable:4035)
// missing return statement at stop of non-void function "rdtsc" 
#elif defined(EXTL_COMPILER_IS_INTEL)
#	pragma warning(disable:1011)
// Function should return a value in function rdtsc_counter::rdtsc() const
#elif defined(EXTL_COMPILER_IS_BORLAND)
#	pragma warn -8070
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE

/*!\brief rdtsc_counter class
 *
 * \ingroup extl_group_counter
 */
class rdtsc_counter
{
	/// \name Constructors
	/// @{
	public :
		rdtsc_counter();
	/// @}
	
	/// \name Types
	/// @{
	private:
		typedef rdtsc_counter		class_type;

#ifndef EXTL_64BIT_INT_SUPPORT
		typedef e_uint64_t			interval_type;	
		typedef e_uint64_t			size_type;		
#else
		typedef e_uint32_t			interval_type;	
		typedef e_uint32_t			size_type;		
#endif
	/// @}

	/// \name Operations
	/// @{
	public:
		inline void start();
		inline void stop();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		inline interval_type		count() const;	

	private:
	#ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
		inline size_type			rdtsc() const;
	#else
		size_type					rdtsc() const;
	#endif
	/// @}

	/// \name Members
	/// @{
	private:
		size_type m_start;
		size_type m_stop;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Class implementation
 */
inline rdtsc_counter::rdtsc_counter()
	: m_start(0), m_stop(0)
{
}

#ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
inline rdtsc_counter::size_type rdtsc_counter::rdtsc() const
#else
rdtsc_counter::size_type rdtsc_counter::rdtsc() const
#endif
{
#ifdef EXTL_INLINE_ASM_SUPPORT
	__asm CPUID
	/* __asm _emit 0x0F */
	/* __asm _emit 0xA2 */
	__asm RDTSC
	/* __asm _emit 0x0F */
	/* __asm _emit 0x31 */
#endif
}

inline void rdtsc_counter::start()
{
	m_start = rdtsc();
}
inline void rdtsc_counter::stop()
{
	m_stop = rdtsc();
}
inline rdtsc_counter::interval_type rdtsc_counter::count() const
{
	EXTL_ASSERT(m_stop >= m_start);
	return static_cast<interval_type>(m_stop - m_start);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WINDOWS_RDTSC_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
