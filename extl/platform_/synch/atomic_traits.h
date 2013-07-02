/* ///////////////////////////////////////////////////////////////////////
 * File:		atomic_traits.h		
 *
 * Created:		08.03.27					
 * Updated:		09.01.15
 *
 * Brief:		the atomic_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SYNCH_ATOMIC_TRAITS_H
#define EXTL_SYNCH_ATOMIC_TRAITS_H

/*!\file atomic_traits.h
 * \brief atomic_traits class
 */
#ifndef __cplusplus
#	error atomic_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#if defined(EXTL_PLATFORM_IS_UNIX)
#	include "../unix/synch/atomic_func.h"
#elif defined(EXTL_PLATFORM_IS_WINDOWS)
#	include "../windows/synch/atomic_func.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE 

/*!\brief atomic_traits class
 *
 * \param is_atomic: is_atomic will be \true if operation is atomic
 *
 * \ingroup extl_group_synch
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT	
template<e_bool_t is_atomic = e_true_v>
#else
template<e_bool_t is_atomic>
#endif
class atomic_traits 
{
	/// \name Types
	/// @{
	public:
		typedef atomic_traits<is_atomic>			class_type;
		typedef e_size_t							size_type;
		typedef EXTL_NS_PLATFORM_SPEC(e_atomic_t)	atomic_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// increase 
		static void inc(atomic_type volatile* p)
		{
			EXTL_NS_PLATFORM_SPEC(atomic_inc)(p);
		}
		/// decrease 
		static void dec(atomic_type volatile* p)
		{
			EXTL_NS_PLATFORM_SPEC(atomic_dec)(p);
		}

		/// ++i 
		static atomic_type preinc(atomic_type volatile* p)
		{
			return EXTL_NS_PLATFORM_SPEC(atomic_preinc)(p);
		}
		/// --i 
		static atomic_type predec(atomic_type volatile* p)
		{
			return EXTL_NS_PLATFORM_SPEC(atomic_predec)(p);
		}

		/// i++ 
		static atomic_type postinc(atomic_type volatile* p)
		{
			return EXTL_NS_PLATFORM_SPEC(atomic_postinc)(p);
			
		}
		/// i-- 
		static atomic_type postdec(atomic_type volatile* p)
		{
			return EXTL_NS_PLATFORM_SPEC(atomic_postdec)(p);
		}
		/// write 
		static void write(atomic_type volatile* p, size_type n)
		{
			EXTL_NS_PLATFORM_SPEC(atomic_write)(p, n);
			
		}
		/// read 
		static atomic_type read(atomic_type volatile* p)
		{
			return EXTL_NS_PLATFORM_SPEC(atomic_read)(p);
		}
	/// @}
};

/*!\brief atomic_traits<e_false_v> class - non-atomic operation 
 *
 * \ingroup extl_group_synch
 */
EXTL_TEMPLATE_SPECIALISATION
class atomic_traits<e_false_v> 
{
	/// \name Types
	/// @{
	public:
		typedef atomic_traits<e_false_v>				class_type;
		typedef e_size_t								size_type;
		typedef size_type								atomic_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// increase 
		static void inc(atomic_type volatile* p)
		{
			++*p;
		}
		/// decrease 
		static void dec(atomic_type volatile* p)
		{
			--*p;
		}

		/// ++i 
		static atomic_type preinc(atomic_type volatile* p)
		{
			return ++*p;
		}
		/// --i 
		static atomic_type predec(atomic_type volatile* p)
		{
			return --*p;
		}

		/// i++ 
		static atomic_type postinc(atomic_type volatile* p)
		{
			atomic_type t = *p;
			++*p;
			return t;
			
		}
		/// i-- 
		static atomic_type postdec(atomic_type volatile* p)
		{
			atomic_type t = *p;
			--*p;
			return t;
		}
		/// write 
		static void write(atomic_type volatile* p, size_type n)
		{
			*p = n;
		}
		/// read 
		static atomic_type read(atomic_type volatile* p)
		{
			return *p;
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_ATOMIC_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
