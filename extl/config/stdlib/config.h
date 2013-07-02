/* ///////////////////////////////////////////////////////////////////////
 * File:		config.h		
 *
 * Created:		08.02.02				
 * Updated:		08.04.15	
 *
 * Brief: Standard library config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_STDLIB_H
#define EXTL_CONFIG_STDLIB_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

/* //////////////////////////////////////////////////////////////////// */
#ifdef EXTL_NO_STL
#	undef EXTL_NO_STL
#endif 

#ifdef EXTL_STL_VER_IS_DINKUMWARE
#	undef EXTL_STL_VER_IS_DINKUMWARE
#endif 

#ifdef EXTL_STL_VER_IS_DINKUMWARE_FOR_VC
#	undef EXTL_STL_VER_IS_DINKUMWARE_FOR_VC
#endif 

#ifdef EXTL_STL_VER_IS_DINKUMWARE_FOR_BORLAND
#	undef EXTL_STL_VER_IS_DINKUMWARE_FOR_BORLAND
#endif

#ifdef EXTL_STL_VER_IS_STLPORT
#	undef EXTL_STL_VER_IS_STLPORT
#endif 

#ifdef EXTL_STL_VER_IS_MSL
#	undef EXTL_STL_VER_IS_MSL
#endif

#ifdef EXTL_STL_VER_IS_SGI_GNU
#	undef EXTL_STL_VER_IS_SGI_GNU
#endif 

#ifdef EXTL_STL_VER_IS_SGI
#	undef EXTL_STL_VER_IS_SGI
#endif 

#ifdef EXTL_STL_VER_IS_ROGUEWARE
#	undef EXTL_STL_VER_IS_ROGUEWARE
#endif 

/* //////////////////////////////////////////////////////////////////// */
#if !defined(EXTL_COMPILER_IS_DMC) && \
		!defined(EXTL_COMPILER_IS_WATCOM) && \
			!defined(EXTL_USE_STL_DISABLE)
#	include <utility>
#else
#	define EXTL_NO_STL	/* not exist stl */
#endif

/* STLport include some other libraries, so it must be put the first position */
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION) 
#	define EXTL_STL_VER_IS_STLPORT
#	define EXTL_STL_VER_STRING	"STLport"
#	ifdef EXTL_STL_VER_TEST_ENABLE
#		pragma message("STLport")
#	endif
//#	include "stlport.h"

/* Rogue Wave Standary Library */
#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
#	define EXTL_STL_VER_IS_ROGUEWARE
#	define EXTL_STL_VER_STRING	"Rogue Wave"
#	ifdef EXTL_STL_VER_TEST_ENABLE
#		pragma message("Rogue Wave")
#	endif
//#	include "roguewave.h"

/* GNU */
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__) 
#	define EXTL_STL_VER_IS_SGI_GNU
#	define EXTL_STL_VER_STRING	"SGI GNU"
#	ifdef EXTL_STL_VER_TEST_ENABLE
#		pragma message("SGI GNU")
#	endif
//#	include "gnu.h"

/* SGI */
#elif defined(__STL_CONFIG_H) 
#	define EXTL_STL_VER_IS_SGI
#	define EXTL_STL_VER_STRING	"SGI"
#	ifdef EXTL_STL_VER_TEST_ENABLE
#		pragma message("SGI")
#	endif

/* Metrowerks' MSL Standary Library */
#elif defined(__MSL_CPP__) 
#	define EXTL_STL_VER_IS_MSL
#	define EXTL_STL_VER_STRING	"MSL"
#	ifdef EXTL_STL_VER_TEST_ENABLE
#		pragma message("MSL")
#	endif
//#	include "msl.h"

/* Dinkumware Standary Library */
#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER) 

#	define EXTL_STL_VER_IS_DINKUMWARE

#	if defined(EXTL_COMPILER_IS_INTEL) || \
			defined(EXTL_COMPILER_IS_MSVC) || \
				( defined(EXTL_COMPILER_IS_VECTORC) && defined(_MSC_VER) )
#		define EXTL_STL_VER_IS_DINKUMWARE_FOR_VC
#		define EXTL_STL_VER_STRING	"Dinkumware for VC++"
#		ifdef EXTL_STL_VER_TEST_ENABLE
#			pragma message("Dinkumware for VC++")
#		endif
#	elif defined(EXTL_COMPILER_IS_BORLAND)
#		define EXTL_STL_VER_IS_DINKUMWARE_FOR_BORLAND
#		define EXTL_STL_VER_STRING	"Dinkumware for Borland"
#		ifdef EXTL_STL_VER_TEST_ENABLE
#			pragma message("Dinkumware for Borland")
#		endif
#	else
#		error  Dinkumware standard library with unknown compiler.
#	endif

//#	include "dinkumware.h"
#else
#	ifndef EXTL_NO_STL
#		error Unknown standard library
#	endif
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_STDLIB_H */
/* //////////////////////////////////////////////////////////////////// */
