/* ///////////////////////////////////////////////////////////////////////
 * File:		offsetof.h		
 *
 * Created:		08.02.22				
 * Updated:		08.05.05	
 *
 * Brief: The offset of a given member within a class, struct or union type
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_OFFSET_OF_H
#define EXTL_UTILITY_OFFSET_OF_H

/*!\file offsetof.h
 * \brief The offset of a given member within a class, struct or union type
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#ifdef EXTL_OFFSET_OF
#	undef EXTL_OFFSET_OF
#endif

#ifdef __cplusplus
/* GCC warning: invalid access to non-static data member of NULL object */
#	if defined(EXTL_COMPILER_IS_GCC)
#		define EXTL_OFFSET_OF(S, M)	\
			(reinterpret_cast< EXTL_NS(e_size_t) >(&reinterpret_cast<S*>(1)->M) - 1)
#	else
#		define EXTL_OFFSET_OF(S, M)	\
			(reinterpret_cast< EXTL_NS(e_size_t) >(&reinterpret_cast<S*>(0)->M))
#	endif
#else
#	define EXTL_OFFSET_OF(S, M)	((e_size_t)&((S*)(0))->M)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_UTILITY_OFFSET_OF_TEST_ENABLE
#	include "unit_test/offset_of_test.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_OFFSET_OF_H */
/* //////////////////////////////////////////////////////////////////// */
