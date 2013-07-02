/* ///////////////////////////////////////////////////////////////////////
 * File:		container.h		
 *
 * Created:		08.07.29				
 * Updated:		08.07.29	
 *
 * Brief: The Container Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_H
#define EXTL_CONTAINER_H

/*!\file container.h
 * \brief The container library
 * \defgroup extl_group_container
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#ifdef EXTL_CONTAINER_FIXED_MARRAY_SUPPORT
#	include "marray.h"
#endif

#ifdef EXTL_CONTAINER_TUPLE_SUPPORT
#	include "tuple.h"
#endif

#include "hash.h"
#include "matrix.h"
#include "array.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "bit.h"
#include "pair.h"

#ifdef EXTL_CONTAINER_NET_SUPPORT
#	include "net.h"
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_H */
/* //////////////////////////////////////////////////////////////////// */
