/* ///////////////////////////////////////////////////////////////////////
 * File:		version.h
 *
 * Created:		08.02.02
 * Updated:		08.04.14
 *
 * Brief: Compiler version detect
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef  EXTL_CONFIG_COMPILER_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Intel C/C++
 * Borland C/C++
 * GNU C/C++
 * Watcom C/C++
 * Visual C++
 * Codeplay VectorC C++
 */

#ifdef EXTL_COMPILER_IS_MSVC
#	undef EXTL_COMPILER_IS_MSVC
#endif

#ifdef EXTL_COMPILER_IS_INTEL
#	undef EXTL_COMPILER_IS_INTEL
#endif

#ifdef EXTL_COMPILER_IS_BORLAND
#	undef EXTL_COMPILER_IS_BORLAND
#endif

#ifdef EXTL_COMPILER_IS_GCC
#	undef EXTL_COMPILER_IS_GCC
#endif

#ifdef EXTL_COMPILER_IS_WATCOM
#	undef EXTL_COMPILER_IS_WATCOM
#endif

#ifdef EXTL_COMPILER_IS_DMC
#	undef EXTL_COMPILER_IS_DMC
#endif

#ifdef EXTL_COMPILER_IS_UNKNOWN
#	undef EXTL_COMPILER_IS_UNKNOWN
#endif

/* Intel C++ */
#if defined(__INTEL_COMPILER)
#	define EXTL_COMPILER_IS_INTEL
#	define EXTL_COMPILER_STRING				"Intel C/C++"
#	if (__INTEL_COMPILER == 600)
#		define EXTL_COMPILER_VERSION_STRING		"Intel C/C++ 6.0"
#	elif (__INTEL_COMPILER == 700)
#		define EXTL_COMPILER_VERSION_STRING		"Intel C/C++ 7.0"
#	elif (__INTEL_COMPILER == 800)
#		define EXTL_COMPILER_VERSION_STRING		"Intel C/C++ 8.0"
#	elif (__INTEL_COMPILER == 900)
#		define EXTL_COMPILER_VERSION_STRING		"Intel C/C++ 9.0"
#	elif (__INTEL_COMPILER == 1000)
#		define EXTL_COMPILER_VERSION_STRING		"Intel C/C++ 10.0"
#	elif (__INTEL_COMPILER == 1100)
#		define EXTL_COMPILER_VERSION_STRING		"Intel C/C++ 11.0"
#	else
#		error Unknown Intel C++ Compiler Version
#	endif

/* Borland C++ */
#elif defined(__BORLANDC__)
#	define EXTL_COMPILER_IS_BORLAND
#	define EXTL_COMPILER_STRING				"Borland C/C++"
#	if 0
#		define EXTL_COMPILER_VERSION_STRING		"Borland C++ 4.52"
#	elif 0
#		define EXTL_COMPILER_VERSION_STRING		"Borland C++ 5.5"
#	elif (__BORLANDC__ == 0x0551)
#		define EXTL_COMPILER_VERSION_STRING		"Borland C++ 5.51"
#	elif (__BORLANDC__ == 0x0560)
#		define EXTL_COMPILER_VERSION_STRING		"Borland C++ 5.6"
# elif (__BORLANDC__ == 0x0564)
#		define EXTL_COMPILER_VERSION_STRING		"Borland C++ 5.6.4 (C++ BuilderX)"
#	elif (__BORLANDC__ == 0x0582)
#		define EXTL_COMPILER_VERSION_STRING		"Borland C++ 5.82 (Turbo C++)"
#	else
#		error Unknown Borland C++ Compiler Version
#	endif

/* GNU C/C++ */
#elif defined(__GNUC__)
#	define EXTL_COMPILER_IS_GCC
#	define EXTL_COMPILER_STRING				"GNU C/C++"
#	if  __GNUC__ == 2
#		if __GNUC_MINOR__ < 95
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ <2.95"
#		elif __GNUC_MINOR__ == 95
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 2.95"
#		elif __GNUC_MINOR__ == 96
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 2.96"
#		else
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ >2.96&&<3.0"
#		endif
#	elif __GNUC__ == 3
#		if __GNUC_MINOR__ == 2
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 3.2"
#		elif __GNUC_MINOR__ == 3
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 3.3"
#		elif __GNUC_MINOR__ == 4
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 3.4"
#		else
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ >3.4&&<4.0"
#		endif
#	elif __GNUC__ == 4
#		if __GNUC_MINOR__ == 1
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 4.1"
#		elif __GNUC_MINOR__ == 2
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 4.2"
#		elif __GNUC_MINOR__ == 3
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 4.3"
#		elif __GNUC_MINOR__ == 4
#			define EXTL_COMPILER_VERSION_STRING		"GNU C/C++ 4.4"
#		endif
#	else
#		error Unknown GNU C/C++ Compiler Version
#	endif

/* Watcom C/C++ */
#elif defined(__WATCOMC__)
#	define EXTL_COMPILER_IS_WATCOM
#	define EXTL_COMPILER_STRING				"Watcom C/C++"
#	if (__WATCOMC__ == 1100)
#		define EXTL_COMPILER_VERSION_STRING      "Watcom C/C++ 11.0"
#	elif (__WATCOMC__ == 1200)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.0 (Watcom 12.0)"
#	elif (__WATCOMC__ == 1210)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.1 (Watcom 12.1)"
#	elif (__WATCOMC__ == 1220)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.2 (Watcom 12.2)"
#	elif (__WATCOMC__ == 1230)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.3 (Watcom 12.3)"
#	elif (__WATCOMC__ == 1240)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.4 (Watcom 12.4)"
#	elif (__WATCOMC__ == 1250)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.5"
#	elif (__WATCOMC__ == 1260)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.6"
#	elif (__WATCOMC__ == 1270)
#		define EXTL_COMPILER_VERSION_STRING      "Open Watcom C/C++ 1.7"
#	else
#		error Unknown Watcom C/C++ Compiler Version
#	endif

/* Digital Mars C/C++ */
#elif defined(__DMC__)
#	define EXTL_COMPILER_IS_DMC
#	define EXTL_COMPILER_STRING          "Digital Mars C/C++"
#	if (__DMC__ < 0x0826)
#		error Only versions 8.26 and later of the Digital Mars C/C++ compilers are supported by the EXTL libraries
#	else
#		if __DMC__ >= 0x0832
#			define EXTL_COMPILER_VERSION_STRING      __DMC_VERSION_STRING__
#		elif (__DMC__ == 0x0826)
#			define EXTL_COMPILER_VERSION_STRING      "Digital Mars C/C++ 8.26"
#		elif (__DMC__ == 0x0827)
#			define EXTL_COMPILER_VERSION_STRING      "Digital Mars C/C++ 8.27"
#		elif (__DMC__ == 0x0828)
#			define EXTL_COMPILER_VERSION_STRING      "Digital Mars C/C++ 8.28"
#		elif (__DMC__ == 0x0829)
#			define EXTL_COMPILER_VERSION_STRING      "Digital Mars C/C++ 8.29"
#		elif (__DMC__ == 0x0830)
#			define EXTL_COMPILER_VERSION_STRING      "Digital Mars C/C++ 8.30"
#		elif (__DMC__ == 0x0831)
#			define EXTL_COMPILER_VERSION_STRING      "Digital Mars C/C++ 8.31"
#		else
#			error Unknown Digital Mars C/C++ Compiler Version
#		endif
#	endif

/* Codeplay VectorC C/C++ */
#elif defined(__VECTORC)
#	define EXTL_COMPILER_IS_VECTORC
#	define EXTL_COMPILER_VERSION_STRING          "CodePlay VectorC C/C++"
#	if (__VECTORC == 1)
#		define EXTL_COMPILER_VERSION_STRING       "CodePlay VectorC C/C++"
#	else
#		error Unknown CodePlay VectorC C++ Compiler Version
#	endif

/* Visual C++ */
#elif defined(_MSC_VER)
#	define EXTL_COMPILER_IS_MSVC
#		define EXTL_COMPILER_STRING				"Visual C++"
#	if defined(EXTL_FORCE_MSVC_4_2) && (_MSC_VER == 1020)
#		define EXTL_COMPILER_VERSION_STRING		"Visual C++ 4.2"
#	elif (_MSC_VER == 1100)
#		define EXTL_COMPILER_VERSION_STRING      "Visual C++ 5.0"
#	elif (_MSC_VER == 1200)
#		define EXTL_COMPILER_VERSION_STRING      "Visual C++ 6.0"
#	elif (_MSC_VER == 1300)
#		define EXTL_COMPILER_VERSION_STRING      "Visual C++ .NET (7.0)"
#	elif (_MSC_VER == 1310)
#		define EXTL_COMPILER_VERSION_STRING      "Visual C++ .NET (7.1)"	/* .NET 2003 */
#	elif (_MSC_VER == 1400)
#		define EXTL_COMPILER_VERSION_STRING      "Visual C++ .NET (8.0)"	/* .NET 2005 */
#	elif (_MSC_VER == 1500)
#		define EXTL_COMPILER_VERSION_STRING      "Visual C++ .NET (9.0)"	/* .NET 2008 */
#	else
#		error Unknown Visual C++ Compiler Version
#	endif

#else
#	define EXTL_COMPILER_STRING				"Unknown Compiler"
#	define EXTL_COMPILER_VERSION_STRING		"Unknown Compiler Version"
#	define EXTL_COMPILER_IS_UNKNOWN
#endif
