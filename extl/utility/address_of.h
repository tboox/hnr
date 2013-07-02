/* ///////////////////////////////////////////////////////////////////////
 * File:		address_of.h		
 *
 * Created:		08.04.01				
 * Updated:		08.04.14	
 *
 * Brief: Gets the real address of object 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_ADDRESS_OF_H
#define EXTL_UTILITY_ADDRESS_OF_H

/*!\file address_of.h
 * \brief Gets the real address of object 
 *
 * Solves to the problem that the object overloaded operator& can not get it's real address
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h" 

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#ifdef EXTL_ADDRESS_OF
#	undef EXTL_ADDRESS_OF
#endif

#ifdef __cplusplus
#	define EXTL_ADDRESS_OF(V)	(address_of(V))
#else
#	define EXTL_ADDRESS_OF(V)	(&V)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#ifdef __cplusplus
/* VC7.0: needs return the pointer type indirectly */
#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1300 

template<typename_param_k T> 
struct addptr_
{
	typedef T* type;
};
template < typename_param_k T > 
EXTL_INLINE typename_type_ret_k addptr_<T>::type address_of(T& v)

#else
/// address_of
template < typename_param_k T >
EXTL_INLINE T* address_of(T const volatile& v) /* WATCOM: must add cv-qualified */

#endif
{
	return reinterpret_cast<T*>(
		&const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
}

/* Borland: Cannot cast from 'int *' to 'const volatile char &' */
/* DMC: non-const reference initialized to temporary */
#if defined(EXTL_COMPILER_IS_BORLAND) || \
				defined(EXTL_COMPILER_IS_DMC) 

/// address_of
template< typename_param_k T, e_size_t N >
EXTL_INLINE T (*address_of(T (&t)[N]))[N]
{
   return reinterpret_cast<T(*)[N]>(&t);
}
/// address_of
template< typename_param_k T, e_size_t N >
EXTL_INLINE const T (*address_of(const T (&t)[N]))[N]
{
   return reinterpret_cast<const T(*)[N]>(&t);
}

#endif
#endif /* __cplusplus */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_UTILITY_ADDRESS_OF_TEST_ENABLE
#	include "unit_test/address_of_test.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_ADDRESS_OF_H */
/* //////////////////////////////////////////////////////////////////// */
