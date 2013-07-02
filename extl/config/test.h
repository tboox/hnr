/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.03.30					
 * Updated:		08.04.14	
 *
 * Brief:		The Unit-testing config
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_TEST_H
#define EXTL_CONFIG_TEST_H

#ifndef  EXTL_CONFIG_H
#	error This file must be included of config.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing 
 */

/* type size */
// #define	EXTL_TYPE_SIZE_TEST_ENABLE 

/* type traits */
// #define	EXTL_TYPE_TRAITS_TEST_ENABLE 

/* exception error */
// #define	EXTL_ERROR_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * algorithm
 */

/* max_min */
// #define	EXTL_ALGORITHM_MAX_MIN_TEST_ENABLE 

/* sort */
// #define	EXTL_ALGORITHM_SORT_TEST_ENABLE 
/* ///////////////////////////////////////////////////////////////////////
 * intelligence\ga
 */

/* ga */
// #define	EXTL_INTELLIGENCE_GA_GA_TEST_ENABLE 

/* uga */
// #define	EXTL_INTELLIGENCE_GA_UGA_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * intelligence\ann
 */

/* bp_network */
// #define	EXTL_INTELLIGENCE_ANN_BP_NETWORK_TEST_ENABLE 

/* perceptron_network */
// #define	EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_TEST_ENABLE 

/* wga_network */
// #define	EXTL_INTELLIGENCE_ANN_WGA_NETWORK_TEST_ENABLE 

/* bagging_networks */
// #define EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_TEST_ENABLE

/* ada_boosting_networks */
// #define EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_NETWORKS_TEST_ENABLE

/* pca_network */
// #define EXTL_INTELLIGENCE_ANN_PCA_NETWORK_TEST_ENABLE

/* pca_mixed_network */
// #define EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_TEST_ENABLE
/* ///////////////////////////////////////////////////////////////////////
 * Container
 */
/* tuple */
// #define	EXTL_CONTAINER_TUPLE_TEST_ENABLE

/* multiple array */
// #define	EXTL_CONTAINER_MARRAY_TEST_ENABLE

/* array */
// #define	EXTL_CONTAINER_ARRAY_TEST_ENABLE

/* matrix */
// #define	EXTL_CONTAINER_MATRIX_TEST_ENABLE

/* queue */
// #define	EXTL_CONTAINER_QUEUE_TEST_ENABLE

/* list */
// #define	EXTL_CONTAINER_LIST_TEST_ENABLE

/* hash */
// #define	EXTL_CONTAINER_HASH_TEST_ENABLE

/* bit_field */
// #define	EXTL_CONTAINER_BIT_FIELD_TEST_ENABLE

/* fixed_bit_field */
// #define	EXTL_CONTAINER_FIXED_BIT_FIELD_TEST_ENABLE

/* bit_array */
// #define	EXTL_CONTAINER_BIT_ARRAY_TEST_ENABLE

/* net */
// #define	EXTL_CONTAINER_NET_TEST_ENABLE

/* ///////////////////////////////////////////////////////////////////////
 * Math 
 */

/* val-matrix */
// #define	EXTL_MATH_VMATRIX_TEST_ENABLE

/* val-vector */
// #define EXTL_MATH_VVECTOR_TEST_ENABLE

/* ///////////////////////////////////////////////////////////////////////
 * Functional
 */
/* func_ptr */
// #define	EXTL_FUNCTIONAL_FUNC_PTR_TEST_ENABLE 

/* mem_func_ptr */
// #define	EXTL_FUNCTIONAL_MEM_FUNC_PTR_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * Counter
 */
/* shared_counter */
// #define	EXTL_COUNTER_SHARED_COUNTER_TEST_ENABLE 

/* object_counter */
// #define	EXTL_COUNTER_OBJECT_COUNTER_TEST_ENABLE 

/* clock_counter */
// #define	EXTL_COUNTER_CLOCK_COUNTER_TEST_ENABLE 

/* highperformance_counter */
// #define	EXTL_COUNTER_HIGHPERFORMANCE_COUNTER_TEST_ENABLE 

/* multimedia_counter */
// #define	EXTL_COUNTER_MULTIMEDIA_COUNTER_TEST_ENABLE 

/* processtimes_counter */
// #define	EXTL_COUNTER_PROCESSTIMES_COUNTER_TEST_ENABLE 

/* rdtsc_counter */
// #define	EXTL_COUNTER_RDTSC_COUNTER_TEST_ENABLE 

/* systemtime_counter */
// #define	EXTL_COUNTER_SYSTEMTIME_COUNTER_TEST_ENABLE 

/* threadtimes_counter */
// #define	EXTL_COUNTER_THREADTIMES_COUNTER_TEST_ENABLE 

/* tick_counter */
// #define	EXTL_COUNTER_TICK_COUNTER_TEST_ENABLE 
/* ///////////////////////////////////////////////////////////////////////
 * Conversion
 */

/* atow */
// #define	EXTL_CONVERSION_ATOW_TEST_ENABLE

/* wtoa */
// #define	EXTL_CONVERSION_WTOA_TEST_ENABLE 

/* itos */
// #define	EXTL_CONVERSION_ITOS_TEST_ENABLE

/* stoi */
// #define	EXTL_CONVERSION_STOI_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * Mpl
 */
/* if_ */
// #define	EXTL_MPL_IF_TEST_ENABLE 

/* is_even */
// #define	EXTL_MPL_MATH_IS_EVEN_TEST_ENABLE 

/* is_prime */
// #define	EXTL_MPL_MATH_IS_PRIME_TEST_ENABLE 

/* log */
// #define	EXTL_MPL_MATH_LOG_TEST_ENABLE 

/* pow */
// #define	EXTL_MPL_MATH_POW_TEST_ENABLE 

/* pi */
// #define	EXTL_MPL_MATH_PI_TEST_ENABLE 

/* sqrt */
// #define	EXTL_MPL_MATH_SQRT_TEST_ENABLE 

/* factorial */
// #define	EXTL_MPL_MATH_FACTORIAL_TEST_ENABLE 

/* max_min */
// #define	EXTL_MPL_MATH_MAX_MIN_TEST_ENABLE 
/* ///////////////////////////////////////////////////////////////////////
 * Smart ptr 
 */

/* shared ptr */
// #define	EXTL_SHARED_PTR_TEST_ENABLE 

/* scoped ptr */
// #define	EXTL_SCOPED_PTR_TEST_ENABLE 

/* shared array */
// #define	EXTL_SHARED_ARRAY_TEST_ENABLE 

/* scoped array */
// #define	EXTL_SCOPED_ARRAY_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * Synchronization 
 */

/* synchronization lock */
// #define	EXTL_SYNCH_LOCK_TEST_ENABLE 

 /* atomic functions */
// #define	EXTL_SYNCH_ATOMIC_FUNCTIONS_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * Memory 
 */

/* scoped_buffer */
// #define	EXTL_MEMORY_SCOPED_BUFFER_TEST_ENABLE 

/* memory allocator */
// #define	EXTL_MEMORY_ALLOCATOR_TEST_ENABLE 

/* memory pool */
// #define	EXTL_MEMORY_BASIC_POOL_TEST_ENABLE 
// #define	EXTL_MEMORY_FIXED_POOL_TEST_ENABLE 
// #define	EXTL_MEMORY_OBJECT_POOL_TEST_ENABLE 
// #define	EXTL_MEMORY_OBJECTS_POOL_TEST_ENABLE 
// #define	EXTL_MEMORY_POD_POOL_TEST_ENABLE 
// #define	EXTL_MEMORY_PODS_POOL_TEST_ENABLE 

/* memory helpful functions */
// #define	EXTL_MEMORY_HELP_FUNCTIONS_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * String
 */

/* std_char_traits */
// #define	EXTL_STRING_STD_CHAR_TRAITS_TEST_ENABLE 

/* string_traits */
// #define	EXTL_STRING_STRING_TRAITS_TEST_ENABLE 

/* stack_string */
// #define	EXTL_STRING_STACK_STRING_TEST_ENABLE 

/* scoped_string */
// #define	EXTL_STRING_SCOPED_STRING_TEST_ENABLE 

/* attached_string */
// #define	EXTL_STRING_ATTACHED_STRING_TEST_ENABLE 
/* ///////////////////////////////////////////////////////////////////////
 * Utility
 */

/* element_num */
// #define	EXTL_UTILITY_ELEMENT_NUM_TEST_ENABLE 

/* operator_bool */
// #define	EXTL_UTILITY_OPERATOR_BOOL_TEST_ENABLE 

/* operators */
// #define	EXTL_UTILITY_OPERATORS_TEST_ENABLE 

/* offset_of */
// #define	EXTL_UTILITY_OFFSET_OF_TEST_ENABLE 

/* address_of */
// #define	EXTL_UTILITY_ADDRESS_OF_TEST_ENABLE 

/* properties */
// #define	EXTL_UTILITY_PROPERTIES_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * Complier 
 */

/* compiler_traits */
// #define	EXTL_COMPILER_TRAITS_TEST_ENABLE 

/* ebo_traits */
// #define	EXTL_COMPILER_TRAITS_EBO_TRAITS_TEST_ENABLE 

/* edo_traits */
// #define	EXTL_COMPILER_TRAITS_EDO_TRAITS_TEST_ENABLE 

/* rvo_traits */
// #define	EXTL_COMPILER_TRAITS_RVO_TRAITS_TEST_ENABLE 

/* ///////////////////////////////////////////////////////////////////////
 * System
 */
// #define EXTL_SYSTEM_TRAITS_TEST_ENABLE

/* ///////////////////////////////////////////////////////////////////////
 * Filesystem
 */
/* filesystem_traits */
// #define EXTL_FILESYSTEM_TRAITS_TEST_ENABLE

/* path_traits */
// #define EXTL_PATH_TRAITS_TEST_ENABLE

/* path */
// #define EXTL_PATH_TEST_ENABLE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
