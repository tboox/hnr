/* ///////////////////////////////////////////////////////////////////////
 * File:		atomic_functions.h		
 *
 * Created:		08.03.27				
 * Updated:		08.05.05
 *
 * Brief: Platform atomic_functions library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_ATOMIC_FUNCTIONS_H
#define EXTL_PLATFORM_ATOMIC_FUNCTIONS_H

#ifndef __cplusplus
#	error atomic_functions.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../platform.h"

#if defined(EXTL_PLATFORM_IS_WIN) && \
		!defined(EXTL_WIN_NO_SUPPORT)
#	include "../../win/synch/atomic_functions.h"

#elif defined(EXTL_PLATFORM_IS_UNIX) && \
		!defined(EXTL_UNIX_NO_SUPPORT)
#	error atomic_functions.h have not be implemented.
#else 
#	error Unknown Platform.
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_ATOMIC_FUNCTIONS_H */
/* //////////////////////////////////////////////////////////////////// */
