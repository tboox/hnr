/* ///////////////////////////////////////////////////////////////////////
 * File:		int_.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: int_ class - integer type wrap
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_INT_H
#define EXTL_MPL_INT_H

/*!\file int_.h
 * \brief int_ class - logical operation 
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_BEGIN_WHOLE_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_MPL_SUPPORT

/* ///////////////////////////////////////////////////////////////////////
 * Integer wrap 
 */
#ifndef EXTL_MPL_INT_WRAP
#	define EXTL_MPL_INT_WRAP(name, v_t)			\
template< v_t N >								\
struct name										\
{												\
	EXTL_STATIC_MEMBER_CONST(v_t, value = N);	\
												\
	typedef name<N>			type;				\
	typedef v_t				value_t;			\
												\
	typedef name<N-1>		prior;				\
	typedef name<N+1>		next;				\
												\
	operator v_t() const						\
	{											\
		return static_cast<v_t>(this->value);	\
	}											\
};
#endif

EXTL_MPL_INT_WRAP(int_, e_int_t)
EXTL_MPL_INT_WRAP(sint_, e_sint_t)
EXTL_MPL_INT_WRAP(uint_, e_uint_t)

EXTL_MPL_INT_WRAP(int8_, e_int8_t)
EXTL_MPL_INT_WRAP(sint8_, e_sint8_t)
EXTL_MPL_INT_WRAP(uint8_, e_uint8_t)

EXTL_MPL_INT_WRAP(int16_, e_int16_t)
EXTL_MPL_INT_WRAP(sint16_, e_sint16_t)
EXTL_MPL_INT_WRAP(uint16_, e_uint16_t)

EXTL_MPL_INT_WRAP(int32_, e_int32_t)
EXTL_MPL_INT_WRAP(sint32_, e_sint32_t)
EXTL_MPL_INT_WRAP(uint32_, e_uint32_t)

#if defined(EXTL_64BIT_INT_SUPPORT)
EXTL_MPL_INT_WRAP(int64_, e_int64_t)
EXTL_MPL_INT_WRAP(sint64_, e_sint64_t)
EXTL_MPL_INT_WRAP(uint64_, e_uint64_t)
#endif

EXTL_MPL_INT_WRAP(long_, e_long_t)
EXTL_MPL_INT_WRAP(ulong_, e_ulong_t)

/* Maximum integer type as template param */
#if defined(EXTL_64BIT_INT_SUPPORT) && \
		!defined(EXTL_COMPILER_IS_BORLAND) /* BORLAND: 64-bit maybe overflow */
typedef	e_int64_t e_max_int_t;
typedef	e_int64_t e_smax_int_t;
typedef	e_uint64_t e_umax_int_t;
#else
typedef	e_int32_t e_max_int_t;
typedef	e_int32_t e_smax_int_t;
typedef	e_uint32_t e_umax_int_t;
#endif

EXTL_MPL_INT_WRAP(max_int_, e_max_int_t)
EXTL_MPL_INT_WRAP(smax_int_, e_smax_int_t)
EXTL_MPL_INT_WRAP(umax_int_, e_umax_int_t)

#undef EXTL_MPL_INT_WRAP

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MPL_INT_H */
/* //////////////////////////////////////////////////////////////////// */
