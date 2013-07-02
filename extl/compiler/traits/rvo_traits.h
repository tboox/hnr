/* ///////////////////////////////////////////////////////////////////////
 * File:		rvo_traits.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.15	
 *
 * Brief: Return value optimization
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_COMPILER_TRAITS_RVO_TRAITS_H
#define EXTL_COMPILER_TRAITS_RVO_TRAITS_H

/*!\file rvo_traits.h
 * \brief Return value optimization
 */
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../counter/object_counter.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * RVO(Return value optimization)
 */
struct rvo_obj : public object_counter<rvo_obj>
{
	rvo_obj(){}
	rvo_obj(int data)
		: m_data(data)
	{
	}
	int m_data;
};

EXTL_INLINE rvo_obj rvo_func(int i)
{
	/* Compiler will optimize the temporary object if support RVO*/
	return rvo_obj(i);
}
EXTL_INLINE e_bool_t is_support_rvo()
{
	rvo_obj nrv;
	nrv = rvo_func(1);
	/* The number of copy constructor is zero because no exist the temporary object */
	return object_counter<rvo_obj>::get_copy_count() == 0;
}
/* ///////////////////////////////////////////////////////////////////////
 * NRVO(Named return value optimization)
 */
struct nrvo_obj : public object_counter<nrvo_obj>
{
	int m_data;
};

EXTL_INLINE nrvo_obj nrvo_func(int i)
{
	/* Compiler will optimize the ret if support NRVO*/
	nrvo_obj ret;
	ret.m_data = i;
	return ret;
}
EXTL_INLINE e_bool_t is_support_nrvo()
{
	nrvo_obj nrv;
	nrv = nrvo_func(1);
	/* The number of copy constructor is zero because no exist the ret */
	return object_counter<nrvo_obj>::get_copy_count() == 0;
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::deatil namespace 
 */
EXTL_DETAIL_END_NAMESPACE 

/*!\brief Return value optimization
 *
 * \ingroup extl_group_compiler
 */
struct rvo_traits
{
	static e_bool_t is_support_rvo()
	{
		return EXTL_NS_DETAIL(is_support_rvo)();
	}
	static e_bool_t is_support_nrvo()
	{
		return EXTL_NS_DETAIL(is_support_nrvo)();
	}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit testing
 */
#ifdef EXTL_COMPILER_TRAITS_RVO_TRAITS_TEST_ENABLE
#	include "unit_test/rvo_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_COMPILER_TRAITS_RVO_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */

