/* ///////////////////////////////////////////////////////////////////////
 * File:		is_polymorphic.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: is_polymorphic traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_IS_POLYMORPHIC_H
#define EXTL_TYPE_TRAITS_IS_POLYMORPHIC_H

#ifndef EXTL_TYPE_TRAITS_IS_POLYMORPHIC_SUPPORT
#	error extl::is_polymorphic is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_IS_CLASS_SUPPORT
#	include "is_class.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MUST_BE_POLYMORPHIC(type)			EXTL_MUST_BE_(is_polymorphic, type)
#define EXTL_MUST_BE_CV_POLYMORPHIC(type)		EXTL_MUST_BE_CV_(is_polymorphic, type)

#define EXTL_MUST_NOT_BE_POLYMORPHIC(type)		EXTL_MUST_NOT_BE_(is_polymorphic, type)
#define EXTL_MUST_NOT_BE_CV_POLYMORPHIC(type)	EXTL_MUST_NOT_BE_CV_(is_polymorphic, type)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT
/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T >
struct is_polymorphic_helper1 : public T
{
	is_polymorphic_helper1(); 
	~is_polymorphic_helper1(); // note: non-virtual destructor 
	e_byte_t padding[256];
private:
	is_polymorphic_helper1(is_polymorphic_helper1 const&);
	is_polymorphic_helper1& operator=(is_polymorphic_helper1 const&);
};

template < typename_param_k T >
struct is_polymorphic_helper2 : public T
{
	is_polymorphic_helper2(); 
	virtual ~is_polymorphic_helper2(); // note: virtual destructor 
	e_byte_t padding[256];
private:
	is_polymorphic_helper2(is_polymorphic_helper2 const&);
	is_polymorphic_helper2& operator=(is_polymorphic_helper2 const&);
};

template < e_bool_t is_class >
struct is_polymorphic_helper
{
	template < typename_param_k T >
	struct result
	{
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
	};
};

EXTL_TEMPLATE_SPECIALISATION
struct is_polymorphic_helper< e_true_v >
{
	template < typename_param_k T >
	struct result
	{
		/* T is polymorphic class if non-virtual derived class 
		 * and virtual derived class have same size.
		 */
		EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (sizeof(is_polymorphic_helper1<T>) == sizeof(is_polymorphic_helper2<T>)));
	};
};

template < typename_param_k T >
struct is_polymorphic_impl
	: is_polymorphic_helper< (is_class<T>::value) >::template_qual_k result<T>
{
};

EXTL_BOOL_TRAIT_DEF_1(is_polymorphic, is_polymorphic_impl< T >::value)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#	ifdef EXTL_TYPE_TRAITS_TEST_ENABLE
#		include "unit_test/is_polymorphic_test.h"
#	endif
#endif /* EXTL_TYPE_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_IS_POLYMORPHIC_H */
/* //////////////////////////////////////////////////////////////////// */
