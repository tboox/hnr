/* ///////////////////////////////////////////////////////////////////////
 * File:		allocator.h		
 *
 * Created:		08.02.17				
 * Updated:		08.05.05
 *
 * Brief: Platform allocators library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_MEMORY_ALLOCATOR_H
#define EXTL_PLATFORM_MEMORY_ALLOCATOR_H

#ifndef __cplusplus
#	error allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../platform.h"

/* ///////////////////////////////////////////////////////////////////////
 * Windows allocators 
 */
#if defined(EXTL_PLATFORM_IS_WIN) && \
		!defined(EXTL_WIN_NO_SUPPORT)

#	ifndef EXTL_PLATFORM_WIN_MEMORY_ALLOCATOR_H
#		include "../../win/memory/allocator.h"
#	endif

/* Unix allocators */
#elif defined(EXTL_PLATFORM_IS_UNIX) && \
	!defined(EXTL_UNIX_NO_SUPPORT)
#	error allocator.h have not be implemented.
#else 
#	error Unknown Operating system.
#endif 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_MEMORY_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */
