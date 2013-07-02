/* ///////////////////////////////////////////////////////////////////////
 * File:		compiler_traits.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.15	
 *
 * Brief:		The Compiler Traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS__H
#define EXTL_COMPILER_TRAITS_H

/*!\file compiler_traits.h
 * \brief The Compiler traits
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "ebo_traits.h"
#include "edo_traits.h"
#include "rvo_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief The Compiler traits 
 *
 * \ingroup extl_group_compiler
 */
struct compiler_traits
{
	/// EBO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo = (ebo_traits::is_support_ebo));
	/// Extensible EBO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo_ex = (ebo_traits::is_support_ebo_ex));

	/// EDO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo = (edo_traits::is_support_edo));
	/// Extensible EDO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo_ex = (edo_traits::is_support_edo_ex));

	/// RVO support 
	static e_bool_t is_support_rvo()
	{
		return rvo_traits::is_support_rvo();
	}
	/// NRVO support 
	static e_bool_t is_support_nrvo()
	{
		return rvo_traits::is_support_nrvo();
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COMPILER_TRAITS_TEST_ENABLE
#	include "unit_test/compiler_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */

