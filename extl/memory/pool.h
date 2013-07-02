/* ///////////////////////////////////////////////////////////////////////
 * File:		pool.h		
 *
 * Created:		08.05.04					
 * Updated:		08.05.04	
 *
 * Brief:		The Memory Pool Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_POOL_H
#define EXTL_MEMORY_POOL_H

/* ///////////////////////////////////////////////////////////////////////
 * Class Graphs
 *                pods_pool
 *              / 
 * basic_pool - 
 *              \
 *                objects_pool
 *
 *                pod_pool
 *              / 
 * fixed_pool - 
 *              \
 *                object_pool
 *
 * singleton_pool
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_pool.h"
#include "fixed_pool.h"
#include "pod_pool.h"
#include "pods_pool.h"
#include "object_pool.h"
#include "objects_pool.h"
#include "singleton_pool.h"

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_POOL_H */
/* //////////////////////////////////////////////////////////////////// */

