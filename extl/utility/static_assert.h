/* ///////////////////////////////////////////////////////////////////////
 * File:		static_assert.h		
 *
 * Created:		08.02.02				
 * Updated:		08.05.05	
 *
 * Brief: static assertion
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_STATIC_ASSERT_H
#define EXTL_UTILITY_STATIC_ASSERT_H

/*!\file static_assert.h
 * \brief static assertion
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * static assertion
 */
#if defined(EXTL_0x_STATIC_ASSERT_SUPPORT) // c++0x

#	define EXTL_STATIC_ASSERT(expr)		static_assert(expr, "")

#elif defined(__cplusplus) && \
		defined(EXTL_TEMPLATE_SPEC_SUPPORT) && \
			!defined(EXTL_COMPILER_IS_VECTORC)

	template < bool x > 
	struct extl_static_assertion_failure;

	EXTL_TEMPLATE_SPECIALISATION
	struct extl_static_assertion_failure< true > 
	{ 
		enum 
		{ 
			value = 1 
		}; 
	};
	template < int x > 
	struct extl_static_assert_test{};

#	define EXTL_STATIC_ASSERT(expr)	do{ typedef EXTL_NS(extl_static_assert_test)<\
										sizeof(EXTL_NS(extl_static_assertion_failure)< (bool)( expr ) >) > extl_static_assert; } while(0)
#else 
#	if (defined(EXTL_COMPILER_IS_GCC) && \
			(__GNUC__ < 3 || \
				(__GNUC__ == 3 && \
					__GNUC_MINOR__ < 4))) || \
		 defined(EXTL_COMPILER_IS_INTEL) || \
			defined(EXTL_COMPILER_IS_DMC)
#		define EXTL_STATIC_ASSERT(ex)        do { typedef int ai[(ex) ? 1 : -1]; } while(0)
#	else
#		define EXTL_STATIC_ASSERT(ex)        do { typedef int ai[(ex) ? 1 : 0]; } while(0)
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_STATIC_ASSERT_H */
/* //////////////////////////////////////////////////////////////////// */
