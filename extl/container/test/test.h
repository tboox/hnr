/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.11.24			
 * Updated:		08.11.24
 *
 * Brief:		The Container Library Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_TEST_H
#define EXTL_CONTAINER_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../container.h"

#ifdef EXTL_CONTAINER_ARRAY_TEST_ENABLE
#	include "basic_array_test.h"
#endif

#ifdef EXTL_CONTAINER_LIST_TEST_ENABLE
#	include "basic_list_test.h"
#endif

#ifdef EXTL_CONTAINER_QUEUE_TEST_ENABLE
#	include "basic_queue_test.h"
#endif

#ifdef EXTL_CONTAINER_BIT_ARRAY_TEST_ENABLE
#	include "bit_array_test.h"
#endif

#ifdef EXTL_CONTAINER_BIT_FIELD_TEST_ENABLE
#	include "bit_field_test.h"
#endif

#ifdef EXTL_CONTAINER_FIXED_BIT_FIELD_TEST_ENABLE
#	include "fixed_bit_field_test.h"
#endif

#ifdef EXTL_CONTAINER_FIXED_MARRAY_SUPPORT
#	ifdef EXTL_CONTAINER_MARRAY_TEST_ENABLE
#		include "fixed_marray_test.h"
#	endif
#endif

#ifdef EXTL_CONTAINER_HASH_TEST_ENABLE
#	include "fixed_hash_test.h"
#endif

#ifdef EXTL_CONTAINER_MATRIX_TEST_ENABLE
#	include "basic_matrix_test.h"
#	include "symmetrical_matrix_test.h"
#	include "sparse_matrix_test.h"
#	include "symmetrical_sparse_matrix_test.h"
#endif

#ifdef EXTL_CONTAINER_QUEUE_TEST_ENABLE
#	include "fixed_reque_test.h"
#endif

#ifdef EXTL_CONTAINER_TUPLE_SUPPORT
#	ifdef EXTL_CONTAINER_TUPLE_TEST_ENABLE
#		include "tuple_test.h"
#	endif
#endif

#ifdef EXTL_CONTAINER_NET_SUPPORT
#	ifdef EXTL_CONTAINER_NET_TEST_ENABLE
#		include "basic_net_test.h"
#		include "sparse_net_test.h"
#	endif
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

