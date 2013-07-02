/* ///////////////////////////////////////////////////////////////////////
 * File:		edo_traits.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.15	
 *
 * Brief: Empty derived class optimization traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_EDO_TRAITS_H
#define EXTL_COMPILER_TRAITS_EDO_TRAITS_H

/*!\file edo_traits.h
 * \brief Empty derived class optimization traits
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
struct edo_empty{};				
/* Non-empty class */
struct edo_non_empty{int d;};

/* //////////////////////////////////////////////////////////////////////
 * EDO1:
 * empty_child - empty_base
 */
struct edo1_empty_base{};
struct edo1_empty_child : edo1_empty_base{};
struct edo1_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo1_empty_child) == sizeof(edo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO2:
 * empty_child_template - empty_base
 */
struct edo2_empty_base{};
template < typename_param_k B >
struct edo2_empty_child_template : B{};
struct edo2_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo2_empty_child_template<edo2_empty_base>) == sizeof(edo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO3:
 * empty_child - non_empty_base
 */
struct edo3_non_empty_base{int d;};
struct edo3_empty_child : edo3_non_empty_base{};
struct edo3_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo3_empty_child) == sizeof(edo_non_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO4:
 * empty_child_template - non_empty_base
 */
struct edo4_non_empty_base{int d;};
template < typename_param_k B >
struct edo4_empty_child_template : B{};
struct edo4_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo4_empty_child_template<edo4_non_empty_base>) == sizeof(edo_non_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO5:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						empty_base2
 */
struct edo5_empty_base1{};
struct edo5_empty_base2{};
struct edo5_empty_child : edo5_empty_base1, edo5_empty_base2{};
struct edo5_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo5_empty_child) == sizeof(edo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO6:
 *								empty_base1
 *							/	
 * empty_child_template	-
 *							\
 *								empty_base2
 */
struct edo6_empty_base1{};
struct edo6_empty_base2{};
template < typename_param_k B1, typename_param_k B2 >
struct edo6_empty_child_template : B1, B2{};
struct edo6_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo6_empty_child_template
														< 
															edo6_empty_base1,
															edo6_empty_base2
														>)
														== sizeof(edo_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO7:
 *						empty_base1
 *					/	
 * empty_child	-
 *					\
 *						non_empty_base2
 */
struct edo7_empty_base1{};
struct edo7_non_empty_base2{int d;};
struct edo7_empty_child : edo7_empty_base1, edo7_non_empty_base2{};
struct edo7_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo7_empty_child) == sizeof(edo_non_empty)));
};

/* //////////////////////////////////////////////////////////////////////
 * EDO8:
 *								empty_base1
 *							/	
 * empty_child_template	-
 *							\
 *								non_empty_base2
 */
struct edo8_empty_base1{};
struct edo8_non_empty_base2{int d;};
template < typename_param_k B1, typename_param_k B2 >
struct edo8_empty_child_template : B1, B2{};
struct edo8_support_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support = (sizeof(edo8_empty_child_template
														< 
															edo8_empty_base1, 
															edo8_non_empty_base2 
														>) 
														== sizeof(edo_non_empty)));
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_END_NAMESPACE 

/*!\brief Empty derived class optimization traits
 *
 * \ingroup extl_group_compiler
 */
struct edo_traits
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo1 = (EXTL_NS_DETAIL(edo1_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo2 = (EXTL_NS_DETAIL(edo2_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo3 = (EXTL_NS_DETAIL(edo3_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo4 = (EXTL_NS_DETAIL(edo4_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo5 = (EXTL_NS_DETAIL(edo5_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo6 = (EXTL_NS_DETAIL(edo6_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo7 = (EXTL_NS_DETAIL(edo7_support_traits)::is_support));
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo8 = (EXTL_NS_DETAIL(edo8_support_traits)::is_support));

	/// EDO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo = (is_support_edo1 && is_support_edo2 && 
															is_support_edo3 && is_support_edo4));
	/// Extensible EDO support 
	EXTL_STATIC_MEMBER_CONST(e_bool_t, is_support_edo_ex = (is_support_edo && is_support_edo5 && 
																is_support_edo6 && is_support_edo7 &&
																		is_support_edo8));
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing
 */
#ifdef EXTL_COMPILER_TRAITS_EDO_TRAITS_TEST_ENABLE
#	include "unit_test/edo_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_EDO_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */

