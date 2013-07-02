/* ///////////////////////////////////////////////////////////////////////
 * File:		ebo_traits.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.15	
 *
 * Brief: Empty base class optimization traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_EBO_TRAITS_H
#define EXTL_COMPILER_TRAITS_EBO_TRAITS_H

/*!\file ebo_traits.h
 * \brief Empty base class optimization traits
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_BEGIN_NAMESPACE 

/* Empty class */
struct ebo_empty{};		
/* Non-empty class */
struct ebo_non_empty{int d;};	

/* //////////////////////////////////////////////////////////////////////
 * EBO1:
 * empty_child - empty_base
 */
struct ebo1_empty_base{};
struct ebo1_empty_child : ebo1_empty_base{};
struct ebo1_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo1_empty_child) == sizeof(ebo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EBO2:
 * non_empty_child - empty_base
 */
struct ebo2_empty_base{};
struct ebo2_non_empty_child : ebo2_empty_base {int d;};
struct ebo2_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo2_non_empty_child) == sizeof(ebo_non_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EBO3:
 * empty_child - empty_base2 - empty_base1
 */
struct ebo3_empty_base1{};
struct ebo3_empty_base2 : ebo3_empty_base1{};
struct ebo3_empty_child : ebo3_empty_base2{};
struct ebo3_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo3_empty_child) == sizeof(ebo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EBO4:
 * non_empty_child - empty_base2 - empty_base1
 */
struct ebo4_empty_base1{};
struct ebo4_empty_base2 : ebo4_empty_base1{};
struct ebo4_non_empty_child : ebo4_empty_base2{int d;};
struct ebo4_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo4_non_empty_child) == sizeof(ebo_non_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EBO5:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						empty_base2
 */
struct ebo5_empty_base1{};
struct ebo5_empty_base2{};
struct ebo5_empty_child : ebo5_empty_base1, ebo5_empty_base2{};
struct ebo5_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo5_empty_child) == sizeof(ebo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EBO6:
 *							empty_base1
 *						/	
 * non_empty_child	-
 *						\
 *							empty_base2
 */
struct ebo6_empty_base1{};
struct ebo6_empty_base2{};
struct ebo6_non_empty_child : ebo6_empty_base1, ebo6_empty_base2{int d;};
struct ebo6_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo6_non_empty_child) == sizeof(ebo_non_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EBO7:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						non_empty_base2
 */
struct ebo7_empty_base1{};
struct ebo7_non_empty_base2{int d;};
struct ebo7_empty_child : ebo7_empty_base1, ebo7_non_empty_base2{};
struct ebo7_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(ebo7_empty_child) == sizeof(ebo_non_empty)));
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_END_NAMESPACE 

/*!\brief Empty base class optimization traits
 *
 * \ingroup extl_group_compiler
 */
struct ebo_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo1 = (EXTL_NS_DETAIL(ebo1_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo2 = (EXTL_NS_DETAIL(ebo2_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo3 = (EXTL_NS_DETAIL(ebo3_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo4 = (EXTL_NS_DETAIL(ebo4_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo5 = (EXTL_NS_DETAIL(ebo5_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo6 = (EXTL_NS_DETAIL(ebo6_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo7 = (EXTL_NS_DETAIL(ebo7_support_traits)::is_support));

	/// Basic EBO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo = (is_support_ebo1 && is_support_ebo2 && 
															is_support_ebo3 && is_support_ebo4));
	/// Extensible EBO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_ebo_ex = (is_support_ebo && is_support_ebo5 && 
																is_support_ebo6 && is_support_ebo7));
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing
 */
#ifdef EXTL_COMPILER_TRAITS_EBO_TRAITS_TEST_ENABLE
#	include "unit_test/ebo_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_EBO_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */

