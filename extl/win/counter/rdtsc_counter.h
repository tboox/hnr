/* ///////////////////////////////////////////////////////////////////////
 * File:		rdtsc_counter.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.06
 *
 * Brief: rdtsc_counter class - precision: cpu clock count
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_RDTSC_COUNTER_H
#define EXTL_PLATFORM_WIN_RDTSC_COUNTER_H

/*!\file rdtsc_counter.h
 * \brief rdtsc_counter class - precision: cpu clock count
 */
#ifndef __cplusplus
#	error rdtsc_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifndef EXTL_INLINE_ASM_SUPPORT
#	error rdtsc_counter.h need EXTL_INLINE_ASM_SUPPORT.
#endif

/* 'rdtsc' : no return value */
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER ==1200)
#	pragma warning(disable:4035)
/* missing return statement at end of non-void function "rdtsc" */
#elif defined(EXTL_COMPILER_IS_INTEL)
#	pragma warning(disable:1011)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief rdtsc_counter class
 * \ingroup extl_group_counter
 */
class rdtsc_counter
{
	/// \name Constructors
	/// @{
	public :
		rdtsc_counter();
		~rdtsc_counter();
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
		inline void begin();
		inline void end();
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		inline interval_type	count() const;	

	private:
	#ifdef EXTL_INLINE_ASM_IN_INLINE_SUPPORT
		inline size_type		rdtsc() const;
	#else
		size_type				rdtsc() const;
	#endif
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
inline rdtsc_counter::rdtsc_counter()
:m_begin(0), m_end(0)
{
}

inline rdtsc_counter::~rdtsc_counter()
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

inline void rdtsc_counter::begin()
{
	m_begin = rdtsc();
}
inline void rdtsc_counter::end()
{
	m_end = rdtsc();
}
inline rdtsc_counter::interval_type rdtsc_counter::count() const
{
	EXTL_ASSERT(m_end >= m_begin);
	return static_cast<interval_type>(m_end - m_begin);
}

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_RDTSC_COUNTER_TEST_ENABLE
#	include "unit_test/rdtsc_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_RDTSC_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
