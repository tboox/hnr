/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.02					
 * Updated:		08.04.14
 *
 * Brief: compiler traits config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONFIG_COMPILER_H
#define EXTL_CONFIG_COMPILER_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Detecting compiler version
 */
#include "version.h"

#include "undefs.h"
#if defined(EXTL_COMPILER_IS_MSVC)
#	include "msvc.h"
#elif defined(EXTL_COMPILER_IS_INTEL)
#	include "intel.h"
#elif defined(EXTL_COMPILER_IS_BORLAND)
#	include "borland.h"
#elif defined(EXTL_COMPILER_IS_WATCOM)
#	include "watcom.h"
#elif defined(EXTL_COMPILER_IS_GCC)
#	include "gcc.h"
#elif defined(EXTL_COMPILER_IS_DMC)
#	include "dmc.h"
#elif defined(EXTL_COMPILER_IS_VECTORC)
#	include "vectorc.h"
#else
#	error Unknown Compiler
#endif 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_COMPILER_H */
/* //////////////////////////////////////////////////////////////////// */
