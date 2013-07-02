/* ///////////////////////////////////////////////////////////////////////
 * File:		type_buffer.h		
 *
 * Created:		08.02.15			
 * Updated:		08.07.13
 *
 * Brief: type_buffer traits - only supported at VC 6.0 7.0 7.1
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_TYPE_BUFFER_H
#define EXTL_TYPE_TRAITS_TYPE_BUFFER_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#if (defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1300))
#	if _MSC_VER == 1300
		template< typename ID >
		struct type_buffer
		{
			template < e_bool_t >
			struct result_impl;

			typedef result_impl< e_true_v > result;
		};
		template < typename T ,typename ID >
		struct save_type
			: type_buffer< ID >
		{
			template <>
			struct result_impl< e_true_v > /* VC 7.0 bug */
			{
				typedef T type;
			};
		};
#	else
		template< typename ID >	/* ID: identification */
		struct type_buffer
		{
			struct result;
		};
		template < typename T, typename ID >
		struct save_type
			: type_buffer< ID >
		{
			typedef type_buffer< ID > base_type;
			struct base_type::result /* VC 6.0 && VC 7.1 bug */
			{
				typedef T type;
			};
		};
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*EXTL_TYPE_TRAITS_TYPE_BUFFER_H */
/* //////////////////////////////////////////////////////////////////// */
