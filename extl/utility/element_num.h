/* ///////////////////////////////////////////////////////////////////////
 * File:		element_num.h		
 *
 * Created:		08.02.02				
 * Updated:		08.04.14	
 *
 * Brief: Gets the number of elements in the array 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_ELEMENT_NUM_H
#define EXTL_UTILITY_ELEMENT_NUM_H

/*!\file element_num.h
 * \brief Gets the number of elements in the array 
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "static_assert.h"
#include "../type/typedef.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#if defined(__cplusplus) && \
     defined(EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT)

#	if defined(EXTL_COMPILER_IS_GCC)

#		pragma pack(push, 1)
		template < e_uint_t N >
		struct extl_array_size
		{
			e_byte_t c[N];
		};
#		pragma pack(pop)

		template < typename_param_k T, e_uint_t N >
		extl_array_size<N> const& extl_static_array_size(T (&)[N]);

		/// EXTL_ELEMENT_NUM
#		define EXTL_ELEMENT_NUM(ar)	sizeof(EXTL_NS(extl_static_array_size)(ar))
#	else

		template < e_uint_t N >
		struct extl_array_size
		{
			e_byte_t c[N];
		};

		/* Passing array by reference will not cause pointer decay  */
		template < typename_param_k  T, e_uint_t N >
		extl_array_size<N> const& extl_static_array_size(T (&)[N]);
		
		/// EXTL_ELEMENT_NUM
#		define EXTL_ELEMENT_NUM(ar)	sizeof(EXTL_NS(extl_static_array_size)(ar).c)
#	endif /* EXTL_COMPILER_IS_GCC */
#else
	/*!\brief EXTL_ELEMENT_NUM does'nt support array-to-pointer decay
	 *
	 * int ar[10];
	 * int *p=ar; //or int *p=&ar[0];
	 * EXTL_ELEMENT_NUM(ar) == 10
	 * EXTL_ELEMENT_NUM(p)  ?= 1 
	 */
#	define EXTL_ELEMENT_NUM(ar)	(sizeof(ar) / sizeof(0[(ar)]))
#endif /* defined(__cplusplus) && \
		  defined(EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT) */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_UTILITY_ELEMENT_NUM_TEST_ENABLE
#	include "unit_test/element_num_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_UTILITY_ELEMENT_NUM_H */
/* //////////////////////////////////////////////////////////////////// */


