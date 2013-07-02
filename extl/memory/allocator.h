/* ///////////////////////////////////////////////////////////////////////
 * File:		allocator.h		
 *
 * Created:		08.02.20				
 * Updated:		08.04.14	
 *
 * Brief:		The Memory Allocator Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_ALLOCATOR_H
#define EXTL_MEMORY_ALLOCATOR_H

/*!\file allocator.h
 * \brief The Memory Allocator Library
 */

/* ///////////////////////////////////////////////////////////////////////
 * Graphs
 *
 * new_allocator             -
 * malloc_allocator           |
 * null_allocator             |
 * std::allocator             |   
 * ... ...                    | - basic_pool_allocator
 * [win]                      |
 * global_allocator           |
 * virtual_allocator          |
 * process_heap_allocator     -
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "new_allocator.h"
#include "malloc_allocator.h"
#include "null_allocator.h"
#include "basic_pool_allocator.h"
#include "allocator_selector.h"

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */
