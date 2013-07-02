/* ///////////////////////////////////////////////////////////////////////
 * File:		tuple.h		
 *
 * Created:		08.07.21		
 * Updated:		08.07.21
 *
 * Brief: tuple class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_TUPLE_H
#define EXTL_CONTAINER_TUPLE_H

/*!\file tuple.h
 * \brief tuple class
 */
#ifndef __cplusplus
#	error tuple.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_CONTAINER_TUPLE_SUPPORT)
#	error tuple.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_0x_VARIADIC_TEMPLATE_SUPPORT
#	include "detail/tuple_impl_0x.h"
#else
#	include "detail/tuple_impl.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_CONTAINER_TUPLE_H */
/* //////////////////////////////////////////////////////////////////// */
