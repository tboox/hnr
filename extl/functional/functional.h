/* ///////////////////////////////////////////////////////////////////////
 * File:		functional.h		
 *
 * Created:		08.11.20			
 * Updated:		08.11.20
 *
 * Brief:		The Functional Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_H
#define EXTL_FUNCTIONAL_H

/*!\file functional.h
 * \brief The Functional Library
 * \defgroup extl_group_functional
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std/functional.h"

#ifdef EXTL_FUNCTIONAL_FUNC_PTR_SUPPORT
#	include "func_ptr.h"
#endif

#ifdef EXTL_FUNCTIONAL_MEM_FUNC_PTR_SUPPORT
#	include "mem_func_ptr.h"
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_FUNCTIONAL_H */
/* //////////////////////////////////////////////////////////////////// */
