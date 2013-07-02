/* ///////////////////////////////////////////////////////////////////////
 * File:		has_virtual_destructor_test.h		
 *
 * Created:		08.02.02					
 * Updated:		08.07.09	
 *
 * Brief: has_virtual_destructor unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTORY_H
#	error This file must be included of has_virtual_destructor.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

struct has_virtual_destructor_test_struct{};
struct has_virtual_destructor_test_virtual_struct
{
	has_virtual_destructor_test_virtual_struct(){};
	virtual ~has_virtual_destructor_test_virtual_struct(){};
};
union has_virtual_destructor_test_union{};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
EXTL_INLINE void has_virtual_destructor_test()
{
	EXTL_MUST_HAVE_VIRTUAL_DESTRUCTOR(has_virtual_destructor_test_virtual_struct);
	
	EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(float);
	EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(float *);
	EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(has_virtual_destructor_test_struct);
	EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(has_virtual_destructor_test_union);
	EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(has_virtual_destructor_test_virtual_struct *);
	EXTL_MUST_NOT_HAVE_VIRTUAL_DESTRUCTOR(has_virtual_destructor_test_virtual_struct [10]);
	
}

/* ///////////////////////////////////////////////////////////////////////
 * extl::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
