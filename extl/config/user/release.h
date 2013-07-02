/* ///////////////////////////////////////////////////////////////////////
 * File:		debug.h		
 *
 * Created:		08.06.30					
 * Updated:		08.06.30	
 *
 * Brief: user debug config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_USER_RELEASE_H
#define EXTL_CONFIG_USER_RELEASE_H

#ifndef  EXTL_CONFIG_USER_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unicode 
 */

// #define EXTL_UNICODE 

/* ///////////////////////////////////////////////////////////////////////
 * Debug
 */

/* Disable assertion in run-time */
 #define	EXTL_ASSERT_DISABLE 


/* ///////////////////////////////////////////////////////////////////////
 * Trace 
 */

/* Disable trace */
 #define EXTL_TRACE_DISABLE

/* Console trace */
// #define EXTL_TRACE_CONSOLE

/* File trace */
 #define EXTL_TRACE_FILE
 #define EXTL_LOG_FILE_TRACE_FILENAME	_T("extl_trace_log.log")

/* Unit-testint Trace */
 #define EXTL_LOG_TEST_FILENAME		_T("extl_unittest.log")

 #define EXTL_TRACE_LINENUM_ENABLE
 #define EXTL_TRACE_FILENAME_ENABLE
// #define EXTL_TRACE_FUNCNAME_ENABLE

/* ///////////////////////////////////////////////////////////////////////
 * Synchronous 
 */

/* Select a synchronous traits */
// #define EXTL_SYNCH_TRAITS_SINGLE_THREAD
 #define EXTL_SYNCH_TRAITS_MULTI_THREAD

/* ///////////////////////////////////////////////////////////////////////
 * Memory
 */

/* Enable memory allocator counter */
// #define EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE 

/* Allocator selector:
 *
 * null_allocator	-----							
 * new_allocator		  |							
 * malloc_allocator			- basic_pool_allocator 
 *               		  |							
 * std::allocator	-----							
 *
 * |______________________|
 *   basic allocator
 * |________________________________________________|
 *					 allocator
 */
/* Select a basic allocator as the current basic memory allocator */
// #define EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_NULL_ALLOCATOR 
// #define EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_NEW_ALLOCATOR 
 #define EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_MALLOC_ALLOCATOR 
// #define EXTL_MEMORY_BASIC_ALLOCATOR_SELECT_STD_ALLOCATOR 

/* Select an allocator as the current memory allocator */
 #define EXTL_MEMORY_ALLOCATOR_SELECT_BASIC_POOL_ALLOCATOR 
// #define EXTL_MEMORY_ALLOCATOR_SELECT_NULL_ALLOCATOR 
// #define EXTL_MEMORY_ALLOCATOR_SELECT_NEW_ALLOCATOR 
// #define EXTL_MEMORY_ALLOCATOR_SELECT_MALLOC_ALLOCATOR 
// #define EXTL_MEMORY_ALLOCATOR_SELECT_STD_ALLOCATOR 

/* ///////////////////////////////////////////////////////////////////////
 * String 
 */

/* ///////////////////////////////////////////////////////////////////////
 * Exception
 */

/* Disable exception specification */
/* #define EXTL_EXCEPTION_SPECIFICATIONS_DISABLE */

/* Enable to throw exception */
// #define EXTL_EXCEPTION_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * Other
 * Note: Some compilers may be not supported.
 */

/* Force all keyword to be supported */
/* #define EXTL_FORCE_ALL_KEYWORD_SUPPORT */

/* Force named return value optimization to be supported */
/* #define EXTL_FORCE_NRVO_SUPPORT */

/* Enable to test the version of the standard library  */
// #define EXTL_STL_VER_TEST_ENABLE 

/* Disable to use the standard library */
// #define EXTL_USE_STL_DISABLE 


/* ///////////////////////////////////////////////////////////////////////
 * Locale
 */

 #define EXTL_LOCALE_CHINESE
/* #define EXTL_LOCALE_C */
/* #define EXTL_LOCALE_DEFAULT */

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_USER_RELEASE_H */
/* //////////////////////////////////////////////////////////////////// */
